---
scope: Stage 11 behavior specification
truth: This file defines the read-only terminal viewer; the data file contract is the Storage section of ../README.md
updated: 2026-09-30
---

# Stage 11 — Terminal Viewer

## Usage

1. `study add`로 기록을 남깁니다. 기록은 CLI만 바꿉니다.
2. `study-tui`를 실행해 같은 데이터 파일의 기록을 한 화면에서 조회하고, 종료 키로 닫습니다.
3. `study-tui`는 별도 실행 파일이며 데이터 파일을 쓰지 않습니다.

## Try it

    export STUDY_DATA_FILE="$(mktemp -d)/study.tsv"
    ./study add --subject C --minutes 30 --date 2026-09-23 --note "pointer review"
    ./study add --subject 자료구조 --minutes 45 --date 2026-09-24
    ./study-tui

화면에서 두 날짜의 칸과 기록 두 줄, 합계 75분을 확인하고 종료 키로 나옵니다. 실제 데이터 파일(`$HOME/.study.tsv`)로도 열어 봅니다. Stage 10 이후 `study`를 계속 쓰면 잔디밭에 실제 기록이 보입니다.

## Behavior

- 데이터 경로와 파일 형식은 [Storage](../README.md#storage)를 따릅니다. 시작할 때 파일 전체를 한 번 읽고 검증합니다.
- 파일이 없으면 빈 list와 `Total: 0 minutes`를 보여 주고, 종료 키로 exit `0`으로 끝납니다. 이때 파일을 만들지 않습니다.
- 손상된 파일과 읽기 실패는 화면을 켜기 전에 행 번호를 담은 오류를 stderr에 출력하고 exit `1`로 종료합니다.
- 표준 입출력이 terminal이 아니면 escape sequence를 하나도 쓰기 전에 stderr로 알리고 0이 아닌 exit status로 끝납니다.
- UTF-8 locale을 쓸 수 없으면 화면을 켜기 전에 stderr로 알리고 exit `1`로 끝납니다.
- 한 화면입니다. 위에는 날짜별 잔디밭(칸 하나가 그날의 total), 아래에는 선택한 날짜·과목의 기록 list, 하단 줄에는 보이는 기록의 total이 항상 있습니다. 잔디밭에서 고른 날짜가 list를 필터합니다.
- 과목 필터는 저장된 과목 목록에서 고릅니다. 문자열 입력은 없습니다.
- 데이터 파일과 그 디렉터리에 아무것도 만들거나 바꾸지 않습니다.
- 한글 과목이 열을 깨뜨리지 않습니다(표시 폭 2칸). 화면 크기가 바뀌면 다시 그리고, 너무 작으면 그 사실을 화면에 알립니다.
- 정상 종료, 종료 키, SIGINT, SIGTERM, 실행 중 오류 모두 터미널 상태를 실행 전과 같게 되돌립니다.
- 키 배치, 잔디밭의 농도 구간과 기간, 색 표현은 직접 정합니다.

필수 연습: `termios`와 ANSI escape sequence로 터미널을 직접 제어합니다. "상태에서 프레임 문자열을 만드는 부분"과 "프레임을 터미널에 쓰는 부분"을 분리합니다. 날짜별 집계는 기록을 순회하는 callback에서 만듭니다. `study-tui`는 별도 실행 파일이며, 기록 관리와 파일 입출력 소스를 `study`와 공유합니다. 공유 소스를 바꿨다면 그 이유를 학습 로그의 Evidence에 적습니다.

## Done when

- 프레임을 만드는 부분을 문자열 비교로 검증합니다(빈 목록, 한글 과목, 좁은 화면 포함). 이 검증도 UTF-8 locale에서 실행합니다.
- pseudo-terminal에서 실행해 종료 키, 다른 process가 보낸 `kill -INT`, `kill -TERM` 뒤에 1초 안에 끝나고 `stty -g` 출력이 실행 전과 같음을 확인합니다. raw mode에서는 Ctrl-C 키가 신호를 만들지 않으므로 신호는 `kill`로 보냅니다.
- pseudo-terminal의 크기를 바꾼 뒤(`TIOCSWINSZ`) 마지막으로 쓴 프레임(화면 지우기 같은 앞뒤 제어 문자열은 제외)이 새 크기에 대한 프레임 함수의 결과와 같습니다.
- 데이터 파일을 0444, 그 디렉터리를 0555로 두고 실행해도 정상 동작하고, 실행 전후에 파일이 byte 단위로 같습니다. 파일이 없는 경로에서는 실행 뒤에도 파일이 없습니다.
- 손상된 파일, terminal이 아닌 입출력(`</dev/null`, `| cat`), UTF-8이 아닌 locale에서 raw mode에 들어가기 전에 끝납니다.
- Stage 10의 통합 테스트와 단위 테스트가 Stage 11의 build에서 다시 통과합니다.
- 같은 데이터 파일에서 날짜 D와 과목 S를 고른 프레임의 total 줄에 보이는 분 값이 `study total --date D --subject S`가 출력한 분 값과 같습니다.
- Sanitizer·Valgrind와 [공통 완료 조건](../../../CURRICULUM.md#shared-completion-gates)을 통과합니다. terminal이 필요한 검증은 pseudo-terminal에서 실행합니다.
