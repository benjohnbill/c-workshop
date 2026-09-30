---
scope: Deferred extension: allocator-model behavior specification
truth: This is a bounded learning model, not a replacement for libc malloc
updated: 2026-09-22
---

# Extension — Arena Allocator Model

## Scenario

4096-byte 고정 arena를 여러 요청에 나눠 주고 다시 회수하는 작은 allocator
모형을 만들어요. System allocator를 대체하거나 성능 점수를 얻는 것이 아니라,
block metadata와 free block 변화가 눈에 보이게 만드는 단계예요.

## Required behavior

- 반환하는 payload 시작 주소는 16-byte aligned여야 해요.
- 요청 크기와 block 관리에 필요한 공간을 구분해요.
- 첫 번째로 들어맞는 free block을 선택해요.
- 남는 공간이 유효한 block을 만들 만큼 크면 분할해요.
- 해제한 block과 물리적으로 인접한 free block을 합쳐요.
- 0-byte 요청, arena보다 큰 요청, arena 밖 주소와 중복 해제를 거부해요.
- Arena 내부 block을 offset, total size, allocation state 순서로 출력할 수
  있어야 해요.
- Model 내부에서 payload를 얻기 위해 system `malloc()`을 사용하지 않아요.

## Acceptance sequence

1. 서로 다른 크기의 block 세 개를 할당하고 alignment와 비중첩을 확인해요.
2. 가운데 block을 해제하고 더 작은 요청이 해당 공간을 재사용하는지 확인해요.
3. 인접 block을 해제하고 이전보다 큰 요청이 병합된 공간에 들어가는지 확인해요.
4. 모든 block을 해제한 뒤 arena가 하나의 free block으로 돌아오는지 확인해요.

각 단계에서 block 전체 크기의 합이 항상 arena 크기와 같아야 해요.
