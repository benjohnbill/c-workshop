---
scope: Stage 5 behavior specification
truth: This file defines required behavior, not implementation structure
updated: 2026-09-22
---

# Stage 5 — Owned Contacts

## Scenario

연락처는 이름과 메모를 보관해요. 연락처를 만든 뒤 입력에 사용했던 문자열을
바꾸거나 재사용해도 연락처에 저장된 내용은 유지되어야 해요. 메모를 교체할 수
있고, 마지막에는 연락처가 소유한 모든 자원을 정리해요.

## Required behavior

- 이름 `Mina`, 메모 `C study`로 연락처 하나를 만들어요.
- 생성에 사용한 원본 문자열을 다른 내용으로 덮어쓴 뒤 연락처를 출력해요.
- 연락처의 메모를 `malloc and free`로 교체하고 다시 출력해요.
- 생성이나 메모 교체가 실패하면 이미 확보한 자원을 남기지 않고 실패를 알려요.
- 정상 종료와 실패 경로 모두에서 연락처가 소유한 자원이 남으면 안 돼요.

## Expected output

```text
Mina: C study
Mina: malloc and free
```
