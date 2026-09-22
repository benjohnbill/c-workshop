---
scope: Stage 4 behavior specification
truth: This file defines required behavior, not implementation structure
updated: 2026-09-22
---

# Stage 4 — Countdown Timers

## Scenario

이름과 남은 시간을 가진 여러 countdown timer를 관리해요. 각 timer는 만료될 때
서로 다른 알림 동작을 실행하며, 그 동작은 어느 timer가 만료됐는지와 해당
timer의 최종 상태를 사용할 수 있어야 해요.

## Required behavior

- `tea` timer는 2 tick, `stretch` timer는 3 tick에서 시작해요.
- 한 round마다 활성 timer의 남은 시간을 1씩 줄여요.
- 남은 시간이 0이 된 순간 해당 timer의 알림을 한 번만 실행해요.
- 한 round에서 발생한 알림을 먼저 출력한 뒤 두 timer의 상태를 출력해요.
- 이미 만료된 timer는 이후 round에서 다시 알리지 않아요.
- 모든 timer가 만료될 때까지 round를 진행해요.

## Expected output

```text
Round 1: tea=1 stretch=2
[tea] done at 0
Round 2: tea=0 stretch=1
[stretch] done at 0
Round 3: tea=0 stretch=0
```
