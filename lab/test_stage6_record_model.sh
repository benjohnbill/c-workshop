#!/usr/bin/env bash
# Usage: lab/test_stage6_record_model.sh [BINARY]
# Checks Stage 6 behavior against the brief and the shared contract:
# stdout, exit code, and whether stderr got a message.
# Without BINARY it builds practice6.c with the c wrapper; with BINARY
# (for example projects/study-cli/study) it runs that executable.
set -uo pipefail
bin=${1:+$(realpath "$1")}
cd "$(dirname "$0")/.."

src=lab/stage6/archived_practice6.c
fails=0

run() {
    if [[ -n $bin ]]; then "$bin" "$@"; else c "$src" "$@"; fi
}

# check NAME EXIT STDERR(yes|no) STDOUT [ARGS...]
check() {
    local name=$1 want_exit=$2 want_err=$3 want_out=$4
    shift 4
    local out err got_exit
    err=$(mktemp)
    out=$(run "$@" 2>"$err")
    got_exit=$?
    local got_err=no
    [[ -s $err ]] && got_err=yes
    rm -f "$err"
    if [[ $got_exit != "$want_exit" || $got_err != "$want_err" || $out != "$want_out" ]]; then
        printf 'FAIL %s: exit %s (want %s), stderr %s (want %s)\n%s\n' \
            "$name" "$got_exit" "$want_exit" "$got_err" "$want_err" "$out" >&2
        fails=$((fails + 1))
    else
        printf 'ok   %s\n' "$name"
    fi
}

check "two records" 0 no \
    $'Subject : C\n- Minutes : 30\nSubject : OS\n- Minutes : 45' C 30 OS 45
check "space and Korean subject" 0 no \
    $'Subject : C pointers\n- Minutes : 20\nSubject : 자료구조\n- Minutes : 1440' \
    "C pointers" 20 자료구조 1440
check "grows past capacity" 0 no \
    "$(for i in $(seq 1 11); do printf 'Subject : s%d\n- Minutes : %d\n' "$i" "$i"; done)" \
    $(for i in $(seq 1 11); do printf 's%d %d ' "$i" "$i"; done)
check "empty" 0 no "No entries."
check "consecutive subject warns" 0 yes \
    $'Subject : C\n- Minutes : 10\nSubject : C\n- Minutes : 15' C 10 C 15

check "missing minutes" 2 yes "" C
check "odd pair" 2 yes "" C 30 OS
check "empty subject" 2 yes "" "" 30
check "tab in subject" 2 yes "" $'C\tx' 30
check "zero minutes" 2 yes "" C 0
check "over 1440" 2 yes "" C 1441
check "sign" 2 yes "" C +30
check "decimal" 2 yes "" C 30.5
check "trailing letter" 2 yes "" C 30m
check "empty minutes" 2 yes "" C ""

if (( fails )); then
    printf '%d check(s) failed\n' "$fails" >&2
    exit 1
fi
