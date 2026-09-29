#!/usr/bin/env bash
# Usage: lab/failinject/run.sh FILE.c N [ARGS...]
# Builds FILE.c with malloc/realloc routed through failinject.c, makes the
# Nth call fail, and runs the result under valgrind. The source is not changed.
set -euo pipefail
here=$(cd "$(dirname "$0")" && pwd)
src=$1; n=$2; shift 2
out=$(mktemp -d)
trap 'rm -rf "$out"' EXIT
# failinject.c must NOT get the -include, or fi_malloc would call itself.
gcc -std=c17 -g -c "$here/failinject.c" -o "$out/fi.o"
gcc -std=c17 -g -include "$here/failinject.h" -c "$src" -o "$out/prog.o"
gcc "$out/prog.o" "$out/fi.o" -o "$out/prog"
FAIL_AT=$n valgrind -q --leak-check=full --error-exitcode=99 "$out/prog" "$@"
