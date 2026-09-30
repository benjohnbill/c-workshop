---
scope: Stage 10 behavior specification
truth: This file defines this version's behavior; the shared contract and the final CLI contract are in ../README.md
updated: 2026-09-30
---

# Stage 10 — Edit and Filter

## Usage

1. 저장된 기록을 ID로 수정하거나 삭제합니다.
2. 날짜나 과목을 지정해 목록과 합계에서 원하는 기록을 찾아봅니다.

## Try it

[Stage 9 Try it](09-daily-cli.md#try-it)의 테스트 파일에 이어서 실행합니다.

```sh
./study edit 1 --minutes 40
./study list --subject C
./study total --date 2026-09-23 --subject C
./study remove 2
./study add --subject 자료구조 --minutes 20 --date 2026-09-23
./study list
```

필터 합계는 `Total: 40 minutes`이고 마지막 목록에는 ID 1과 3이 남습니다.

## Behavior

네 절([Commands](../README.md#commands), [Data rules](../README.md#data-rules), [Query output](../README.md#query-output), [Storage](../README.md#storage)) 전체를 적용합니다. 일부 field만 수정하면 나머지는 유지합니다.
없는 ID나 실패한 저장 때문에 다른 기록이 바뀌면 안 됩니다.

## Done when

- 빈 목록, 일부 field 수정, 없는 ID, 두 필터의 조합을 확인합니다.
- 최대 ID를 지운 뒤와 모든 기록을 지운 뒤, 재실행·추가해도 ID를 재사용하지 않습니다.
- 손상된 파일과 저장 실패에서 원본을 유지합니다.
- 단위 테스트는 argv와 terminal 없이 기록 관리와 파일 입출력을 직접 호출해 배열 확장, deep copy, 수정·삭제, TSV round trip을 검증합니다.
- Shell 통합 테스트는 임시 `STUDY_DATA_FILE`을 사용하며 실제 `$HOME/.study.tsv`를 건드리지 않습니다.
- Sanitizer·Valgrind와 [공통 완료 조건](../../../CURRICULUM.md#shared-completion-gates)을 통과합니다.

## Used again in Stage 11

Stage 11의 list와 total 줄은 이 단계의 필터 규칙(날짜와 과목을 함께 주면 둘 다 만족)과
total 규칙을 같은 뜻으로 씁니다. CLI와 화면에서 같은 기록의 합계가 같아야 하며, 이 일치는 Stage 11 Done when이 확인합니다.

다음 버전: [조회 전용 TUI](11-terminal-viewer.md).
