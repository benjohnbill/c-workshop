---
scope: Evidence of demonstrated C understanding in this repository
role: Append-only context for future tutoring, rechecks, and retrospectives
truth: Code, Git history, and verification output are primary evidence; this log points to them
updated: 2026-09-22
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
