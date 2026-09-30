---
scope: Deferred extension: scheduler-model behavior specification
truth: This is a cooperative state model, not an operating-system thread scheduler
updated: 2026-09-22
---

# Extension — Cooperative Scheduler Model

## Scenario

Task 객체가 자신의 list link를 내부에 포함하고, scheduler가 별도 wrapper node를
할당하지 않은 채 ready queue를 관리해요. 실제 thread나 context switch 없이 한
번에 한 step씩 task callback을 실행해 상태 전이를 관찰해요.

## Required behavior

- Task는 ID, 이름, priority, 상태, flag, 남은 step과 실행 동작을 가져요.
- Ready task 중 priority가 가장 높은 task를 선택해 한 step 실행해요.
- 같은 priority에서는 ready queue에 먼저 들어온 task를 먼저 선택해요.
- 실행 후 step이 남으면 ready queue 뒤에 다시 넣고, 끝났으면 completed 상태로
  바꿔 queue에서 제외해요.
- Blocked task는 ready queue에 없어야 하며, unblock하면 queue 뒤에 들어가요.
- 동일한 task를 queue에 두 번 넣는 동작과 잘못된 상태 전이를 거부해요.
- Scheduler 종료 후 모든 task가 어느 상태인지 출력해요.

## Acceptance scenario

- `compile` priority 3, 2 steps
- `write` priority 2, 2 steps
- `backup` priority 2, 1 step
- `idle` priority 0, 1 step

처음에는 `backup`을 blocked 상태로 두고 두 번 scheduling한 뒤 unblock해요. 매
선택과 상태 전이를 출력하여 priority 선택, 같은 priority의 FIFO, requeue,
completion을 확인해요.

Expected selection order:

```text
compile
compile
write
backup
write
idle
```

Intrusive list의 link는 task의 일부이며 scheduler는 task storage를 소유하지
않아요. 종료 시 list가 비어 있고 어떤 link도 두 list에 동시에 속하지 않아야
해요.
