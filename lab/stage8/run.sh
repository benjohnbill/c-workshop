#!/usr/bin/env bash
# Usage: lab/stage8/run.sh
# Runs every Stage 8 list fixture in this folder through `sc vg list` (sc runs
# make first) and compares the exit status. Valgrind errors exit 99 and fail.
# One file by hand: sc vg list lab/stage8/badval.tsv; echo $?
set -u
here=$(cd "$(dirname "$0")" && pwd)
pass=0; fail=0

check() { # WANT_EXIT DESCRIPTION ARGS...
    want=$1; desc=$2; shift 2
    out=$(sc vg "$@" 2>&1); got=$?
    if [ "$got" = "$want" ]; then mark=PASS; pass=$((pass + 1)); else mark=FAIL; fail=$((fail + 1)); fi
    printf '%s exit=%s want=%s  %-26s %s\n' "$mark" "$got" "$want" "$desc" \
        "$(printf '%s' "$out" | tr '\n' ' ' | sed "s|$here/||g" | cut -c1-70)"
}

check 0 "normal file"            list "$here/ok.tsv"
check 0 "no final newline"       list "$here/nofinalnl.tsv"
check 0 "spaces and Korean"      list "$here/korean.tsv"
check 0 "25 records"             list "$here/many.tsv"
check 0 "header only"            list "$here/header-only.tsv"   # No entries. comes later
check 1 "empty file: line 1"     list "$here/empty.tsv"
check 1 "bad header: line 1"     list "$here/badhead.tsv"
check 1 "OS<TAB>abc: line 3"     list "$here/badval.tsv"
check 1 "DB<TAB>0: line 4"       list "$here/zero.tsv"
check 1 "blank line: line 3"     list "$here/blank.tsv"
check 1 "CRLF: line 2"           list "$here/crlf.tsv"
check 1 "directory: read error"  list "$here"
check 1 "missing file"           list "$here/nope.tsv"
check 2 "no path"                list

echo "pass=$pass fail=$fail"
[ "$fail" -eq 0 ]
