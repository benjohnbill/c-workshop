---
scope: Stage 3 behavior specification
truth: This file defines required behavior; the extended stage also defines representation constraints
updated: 2026-09-22
---

# Stage 3 — Instrument Calibration

구조체 주소를 함수에 전달해 선택한 계측기의 원본 측정값을 바꿔요.

## Base Stage 3

- 첫 번째 계측기는 `18`, 두 번째 계측기는 `31`에서 시작해요.
- 첫 번째에 `+4`, 두 번째에 `-3` 보정을 적용해요.
- 두 값을 출력한 뒤 첫 번째 계측기만 초기화하고 다시 출력해요.
- 계측기는 서로 독립적이며, 보정량은 양수·`0`·음수를 같은 방식으로 처리해요.

### Expected output

```text
After calibration: 22 28
After reset: 0 28
```

## Extended Stage 3

- 계측기 하나를 구조체 인스턴스 하나로 표현해 세 개를 만들어요.
- 보정 함수는 선택한 구조체의 주소와 보정량을, 초기화 함수는 선택한 구조체의
  주소를 받아 원본을 바꿔요.
- 두 함수는 구조체 포인터로 멤버에 접근해요. 멤버의 `int *`만 전달하면 이
  단계의 목표를 충족하지 않아요.
- 각 계측기는 현재값, 보정 횟수, 초기화 횟수를 보관해요. 값이 바뀌지 않아도
  보정 또는 초기화 함수를 호출했다면 해당 횟수는 늘어나요.
- 구조체 선언과 함수 원형은 직접 설계해요.

| Case | Start values | Calibration | Reset target |
| --- | --- | --- | --- |
| Case 1 | `18`, `31`, `12` | 첫째 `+4`, 둘째 `-3`, 셋째 `0`, `+5` | 첫 번째 |
| Case 2 | `-5`, `0`, `40` | 첫째 `-2`, `+2`; 둘째 `0`; 셋째 `+7` | 두 번째 두 번 |

각 Case에서 보정 후와 초기화 후에 현재값, 보정 횟수, 초기화 횟수를 출력해요.
한 계측기의 작업이 나머지 둘을 바꾸면 안 돼요.

### Case 1 expected output

```text
After calibration: values=22 28 17 | calibrations=1 1 2 | resets=0 0 0
After reset: values=0 28 17 | calibrations=1 1 2 | resets=1 0 0
```

Case 2의 출력은 실행 전에 직접 예측해요.
