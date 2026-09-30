---
scope: Evidence of demonstrated C understanding in this repository
role: Append-only context for future tutoring, rechecks, and retrospectives
truth: Code, Git history, and verification output are primary evidence; this log points to them
updated: 2026-09-30
limits: This is not a transcript, diary, score, or substitute for re-verification
---

# Learning Log

Append one entry when a stage passes or the user explicitly closes a session.
Use `Outcome`, `Assistance`, `Demonstrated`, `Corrected`, `Evidence`, and
`Next check`. Earlier entries remain unchanged; a later entry supersedes a
mistaken assessment explicitly.

From 2026-09-30 an entry lands in the same commit as the state it describes.
The `study` program changes in place from stage to stage, so read an entry's
paths at the commit that added it: `git log --reverse -S'<entry heading>' --
LEARNING_LOG.md` finds it. For an earlier entry, that commit shows where the
paths were, not always the state the entry describes. A path in an old entry
may not exist at HEAD after later moves.

## 2026-09-22 — Stage 1: Function pointers

**Outcome:** passed; `fp_practice1.c` retains a separate unfinished struct case

**Assistance:** conceptual-hint

**Demonstrated:**

- Declared function pointers from parameter and return types.
- Reassigned one compatible pointer from one function to another.
- Explained that reassignment changes the stored function target, not the
  pointer's type.
- Called compatible functions through the pointer and predicted their results.

**Corrected:**

- A pointer declaration does not allocate storage for its pointee.
- `int *p = &value` initializes `p`; `*p = value` writes through an already
  valid pointer.
- A null pointer is a defined empty pointer value, not integer storage.
- A different function signature is incompatible at assignment time, not only
  when the call executes.

**Evidence:**

- `practice/01-function-pointers/fp_practice2.c`
- `practice/01-function-pointers/fp_practice3.c`
- The session observed outputs `100`, `500`, `12`, and `7`.
- Repository verification reran both completed programs with the `c` wrapper on
  2026-09-22 and reproduced those outputs without compiler diagnostics.
- GDB showed one `int (*)(int)` pointer change from `basic_sale` to `VIP_sale`.
- `practice/01-function-pointers/fp_practice1.c` is preserved as an unfinished
  attempt and is not passing evidence for its struct case. The workshop warning
  policy rejects its uninitialized `c.right` before execution.

**Next check:** mutate the caller's struct through a pointer without returning a
replacement value.

## 2026-09-22 — Stage 2: Struct callbacks

**Outcome:** passed

**Assistance:** clarification

**Demonstrated:**

- Stored data and a compatible function pointer in each struct instance.
- Assigned different callbacks to two instances, then changed only one.
- Predicted that equal callbacks with equal arguments produce equal results,
  regardless of which instance stores the pointer.
- Explained that a callback field does not automatically receive its containing
  struct's members.

**Corrected:**

- Separate callback fields are separate storage even when their stored function
  addresses are equal.
- Object data reaches a callback only through arguments supplied at the call.

**Evidence:**

- `practice/02-struct-callbacks/fp_practice4.c`
- The session observed output `12`, `4`, `7`, and `4`.
- Repository verification reran the program with the `c` wrapper on 2026-09-22
  and reproduced the output without compiler diagnostics.

**Next check:** Stage 3 — pass a struct address to a function and explain why
the mutation remains visible to the caller.

## 2026-09-23 — Stage 3: Struct pointers

**Outcome:** passed; extended three-instrument case completed

**Assistance:** conceptual-hint

**Demonstrated:**

- Modeled each instrument as an independent `inst` object containing its value,
  calibration count, and reset count.
- Passed an individual instrument address to `calib` and `reset`, then changed
  the caller's original object through `->`.
- Distinguished a pointer to one instrument from a pointer to a container of
  several instruments.
- Treated a zero calibration and a reset operation as calls that increment
  their respective counters even when the value does not change.

**Corrected:**

- A braced initializer is valid while declaring an object; it is not a plain
  right-hand side for assignment after declaration.
- A function remains reusable when its parameter represents one instrument,
  rather than hard-coding a container's first, second, and third members.

**Evidence:**

- `practice/03-struct-pointers/extended_practice3.c`
- The `c` wrapper ran the extended Case 1 on 2026-09-23 without compiler
  diagnostics. It produced values `22 28 17` after calibration and `0 28 17`
  after resetting the first instrument; calibration counts were `1 1 2` and
  reset counts were `1 0 0`.

**Next check:** Stage 4 — pass a timer to its callback so the callback can use
the timer's own final state and runs only once at expiration.

## 2026-09-23 — Stage 5.5: Owned string checkpoint

**Outcome:** session closed with the ownership concept demonstrated; the
optional checkpoint and Review 3–5 brief were not passed as complete programs

**Assistance:** direct-fix

**Demonstrated:**

- Allocated separate storage for a `Memo` object and its string, then copied
  the local character array including its terminator.
- Changed the local input from `original` to `changed` while the copied string
  still printed `original`.
- Identified that replacing `m->str` with a string-literal address loses the
  owned allocation and makes a later `free(m->str)` invalid.
- Described a replacement sequence: allocate and copy new content, retain the
  old value if allocation fails, then free the old allocation and store the new
  address. The replacement sequence was not implemented or verified.

**Corrected:**

- Copying a pointer value into a struct member does not copy the pointed-to
  bytes. A copied C string also needs its terminating null byte.
- `sizeof(s)` inside a function with a `char *s` parameter measures the
  pointer, while `strlen(s) + 1` gives the string's required storage size.
- `free` needs the address returned by allocation; it does not take a size.

**Evidence:**

- `practice/review-03-05/extra_practice.c` at session close allocates and
  copies a local `char input[32]`, then frees the owned string and object.
- The `c` wrapper ran that file on 2026-09-23 without warnings. Its output
  showed `original` in `m->str` and `changed` in `input`.
- The current code does not check either allocation result. `change()` is
  commented out, so replacement, pointer-based time change, and the original
  countdown callback requirements remain unverified.

**Next check:** Start Stage 6 with one owned study record; confirm allocation
failure cleanup before expanding to multiple records.

## 2026-09-23 — Stage 5.5: Completion decision

**Outcome:** passed under the learner-approved owned-string checkpoint scope;
this supersedes the preceding incomplete-checkpoint assessment. Stage 4 and 5
standalone briefs remain deferred, and their original callback and failure
path requirements were not verified here.

**Assistance:** direct-fix

**Demonstrated:**

- Copied the local array into separately owned storage, changed the original,
  and observed that the stored string kept its original content.
- Released the owned string and then the containing object on the normal path.
- Explained why `free` needs the allocation's original address and why a
  replacement must preserve the old string if the new allocation fails.

**Corrected:**

- The review's completion boundary is the owned-string checkpoint, not the
  earlier countdown and file-output extension.

**Evidence:**

- `practice/review-03-05/extra_practice.c` printed `original` for the stored
  string and `changed` for the input on 2026-09-23.
- The strict C17 warning build succeeded. Valgrind reported 0 errors and 0
  blocks in use at exit. AddressSanitizer and UndefinedBehaviorSanitizer ran
  successfully with leak detection disabled; Valgrind supplied the leak check.
- Allocation-failure handling was not exercised and carries into Stage 6.
  String replacement was not exercised and carries into Stage 10.

**Next check:** Stage 6 — create multiple owned study records, grow their
storage, and test cleanup when allocation fails.

## 2026-09-24 — Stage 6: Record-centered refactor in progress

**Outcome:** refactored the prototype back to one `Sub` per study record; the
stage is not passed.

**Assistance:** direct-fix

**Demonstrated:** Distinguished a study record from a subject with nested
sessions. `Rec` owns the record array and its `count/capacity`; repeated subject
names remain separate records.

**Evidence:** `practice/06-dynamic-array/practice6.c` stores one `minutes` value
per `Sub` and grows `Rec.list` in `Sub_add`. The strict `c` build and
`lab/test_stage6_record_model.sh` passed with the six expected records in order.

**Next check:** connect command-line pairs to record creation, then verify empty,
invalid, and over-capacity inputs and memory cleanup.

## 2026-09-29 — Stage 6: Study Records

**Outcome:** passed. The program reads `SUBJECT MINUTES` pairs from `argv`,
stores each pair as a separate owned record, and meets the brief, the shared
contract, and a learner-solved variation.

**Assistance:** direct-fix

**Demonstrated:**

- Explained `argc`/`argv`: the C runtime calls `main` with the word count and a
  pointer array; `argv` is `char **`, `argv[i]` is `char *`, `argv[i][j]` is
  `char`, and every argument arrives as a string.
- Derived digit conversion as `tmp = 10 * tmp + (c - '0')` and reset `tmp`
  per pair after a printf trace showed `3045`.
- Explained why checking `tmp > 1440` after each digit prevents `int` overflow:
  the value at the top of each iteration is at most 1440, so the next step is
  at most 14409. Placed `tmp < 1` after the loop to reject both `0` and `""`.
- Split cleanup responsibility: `Sub_add` frees only what the current call
  allocated and returns `NULL`; `main` sets `status` and jumps to one
  `cleanup` label that calls `record_free`. Kept `new_record` failure out of
  `cleanup` because `record_free(NULL)` would dereference `NULL`.
- Separated the print loop from the free loop so the error path frees records
  without printing them.
- Distinguished input errors (own message, stderr, exit 2) from allocation
  failures (`perror`, exit 1).
- Variation (independent after `strcmp` and index clarification): warned on
  stderr when a subject equals the previous record's subject, guarded by
  `r->count > 0` and read at `r->list[r->count - 1]` before `Sub_add`.

**Corrected:**

- `memcpy(argv[i], &tmp, ...)` copied an `int`'s bytes into a 3-byte string
  and overwrote the next arguments; an integer belongs in an `int`, not back in
  the string. Memory has no type; the reader's type decides the meaning.
- A free loop that started at `list[count]` and used `r->count--` twice per
  pass read past the array and freed mismatched slots.
- `goto cleanup` without `status = 2` exited 0 on an input error.
- `!strpbrk(...)` rejected valid subjects; adding digits to the forbidden set
  violated the shared contract and was reverted. `strpbrk` finds any shared
  character, so it cannot test equality.
- `==` on two `char *` compares addresses, not contents.
- A gdb session keeps the binary it started with; the custom `rerun` did not
  rebuild `c dbg` binaries (handed off separately).

**Evidence:**

- `practice/06-dynamic-array/practice6.c` on 2026-09-29.
- Strict `c` build without diagnostics. Brief inputs: no arguments prints
  `No entries.` on stdout with exit 0; `C`, `C nope`, `C 0`, `C 1441`,
  `"" 30`, `$'C\tX' 30`, `C 99999999999` exit 2 with stderr only; `C 30` and
  the Try it runs exit 0 in input order; 21 records keep order across growth.
- Valgrind reported 0 errors and 0 bytes in use for normal, input-error,
  empty, and growth runs. ASan/UBSan runs were clean.
- `lab/failinject/run.sh` failed each of the 6 allocations in `C 30 OS 45`
  and the `realloc` at the 11th record: every run exited 1 with no Valgrind
  error or leak and printed no records.
- gdb: after `Sub_add`, setting `argv[1][0] = 'X'` left
  `r->list[0]->name` as `"C"` at a separate heap address.
- Variation: the five brief commands behaved as specified;
  `> out.txt` kept the warning on screen and only records in the file.

**Next check:** Stage 7 — decide multi-file build support for the `c`
wrapper first, then split the record module and add `list`/`total`.
`lab/test_stage6_record_model.sh` still expects the old hard-coded records.

## 2026-09-30 — Stage 7: List and Total

**Outcome:** passed under a learner-approved narrowed scope. `study list` and
`study total` read `SUBJECT MINUTES ...` pairs into one `Rec` per run and print
the records or their sum. `main.c` (interface) and `record.c` (core) are
separate modules. Two brief items are carried to Stage 10 and were not verified
here: one shared traversal that takes the per-record function (`Read_list`,
`Read_total`, and an unused `print_result` are still three loops, and
`Read_total` calls its function once with the finished sum), and the small
in-process check that lists and totals the same `Rec`.

**Assistance:** concrete-hint. One item was a direct-fix: at the learner's
request the tutor supplied the two-line change that moves `No entries.` from
`argc_check` into the `list` branch.

**Demonstrated:**

- Split `practice6.c` into `main.c` (argv, output, exit codes) and `record.c`
  (`Rec`, its array, validation). The compiler error `invalid use of incomplete
  typedef 'Rec'` (commit `af23ba0`) showed the hidden definition was enforced;
  a traversal function in `record.c` then replaced the field access in `main.c`.
- Derived the argument count with a command word: `argc` is `2n + 2` for `n`
  pairs. Argued that `study foo 30` cannot be told from a subject while the
  command may be absent, so the command word became mandatory and the
  no-command path was removed.
- Explained two ownership layers: `main` decides when the `Rec` handle is
  created and freed (one `new_record`, one `record_free` on every path), and
  only `record.c` knows how to allocate and free the array, each `Sub`, and each
  name copy. `argv` strings belong to neither, because `Sub_add` copies names.
- Stated that the `name` a callback receives points into memory owned by `Rec`
  and stays valid until `record_free`.
- Moved the running sum from a file-scope `total` to a local in `Read_total`
  after review showed that a second call in one process would print 150
  instead of 75.
- Variation (`longest`, no code supplied): keep the current maximum as a local
  in the traversal, call the passed function once with the result, and return
  `NULL` for an empty record set so `main` can tell.

**Corrected:**

- `argv[1] == "total"` compared addresses, so no branch ran; `strcmp` compares
  contents (`-Waddress`).
- A label is visible only inside its own function. The helper returns the exit
  code and `main` jumps to `cleanup`; a `status` passed by value would not have
  reached `main`.
- Two Stage 6 rules survived the move: `argc % 2 == 0` rejected every valid
  command, and `strcmp(argv[i - 1], argv[i - 3])` read `argv[0]` or `argv[-1]`
  on the first pair (segfault on `./study C 30`) until guarded by `i > 3`.
- One function mixed validation with the empty-list message: `total` printed
  both `No entries.` and `Total: 0 minutes`, and its `exit` skipped
  `record_free` (Valgrind: still reachable, 104 bytes in 2 blocks). Returning a
  status and printing `No entries.` in the `list` branch fixed both.
- A missing or unknown command first exited 0 with a stdout message; it now
  writes to stderr and exits 2. A non-void function fell off its end
  (`-Wreturn-type`).
- An empty result is a normal outcome; it must not share the channel that
  carries the error exit codes 1 and 2 (raised in review).

**Evidence:**

- Strict build with the Makefile flags (`-Werror -Wconversion -Wshadow` and the
  rest) produced no diagnostics on 2026-09-30.
- Runs: `list C 30 OS 45` printed both records in input order; `total C 30 OS 45`
  printed `Total: 75 minutes` and `total C 60 OS 45` printed 105; `list` printed
  `No entries.` and `total` printed `Total: 0 minutes`; `list C 30 OS`,
  `list C abc`, `list C 1441`, an unknown command, and no command exited 2 with
  output on stderr only.
- Valgrind reported "All heap blocks were freed" and 0 errors on `list`,
  `total`, `list C 30 OS 45`, `total C 30`, `foo 30`, `list C 30 OS`, and
  `list C abc`. An ASan/UBSan build ran the main cases without reports.
- Not exercised: allocation-failure injection (`lab/failinject/run.sh`) and
  growth past 10 records through `list` and `total`.

**Next check:** Stage 8 — with `list PATH`, `argc == 2` no longer means an empty
list, so the core must report whether it holds records; the `FILE *` module
must keep earlier records intact when the read buffer is reused. Carried from
this stage: one traversal for `list` and `total` before the Stage 10 filters,
and the in-process check that lists and totals one `Rec`.

## 2026-10-01 — Stage 8: Save and Load, session close

**Outcome:** session closed; the stage is not passed. The `list PATH` read
path works: `storage.c` reads the TSV file into the `Rec` that `main`
creates, and `main` prints the records or an error. `save PATH`,
`total PATH`, the empty-list output `No entries.`, and the Stage 8 gates
remain.

**Assistance:** concrete-hint. On request the tutor added the `storage.o`
lines to the Makefile and step TODO comments (intent and hints; the learner
removed them), and wrote the probe `lab/buffer_probe.c`. One direct-fix: at
the learner's decision the tutor deleted the branch that stripped `\r`
before `\n`.

**Demonstrated:**

- Predicted from `_IO_read_ptr` in gdb that a second `fread(mine, 1, 8, f)`
  leaves `minutes\n` in `mine`. Predicted that `fgets` with size 8 returns
  `subject` and then `\tminute`, and explained that `size - 1` decides the
  cut.
- Named the whole-line signal: a line read to its end still holds `\n`;
  otherwise it was cut or is the last line.
- Reasoned that a record must own a copy made before the read buffer is
  reused, then located that copy in `Sub_add` (`strlen + 1`, `memcpy`), so
  `storage.c` passes pointers into its own buffer.
- Carried the Stage 7 ownership rule: `main` creates and frees `Rec`;
  storage only fills it and closes the `FILE *` it opened.
- Designed `file_read(Rec *r, const char *file, size_t *err_line)`: the
  return value gives the kind (`STORAGE_OK`, `STORAGE_ERR_IO`,
  `STORAGE_ERR_FORMAT`, `STORAGE_ERR_NOMEM`), and the line number goes
  through an out-parameter, the pattern of `minutes_parse`.
- Wrote `\0` over the tab and the newline in the read buffer, arguing that
  the buffer belongs to his code.
- Chose `fgets` over `fread` with a manual search and over `getline` on
  cleanup, code size, and build flags, and knew its cost: lines longer than
  the buffer.
- Counted the header as line 1 so that the number matches an editor.

**Corrected:**

- The stdio buffer is not a `FILE` member. `fopen` allocated 472 bytes and
  the first read a separate 4096-byte block (Valgrind `--trace-malloc`); the
  `_IO_*` members point into that one block. `char mine[9] = {0}` changed no
  `FILE` member (gdb dumps before and after the line).
- `fread` takes a destination, an item size, an item count, and a stream,
  not a range.
- `strlen` measures bytes already in memory up to `\0`; it cannot size a
  line that has not been read.
- `malloc(sizeof(*copy * 9))` allocated 4 bytes (Valgrind: invalid write,
  4 bytes definitely lost).
- Storage calling a function in `main.c` would reverse the call direction;
  `main` calls storage.
- `typedef struct Rec Rec;` in `storage.h` declared a type other than
  `struct _Record` (`conflicting types for 'Rec'`).
- `char *buf` pointed nowhere and `sizeof(buf)` gave the pointer size; it
  became `char buf[1024]`.
- `atoi` accepts `30abc`; `minutes_parse` is the contract check.
- Review found four defects, all fixed: a bad value returned the I/O code
  without a line; an empty file reported line 0; the header was not
  compared; a read error (`ferror`) ended as success.

**Evidence:**

- `projects/study-cli/storage.c`, `storage.h`, `main.c`, and `Makefile` at
  the commit that adds this entry. The strict Makefile build exits 0.
- `sc vg list`: the normal file, a last line without `\n`, subjects with
  spaces and Korean, and 25 records print in order with exit 0. An empty
  file and a `garbage` header report line 1, `OS\tabc` line 3, `DB\t0`
  line 4, a blank line 3, and a CRLF line 2, all with exit 1. A directory
  and a missing path print `cannot read file` with exit 1. No path exits 2.
  Valgrind reported nothing on any run.
- `nm -u storage.o record.o` shows no gate-6 name. `LOGIC_OBJS` is not in
  the Makefile yet.
- Not exercised: ASan/UBSan and allocation failure inside `file_read`. A
  valid line with a 1020-byte subject is rejected and reported one line
  late, because the leftover `\n` is read as a line.

**Next check:** print `No entries.` for a header-only file through a core
query (`argc == 2` no longer means empty); `total PATH` through
`file_read`; `save PATH [SUBJECT MINUTES ...]`, where pairs start at
`argv[3]`, invalid input leaves the file unchanged, the `FILE *` must reach
the write step although the traversal callback takes only `name` and
`minutes`, and a write failure is not reported as success; a policy for
lines longer than the buffer; `LOGIC_OBJS`, ASan, and the DESIGN.md
worksheet rows.
