---
scope: Stage 6 behavior specification
truth: This file defines required behavior, not implementation structure
updated: 2026-09-22
---

# Stage 6 — Growing Playlist

## Scenario

빈 재생 목록에 제목을 계속 추가하고, 중간 항목을 제거하고, 다시 새 항목을
추가해요. 저장 공간의 크기와 관계없이 재생 순서와 각 제목의 내용이 유지되어야
해요.

## Required behavior

- 빈 목록에 `Intro`, `Pointers`, `Ownership`, `Lists`, `CLI`를 순서대로 추가해요.
- 세 번째 항목 `Ownership`을 제거하고 나머지 순서를 유지해요.
- 끝에 `Pintos`를 추가해요.
- 목록의 항목 수와 모든 제목을 순서대로 출력해요.
- 존재하지 않는 index 제거는 목록을 바꾸지 않고 실패를 알려요.
- 저장 공간 확장에 실패하면 기존 목록과 문자열을 그대로 사용할 수 있어야 해요.
- 종료 시 목록이 소유한 모든 자원을 정리해요.

## Expected output

```text
5 tracks
1. Intro
2. Pointers
3. Lists
4. CLI
5. Pintos
```
