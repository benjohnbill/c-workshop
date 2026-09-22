---
scope: Stage 3 behavior specification
truth: This file defines required behavior, not implementation structure
updated: 2026-09-22
---

# Stage 3 — Instrument Calibration

## Scenario

서로 독립적인 두 계측기의 현재 측정값을 관리해요. 보정 작업은 선택한 계측기의
현재 상태를 바꾸고, 초기화 작업은 선택한 계측기 하나만 0으로 돌려요.

## Required behavior

- 첫 번째 계측기는 `18`, 두 번째 계측기는 `31`에서 시작해요.
- 첫 번째에 `+4`, 두 번째에 `-3` 보정을 적용해요.
- 두 값을 출력한 뒤 첫 번째 계측기만 초기화하고 다시 출력해요.
- 다른 계측기에 대한 작업이 나머지 계측기의 상태를 바꾸면 안 돼요.
- 0과 음수 보정량도 같은 규칙으로 처리해요.

## Expected output

```text
After calibration: 22 28
After reset: 0 28
```
