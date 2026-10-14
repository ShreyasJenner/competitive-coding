#!/usr/bin/env bash
# Remove everything build.sh and test.sh generate: usr/bin and usr/obj.
set -euo pipefail

ROOT="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd -P)"

rm -rf "$ROOT/usr/bin" "$ROOT/usr/obj"
# Stray binaries from compiling by hand inside the source tree.
find "$ROOT/usr/src" "$ROOT/usr/test" -type f \( -name 'a.out' -o -name '*.o' -o -name '*.d' \) -print -delete 2>/dev/null || true
echo "clean: removed usr/bin and usr/obj"
