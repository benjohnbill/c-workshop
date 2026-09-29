---
scope: Stage 7 behavior specification
truth: This file defines this version's behavior and required practice; directory name predates the CLI curriculum
updated: 2026-09-23
---

# Stage 7 — List and Total

## 사용 흐름

1. `list`에 기록을 전달하면 각 기록을 입력 순서대로 확인합니다.
2. `total`에 기록을 전달하면 총 공부 시간을 분 단위로 확인합니다.
3. 기록은 해당 실행에서만 사용하며, 파일에 저장되지는 않습니다.

## Try it

```sh
./study list C 30 OS 45
./study total C 30 OS 45
./study list
./study total
```

합계는 `Total: 75 minutes`이며, 빈 입력의 결과는 `No entries.`와 `Total: 0 minutes`입니다.

## Behavior

- 문법은 `study list [SUBJECT MINUTES ...]`, `study total [SUBJECT MINUTES ...]`입니다.
- [공통 입력 규칙](../../projects/study-cli/README.md#shared-contract)을 유지합니다. 명령 누락과 알 수 없는 명령은 오류입니다.
- 조회와 집계는 기록의 내용·순서를 바꾸거나 기록을 해제하지 않습니다.
- 같은 기록 모음에 목록 출력과 집계를 연이어 적용해도 결과가 유지됩니다.
- 파일 저장과 필터는 아직 다루지 않습니다.

필수 연습: 기록 관리와 명령 실행을 별도 source module로 분리합니다.
목록 출력과 집계에서 기록별 처리 동작을 함수 포인터로 전달해 사용하는 지점을
한 곳 만듭니다. 함수 원형과 누적 결과의 보관 위치는 직접 설계합니다.

## Done when

- 같은 기록으로 `list`와 `total`을 실행하고, 시간을 바꾸면 합계도 바뀌는지 확인합니다.
- 빈 목록과 잘못된 명령·입력을 확인합니다.
- 한 process에서 같은 기록 모음을 출력하고 집계하는 작은 검증을 수행합니다.
- [공통 완료 조건](../../CURRICULUM.md#shared-completion-gates)을 통과하고 각 module이 소유하는 자원을 설명합니다.

이 단계 진입 시 여러 source file을 `study`로 build하고 run/debug할 방법을
정합니다. 개인 `c` wrapper의 단일 파일 동작은 보존합니다. 위 명령은 해당
build로 만들어진 실행 파일을 사용하는 예시입니다.

다음 버전: [파일 저장과 불러오기](../08-integrated-system/README.md).
