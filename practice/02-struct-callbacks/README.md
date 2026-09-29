---
scope: Stage 2 retrospective and preserved exercise
truth: practice2-1.c is the original completed session artifact
updated: 2026-09-22
---

# Stage 2 — Struct Callbacks

같은 구조체 타입으로 만든 여러 객체가 서로 다른 데이터와 callback 값을 가질 수
있음을 확인한 단계예요.

## Scenario

두 숫자와 둘 중 하나를 고르는 동작을 하나의 객체에 보관해요. 첫 번째 객체는 큰
값을, 두 번째 객체는 작은 값을 선택해요. 이후 첫 번째 객체의 동작만 작은 값
선택으로 바꿔 두 번째 객체의 상태가 영향을 받지 않는지 확인해요.

## Observed output

```text
첫 번째: 12
두 번째: 4
변경 후 첫 번째: 7
변경 후 두 번째: 4
```

원본 구현은 `practice2-1.c`에 있어요.
