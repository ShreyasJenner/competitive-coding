#!/usr/bin/env bash
# Compile every .c/.cpp under usr/src into usr/bin, mirroring the folder layout.
#
#   ./build.sh                     build everything (only what changed)
#   ./build.sh leetcode/301        build one file (path relative to usr/src,
#                                  extension optional; full paths also work)
#   ./build.sh 301                 same, if only one file is named 301.*
#
# Objects and dependency files go to usr/obj. A file is rebuilt when it, or
# anything it #includes, is newer than its object.
#
# Override compilers/flags via env: CC, CXX, CFLAGS, CXXFLAGS.
# test.sh reuses this script through BUILD_SRC / BUILD_OUT / BUILD_DEFS.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"
SRC="${BUILD_SRC:-$ROOT/usr/src}"
OUT="${BUILD_OUT:-}"                     # subfolder of usr/bin and usr/obj
BIN="$ROOT/usr/bin${OUT:+/$OUT}"
OBJ="$ROOT/usr/obj${OUT:+/$OUT}"
DEFS="${BUILD_DEFS:-}"

CC="${CC:-gcc}"
CXX="${CXX:-g++}"
SAN="-fsanitize=address,undefined"
CFLAGS="${CFLAGS:--std=gnu17 -Wall -Wextra -g $SAN}"
CXXFLAGS="${CXXFLAGS:--std=c++20 -Wall -Wextra -g $SAN}"

# Map an argument to a source file under $SRC.
resolve() {
  local arg=$1 cand
  for cand in "$arg" "$SRC/$arg" "$SRC/$arg.cpp" "$SRC/$arg.c"; do
    if [[ -f $cand ]]; then
      cand="$(realpath "$cand")"
      [[ $cand == "$SRC"/* ]] && { echo "$cand"; return 0; }
    fi
  done
  # Bare problem name ("301"): accept it if exactly one file matches.
  mapfile -t cand < <(find "$SRC" -type f \( -name "$arg.c" -o -name "$arg.cpp" \))
  if ((${#cand[@]} == 1)); then echo "${cand[0]}"; return 0; fi
  if ((${#cand[@]} > 1)); then
    echo "build: '$arg' is ambiguous: ${cand[*]#$SRC/}" >&2
    return 1
  fi
  echo "build: no source for '$arg' under ${SRC#$ROOT/}" >&2
  return 1
}

# True when $obj is missing or older than any dependency listed in $dep.
stale() {
  local obj=$1 dep=$2 f
  [[ -f $obj && -f $dep ]] || return 0
  for f in $(sed -e 's/^[^:]*://' -e 's/\\$//' "$dep"); do
    [[ -f $f && ! $f -nt $obj ]] || return 0
  done
  return 1
}

build_one() {
  local src=$1 rel stem obj dep bin cc flags
  rel="${src#$SRC/}"
  stem="${rel%.*}"
  obj="$OBJ/$stem.o"
  dep="$OBJ/$stem.d"
  bin="$BIN/$stem"

  if [[ $src == *.c ]]; then cc=$CC; flags=$CFLAGS; else cc=$CXX; flags=$CXXFLAGS; fi

  if [[ -x $bin ]] && ! stale "$obj" "$dep"; then
    echo "  up to date  $rel"
    return 0
  fi

  mkdir -p "$(dirname "$obj")" "$(dirname "$bin")"
  # shellcheck disable=SC2086  # flags are intentionally word-split
  if $cc $flags $DEFS -MMD -MP -MF "$dep" -c "$src" -o "$obj" &&
     $cc $flags "$obj" -o "$bin"; then
    echo "  built       $rel -> ${bin#$ROOT/}"
  else
    rm -f "$obj" "$bin"
    echo "  FAILED      $rel"
    return 1
  fi
}

sources=()
if (($#)); then
  for arg in "$@"; do sources+=("$(resolve "$arg")") || exit 1; done
else
  mapfile -t sources < <(find "$SRC" -type f \( -name '*.c' -o -name '*.cpp' \) | sort -V)
fi

if ((${#sources[@]} == 0)); then
  echo "build: nothing to compile in ${SRC#$ROOT/}"
  exit 0
fi

failed=0
for src in "${sources[@]}"; do
  build_one "$src" || failed=$((failed + 1))
done

if ((failed)); then
  echo "build: $failed of ${#sources[@]} failed"
  exit 1
fi
