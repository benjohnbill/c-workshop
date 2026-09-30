---
scope: Shared contract for Stages 6–11 and the final CLI and data-file contract
truth: This file defines shared input rules and the final CLI contract; Stage 6–8 briefs define their interim commands
updated: 2026-09-30
---

# Study CLI

Stage 6부터 이 디렉터리에서 하나의 프로그램을 키웁니다. 구현과 build 파일은
직접 만듭니다. 현재 단계의 명세를 기준으로 구현하고, 이후 단계에서 필요한 변경을 이어갑니다.

| Version | Brief |
| --- | --- |
| 6 — 메모리 안의 기록 | [Study Records](stages/06-study-records.md) |
| 7 — 목록·집계와 module 분리 | [List and Total](stages/07-list-and-total.md) |
| 8 — 파일 저장·불러오기 | [Save and Load](stages/08-save-and-load.md) |
| 9 — 정식 명령과 안전한 저장 | [Daily CLI](stages/09-daily-cli.md) |
| 10 — 수정·삭제·필터 | [Edit and Filter](stages/10-edit-and-filter.md) |
| 11 — 조회 전용 TUI | [Terminal Viewer](stages/11-terminal-viewer.md) |

실행 파일은 둘입니다. `study`는 CLI이고 기록을 바꾸는 유일한 프로그램이에요.
`study-tui`(Stage 11)는 조회 전용이며 기록 관리와 파일 입출력 소스를 `study`와
공유해요.

## Shared contract

Stage 6부터 적용합니다.

- Subject는 비어 있을 수 없고, 공백·한국어를 포함한 UTF-8 byte string을 허용합니다. Tab, carriage return, newline은 거부합니다.
- Minutes는 십진 숫자로만 표현한 `1–1440`의 정수입니다. 부호·소수·숫자 뒤의 다른 문자는 거부합니다.
- 정상 종료는 exit `0`, I/O·memory·없는 ID·손상된 데이터 파일 등의 실행 실패는 `1`, 잘못된 command·option·value는 `2`입니다.
- 결과는 stdout, 오류는 stderr에 영어로 출력합니다. 명시된 결과 문구 외의 꾸밈과 오류 문장은 자유입니다.

아래는 Stage 9–10 CLI의 계약이며, Stage 11의 `study-tui`도 같은 데이터 파일을 읽어요. Stage 6–8의 임시 명령 형식은 각 brief를 따릅니다.

## Commands

```text
study help
study add --subject SUBJECT --minutes MINUTES [--date YYYY-MM-DD] [--note NOTE]
study list [--date YYYY-MM-DD] [--subject SUBJECT]
study total [--date YYYY-MM-DD] [--subject SUBJECT]
study edit ID [--subject SUBJECT] [--minutes MINUTES] [--date YYYY-MM-DD] [--note NOTE]
study remove ID
```

Stage 9에서는 `help`, `add`, 필터 없는 `list`·`total`을 구현합니다.
Stage 10에서 나머지를 추가합니다. 옵션 순서는 자유이며, 알 수 없는 옵션,
중복 옵션, 옵션 값 누락과 불필요한 인자는 거부합니다.

## Data rules

- `add`의 date 기본값은 실행한 날의 local date예요.
- Subject와 minutes는 [Shared contract](#shared-contract)를 따릅니다.
- Note는 생략 시 빈 문자열이며, 공백·한국어를 포함한 UTF-8 byte string을 허용합니다. Tab, carriage return, newline은 거부합니다.
- date는 실제로 존재하는 `YYYY-MM-DD` 날짜여야 해요.
- Subject filter는 UTF-8 byte 기준의 case-sensitive exact match예요.
- Date와 subject filter를 함께 지정하면 두 조건을 모두 만족해야 해요.
- `edit`는 최소 하나의 변경 option이 필요해요.
- 각 add는 저장된 `next_id`를 사용한 뒤 값을 1 증가시켜요. 삭제된 ID는
  재사용하지 않아요.
- ID는 양의 정수입니다. `edit`에서 지정하지 않은 field는 유지합니다.

## Query output

- `list`는 `ID DATE SUBJECT MINUTES NOTE` field를 ID 오름차순으로 출력해요.
- Filter가 적용돼도 같은 field와 순서를 유지해요.
- 일치하는 기록이 없으면 `No entries.`를 출력하고 exit `0`으로 종료해요.
- `total`은 일치하는 기록의 minutes 합계를 `Total: N minutes`로 출력해요.
- 일치하는 기록이 없으면 `Total: 0 minutes`를 출력해요.
- `add`, `edit`, `remove`의 성공 문구는 자유이며 대상 ID를 포함합니다.

## Storage

- `STUDY_DATA_FILE`이 설정되어 있으면 해당 경로를 사용해요.
- 없으면 `$HOME/.study.tsv`를 사용해요.
- 둘 다 사용할 수 없으면 경로를 추측하지 않고 오류로 종료해요.
- 설정된 `STUDY_DATA_FILE`이 빈 문자열이면 오류입니다. 상위 디렉터리는 자동 생성하지 않습니다.
- `help`는 데이터 파일을 읽거나 쓰지 않습니다.
- 데이터 파일이 없는 첫 실행은 빈 기록으로 처리하고 `next_id=1`로 시작합니다. 다른 읽기 오류는 실패입니다.
- 첫 줄은 `#study-v1`, `next_id=N` 두 field를 가진 metadata row예요.
- 둘째 줄은 `id`, `date`, `subject`, `minutes`, `note`의 TSV header예요.
- `next_id`는 모든 저장된 ID보다 커야 하는 양의 정수예요. Metadata가 없거나
  이 조건을 어기면 파일이 손상된 것으로 처리해요.
- Header, field 수, 각 값, ID의 양수 여부와 중복도 검증합니다. 빈 note field는 유효합니다.
- Add가 성공적으로 저장될 때 record와 증가한 `next_id`를 같은 임시 파일에
  기록해요. 저장이 실패하면 둘 다 기존 값으로 남아요.
- Edit와 remove는 `next_id`를 바꾸지 않아요. 모든 record를 삭제한 뒤에도
  metadata row는 유지해요.
- 변경 명령은 전체 파일을 읽고 검증한 뒤 임시 파일에 완전히 기록하고
  `rename()`으로 교체해요.
- 손상된 행을 만나면 행 번호를 포함한 오류를 출력하고 exit `1`로 종료하며 원본을 변경하지 않아요.
- 여러 process의 동시 수정과 file locking은 v1 범위 밖이에요.
