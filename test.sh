#!/usr/bin/env bash
# Compile and run the tests in usr/test.
#
#   ./test.sh                  build and run every test
#   ./test.sh leetcode/301     build and run one test (relative to usr/test)
#   ./test.sh 301              same, if only one test is named 301.cpp
#
# A test file mirrors its solution's path: usr/test/leetcode/301.cpp tests
# usr/src/leetcode/301.cpp. It #includes the solution and is compiled with
# -DTEST, so wrap the solution's own main() in `#ifndef TEST ... #endif`.
# Tests use usr/test/testlib.hpp: testlib::record() per case, and main()
# ends with `return testlib::summary();`. This script reads the summary line
# to report case totals across all test files.
#
# Binaries go to usr/bin/test, objects to usr/obj/test.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
TESTS="$ROOT/usr/test"
BIN="$ROOT/usr/bin/test"

resolve() {
  local arg=$1 cand
  for cand in "$arg" "$TESTS/$arg" "$TESTS/$arg.cpp"; do
    if [[ -f $cand ]]; then
      cand="$(realpath "$cand")"
      [[ $cand == "$TESTS"/* ]] && { echo "$cand"; return 0; }
    fi
  done
  # Bare problem name ("301"): accept it if exactly one test matches.
  mapfile -t cand < <(find "$TESTS" -type f -name "$arg.cpp")
  if ((${#cand[@]} == 1)); then echo "${cand[0]}"; return 0; fi
  if ((${#cand[@]} > 1)); then
    echo "test: '$arg' is ambiguous: ${cand[*]#$TESTS/}" >&2
    return 1
  fi
  echo "test: no test for '$arg' under usr/test" >&2
  return 1
}

tests=()
if (($#)); then
  for arg in "$@"; do tests+=("$(resolve "$arg")") || exit 1; done
else
  mapfile -t tests < <(find "$TESTS" -type f -name '*.cpp' | sort -V)
fi

if ((${#tests[@]} == 0)); then
  echo "test: no tests in usr/test"
  exit 0
fi

echo "Compiling tests"
# Build failures are reported per test below, so don't stop here.
BUILD_SRC="$TESTS" BUILD_OUT=test BUILD_DEFS="-DTEST" "$ROOT/build.sh" "${tests[@]}" || true

log="$(mktemp)"
trap 'rm -f "$log"' EXIT

files_passed=0
cases_passed=0
cases_failed=0
failed=()   # "stem  (reason)" per failing file
for t in "${tests[@]}"; do
  rel="${t#$TESTS/}"
  stem="${rel%.*}"
  bin="$BIN/$stem"
  echo
  echo "== $stem"
  if [[ ! -x $bin ]]; then
    echo "   (did not compile)"
    failed+=("$stem  (did not compile)")
    continue
  fi

  # Running inside a subshell keeps a crash down to one "Aborted" line rather
  # than a noisy pipeline job notice. Sanitizer reports still come through.
  set +e
  ("$bin"; exit $?) 2>&1 | tee "$log"
  status=${PIPESTATUS[0]}
  set -e

  # testlib::summary() prints "cases: <p> passed, <f> failed".
  summary="$(grep -E '^cases: [0-9]+ passed, [0-9]+ failed$' "$log" | tail -1 || true)"
  if [[ -z $summary ]]; then
    # No summary: it crashed (or main() skipped testlib::summary()). Count the
    # cases that finished before that point.
    p=$(grep -c '^PASS ' "$log" || true)
    f=$(grep -c '^FAIL ' "$log" || true)
    cases_passed=$((cases_passed + p))
    cases_failed=$((cases_failed + f))
    failed+=("$stem  (stopped with exit $status after $((p + f)) cases: crashed, or main() doesn't return testlib::summary())")
    continue
  fi
  read -r p f < <(sed -E 's/^cases: ([0-9]+) passed, ([0-9]+) failed$/\1 \2/' <<<"$summary")
  cases_passed=$((cases_passed + p))
  cases_failed=$((cases_failed + f))

  if ((status == 0 && f == 0)); then
    files_passed=$((files_passed + 1))
  elif ((f > 0)); then
    failed+=("$stem  ($f of $((p + f)) cases failed)")
  else
    failed+=("$stem  (all cases passed, but exited with status $status)")
  fi
done

echo
echo "test: $cases_passed cases passed, $cases_failed failed" \
     "(${#tests[@]} files: $files_passed passed, ${#failed[@]} failed)"
for f in "${failed[@]}"; do echo "  FAILED  $f"; done
((${#failed[@]} == 0))
