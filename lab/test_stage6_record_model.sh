#!/usr/bin/env bash
set -euo pipefail

actual=$(c practice/06-dynamic-array/practice6.c)
expected=$'C : 30\nOS : 45\n\nC pointers : 20\n자료구조 : 40\nC : 10\nC : 15'

if [[ "$actual" != "$expected" ]]; then
    printf 'Unexpected output:\n%s\n' "$actual" >&2
    exit 1
fi
