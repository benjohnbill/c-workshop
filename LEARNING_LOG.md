---
scope: Evidence of demonstrated C understanding in this repository
role: Append-only context for future tutoring, rechecks, and retrospectives
truth: Code, Git history, and verification output are primary evidence; this log points to them
updated: 2026-09-29
limits: This is not a transcript, diary, score, or substitute for re-verification
---

# Learning Log

Append one entry when a stage passes or the user explicitly closes a session.
Use `Outcome`, `Assistance`, `Demonstrated`, `Corrected`, `Evidence`, and
`Next check`. Earlier entries remain unchanged; a later entry supersedes a
mistaken assessment explicitly.

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
