---
scope: External contract and acceptance criteria for Stages 9 and 10
truth: This file defines the study CLI interface and persistence behavior
updated: 2026-09-22
---

# Stages 9–10 — Study CLI

터미널에서 공부 기록을 추가하고, 다시 실행한 뒤에도 조회·수정·삭제·집계할 수
있는 `study` 프로그램을 만들어요. Stage 9에서 저장 기반과 세 명령을 만들고,
Stage 10에서 실사용 기능과 오류 복구를 완성해요.

## Commands

```text
study help
study add --subject SUBJECT --minutes MINUTES [--date YYYY-MM-DD] [--note NOTE]
study list [--date YYYY-MM-DD] [--subject SUBJECT]
study total [--date YYYY-MM-DD] [--subject SUBJECT]
study edit ID [--subject SUBJECT] [--minutes MINUTES] [--date YYYY-MM-DD] [--note NOTE]
study remove ID
```

옵션 순서는 자유로워요. 명령 이름, 도움말, 결과와 오류 메시지는 영어로
출력해요. Subject와 note 값에는 한국어를 포함한 UTF-8 byte string을 허용해요.

## Data rules

- `add`의 date 기본값은 실행한 날의 local date예요.
- minutes는 `1–1440`이고 subject는 비어 있을 수 없어요.
- note는 빈 문자열을 허용해요.
- subject와 note에 tab, carriage return, newline이 있으면 거부해요.
- date는 실제로 존재하는 `YYYY-MM-DD` 날짜여야 해요.
- date와 subject filter를 함께 지정하면 두 조건을 모두 만족해야 해요.
- `edit`는 최소 하나의 변경 option이 필요해요.
- ID는 현재까지 사용한 최대 ID에 1을 더하며 삭제한 ID를 재사용하지 않아요.
- 정상 종료는 exit `0`, I/O·memory·없는 ID 등의 실행 실패는 `1`, 잘못된
  command·option·value는 `2`예요.

## Storage

- `STUDY_DATA_FILE`이 설정되어 있으면 해당 경로를 사용해요.
- 없으면 `$HOME/.study.tsv`를 사용해요.
- 둘 다 사용할 수 없으면 경로를 추측하지 않고 오류로 종료해요.
- 첫 줄은 `id`, `date`, `subject`, `minutes`, `note`의 TSV header예요.
- 변경 명령은 전체 파일을 읽고 검증한 뒤 임시 파일에 완전히 기록하고
  `rename()`으로 교체해요.
- 손상된 행을 만나면 행 번호를 포함한 오류를 출력하고 원본을 변경하지 않아요.
- 여러 process의 동시 수정과 file locking은 v1 범위 밖이에요.

## Stage 9 acceptance

- `help`, `add`, `list`가 동작해요.
- 데이터 파일이 없는 첫 실행을 빈 기록으로 처리해요.
- `add` 후 다른 process에서 `list`하여 같은 기록을 확인해요.
- 잘못된 option과 값이 지정된 exit status와 오류를 반환해요.
- 종료 시 load 과정에서 확보한 모든 자원을 정리해요.

## Stage 10 acceptance

- `total`, `edit`, `remove`, date·subject filter가 동작해요.
- 빈 목록, 일부 field 수정, 없는 ID, 손상된 TSV를 처리해요.
- 저장 실패 시 기존 파일 내용이 유지돼요.
- 단위 테스트가 동적 배열 증가, deep copy, 수정·삭제, TSV round trip을
  검증해요.
- Shell 통합 테스트는 임시 `STUDY_DATA_FILE`을 사용하며 실제
  `$HOME/.study.tsv`를 건드리지 않아요.
- Sanitizer와 Valgrind에서 invalid access와 leak이 없어요.
