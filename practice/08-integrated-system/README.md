---
scope: Stage 8 behavior specification
truth: This file defines required behavior, not implementation structure
updated: 2026-09-22
---

# Stage 8 — Delivery Center

## Scenario

배송 센터는 여러 package를 보관하고 각 package에 선택된 배송 policy로 요금을
계산해요. Package가 발송되거나 취소되면 센터에서 사라지고, 나머지 package와
policy는 계속 정상적으로 사용할 수 있어야 해요.

## Required behavior

- 다음 package 세 개를 등록해요.
  - `#101`, label `books`, 2 kg, economy
  - `#102`, label `laptop`, 1 kg, express
  - `#103`, label `clothes`, 5 kg, economy
- Economy 요금은 기본 1000원과 kg당 500원이에요.
- Express 요금은 기본 3000원과 kg당 1000원이에요.
- 모든 package의 ID, label, policy와 계산된 요금을 출력해요.
- `#102`를 발송하여 센터에서 제거하고 남은 package를 다시 출력해요.
- 존재하지 않는 ID의 발송·취소는 다른 package를 바꾸지 않고 실패를 알려요.
- 센터가 종료될 때 남아 있는 package와 각 package가 소유한 자원을 정리해요.
- 등록, 제거, 전체 정리 중 어느 단계에서도 해제된 package를 다시 사용하면 안 돼요.

## Expected output

```text
#101 books economy 2000
#102 laptop express 4000
#103 clothes economy 3500
Dispatched #102
Remaining:
#101 books economy 2000
#103 clothes economy 3500
```
