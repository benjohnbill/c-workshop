---
scope: Stage 1 retrospective and preserved exercises
truth: The C files in this directory are the original session artifacts
updated: 2026-09-22
---

# Stage 1 — Function Pointers

함수 포인터의 타입을 선언하고, 같은 타입의 여러 함수 사이에서 호출 대상을
교체하는 단계예요.

## Preserved exercises

- `practice1-1.c`: 최초 시도예요. 일반 함수 포인터 부분은 진행됐지만 구조체
  case에는 유효한 저장 공간을 가리키지 않는 포인터가 남아 있어 실행 대상으로
  사용하지 않아요.
- `practice1-2.c`: 일반 회원과 VIP 적립 함수를 하나의 함수 포인터로 교체해요.
- `practice1-3.c`: 큰 값과 작은 값을 고르는 함수를 하나의 함수 포인터로 교체해요.

## Observed output

`practice1-2.c`:

```text
일반 회원 적립금: 100원
VIP 회원 적립금: 500원
```

`practice1-3.c`:

```text
큰 값: 12
작은 값: 7
```

원본은 학습 이력을 위해 수정하지 않았어요. 이 단계의 이해 근거는
[the learning log](../../LEARNING_LOG.md)에 있어요.
