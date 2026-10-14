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
# The test's main() should return non-zero when any case fails.
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

passed=0
failed=()
for t in "${tests[@]}"; do
  rel="${t#$TESTS/}"
  stem="${rel%.*}"
  bin="$BIN/$stem"
  echo
  echo "== $stem"
  if [[ ! -x $bin ]]; then
    echo "   (did not compile)"
    failed+=("$stem")
  elif "$bin"; then
    passed=$((passed + 1))
  else
    failed+=("$stem")
  fi
done

echo
echo "test: $passed passed, ${#failed[@]} failed"
for f in "${failed[@]}"; do echo "  FAILED  $f"; done
((${#failed[@]} == 0))
