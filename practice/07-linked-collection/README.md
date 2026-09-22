---
scope: Stage 7 behavior specification
truth: This file defines required behavior, not implementation structure
updated: 2026-09-22
---

# Stage 7 — Undo History

## Scenario

편집 작업의 설명을 시간순으로 기록하고 가장 최근 작업부터 되돌려요. 되돌린
기록은 history에서 사라지고, 이후 새 작업을 추가하면 현재 남아 있는 history
뒤에 이어져요.

## Required behavior

- `open file`, `insert title`, `delete line`을 순서대로 기록해요.
- 두 번 undo하여 `delete line`, `insert title` 순서로 반환해요.
- `save file`을 새로 기록해요.
- 오래된 항목부터 현재 history를 출력해요.
- 빈 history에서 undo하면 실패를 알리고 상태를 바꾸지 않아요.
- 한 항목 제거와 전체 정리 모두에서 다른 항목의 연결과 문자열이 유효해야 해요.
- history의 데이터 관리와 실행 예시는 별도 source module로 분리해요.

## Expected output

```text
Undo: delete line
Undo: insert title
History:
1. open file
2. save file
```

## Tool boundary

이 단계부터 multi-file build가 필요해요. 시작할 때 개인 `c` wrapper의 기존
단일 파일 동작을 보존하면서 project executable을 run/debug할 방법을 별도
작업으로 결정해요. 이 문제를 한 파일로 합쳐서 우회하지 않아요.
