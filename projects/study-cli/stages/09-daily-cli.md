---
scope: Stage 9 behavior specification
truth: This file defines this version's behavior; the shared contract and the final CLI contract are in ../README.md
updated: 2026-09-30
---

# Stage 9 — Daily CLI

## Usage

1. `add`로 과목과 시간을 기록하고, 필요하면 날짜와 메모를 덧붙입니다.
2. 나중에 `list`와 `total`로 저장된 기록과 합계를 확인합니다.
3. 기록은 명령을 다시 실행해도 파일에 남으며, 각 기록에는 ID가 붙습니다.

## Try it

```sh
export STUDY_DATA_FILE="$(mktemp -d)/study.tsv"
./study help
./study add --subject C --minutes 30 --date 2026-09-23 --note "pointer review"
./study add --subject OS --minutes 45 --date 2026-09-23
./study list
./study total
```

새 파일에서는 ID 1과 2의 기록이 보이고 합계는 `Total: 75 minutes`입니다.
각 명령은 별도 process로 실행됩니다. 환경 변수는 테스트용 경로를 지정합니다.

## Behavior

[Commands](../README.md#commands)·[Data rules](../README.md#data-rules)·[Query output](../README.md#query-output)·[Storage](../README.md#storage)에서 Stage 9에 해당하는 계약을
적용합니다. `edit`, `remove`, 조회 필터는 Stage 10 범위입니다. Stage 8의
실험 파일은 변환하지 않으며, 새 v1 파일로 시작합니다.

## Done when

- 새 경로에서 추가한 기록을 다른 process의 `list`·`total`로 확인합니다.
- 옵션 순서를 바꾸고 날짜·메모를 생략해도 계약대로 동작합니다.
- 잘못된 옵션·날짜·시간(exit `2`)과 손상된 파일(exit `1`)을 거부하고 기존 파일을 유지합니다.
- 저장 실패 시 기존 파일과 `next_id`가 유지되고 성공으로 보고되지 않습니다.
- 정상·실패 경로의 파일과 메모리를 정리하고 [공통 완료 조건](../../../CURRICULUM.md#shared-completion-gates)을 통과합니다.

## Used again in Stage 11

Stage 11의 `study-tui`는 이 단계의 v1 파일을 같은 규칙으로 읽습니다: 파일 없음은 빈
기록, 손상된 파일은 행 번호를 담은 오류, 저장된 `next_id`와 ID 규칙은 그대로입니다.

다음 버전: [수정·삭제·필터](10-edit-and-filter.md).
