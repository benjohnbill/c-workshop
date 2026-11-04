---
scope: Dated record of study-cli design entries and decisions, moved out of DESIGN.md
truth: Append-only history; DESIGN.md holds the current design and the current stage's worksheet
born: 2026-09-30
---

# study 설계 기록

지난 stage의 진입·진행 기록과 결정표를 모아 둔다. 내용은 DESIGN.md §4에서 그대로 옮겼고, 제목 수준만 한 단계 올렸다. stage를 마치면 DESIGN.md §4의 그 stage 항목을 여기로 옮긴다. 정리본의 4부(Stage 7)는 이 문서의 내용에서 만든다.

## Stage 7 진입 (2026-09-29)

grilling으로 정하고 기초 세팅에 적용한 결정. `practice6.c`를 interface(`main.c`)와 core(`record.c`)로 나누면서 경계를 막는 방법을 정했다.

| # | 결정 | 이유 |
| --- | --- | --- |
| Q1 | 구조체 정의를 `record.c`로 숨긴다 (opaque type) | main이 배열이라는 비밀을 알면 core를 바꿀 때 main이 깨진다. 출력 반복문만 남았고, Stage 7 순회가 그것을 대체한 뒤 정의를 옮긴다. 옮긴 뒤 컴파일이 통과하면 경계가 막힌 것이다 |
| Q2 | `new_record` 하나가 배열까지 확보한다 | 생성이 한 번의 호출로 끝나면 호출하는 쪽은 `NULL`만 확인하면 된다 |
| Q3 | core는 출력하지 않는다 | 문구와 출력 위치는 interface의 약속. TUI와 테스트 `main`도 같은 core를 쓴다 |
| Q4 | minutes·subject 검사는 core의 함수 | 유효한 기록의 정의. add 입력, edit 입력, 파일 읽기가 모두 호출한다 |
| Q5 | 함수마다 실패는 한 종류 | 검사 실패는 exit 2, `NULL`은 메모리 부족이라 exit 1. interface가 매핑한다 |
| Q6 | 연속 subject 경고는 interface가 argv만으로 판단 | 입력 습관에 대한 확인이지 기록의 규칙이 아니다. 파일에서는 경고할 이유가 없다 |

## Stage 7 진행 (2026-09-30)

코드에 들어간 것:

- 구조체 정의가 `record.c`로 옮겨졌다. `record.h`에는 `typedef struct _Record Rec;`처럼 이름만 남았다.
- 순회 한 곳: `record.c`의 `print_result(const Rec *r, result func)`. `result`는 `record.h`의 함수 포인터 typedef이고, main의 `print_input`이 기록마다 불리는 callback이다.
- 아직 남은 것: `list`/`total` 명령 자리 해석, total 합계를 누적할 값의 위치와 소유자.

Q1은 결정과 반대 순서로 적용됐다. 결정은 "순회가 대체한 뒤 정의를 옮긴다"였지만 정의를 먼저 옮겼고, 그 사이의 커밋 `af23ba0`은 `invalid use of incomplete typedef 'Rec'`로 빌드되지 않았다. 이 에러는 경계가 실제로 막혔다는 증거이기도 하다.

도구:

- `lab/split6`의 세 파일을 `archived_*`로 바꿨다. 같은 이름의 `record.h`가 두 곳에 있어서, lab 쪽에 쓴 선언을 study-cli가 읽는다고 착각했다.
- `~/.local/bin/sc`: `make -s` 뒤에 실행한다. `sc ARGS`, `sc dbg ARGS`, `sc vg ARGS`.

### 정리본 계획 (2026-09-30 grilling)

`study-design.html`(블로그 사본 포함)에 Stage 7을 반영하는 방법.

| # | 결정 |
| --- | --- |
| 게시 시점 | Stage 7을 마칠 때. 그 전까지는 이 파일과 `sources/`에 쌓는다 |
| 3부 | "Stage 7 진입 결정"은 진입 시점의 기록으로 고정한다. Stage 7은 새 4부로 추가한다 |
| 인용 | 내 문장은 오타까지 그대로. AI의 답은 Antithese의 증거로 요약하고, AI가 쓴 코드는 싣지 않는다 |
| 출처 | 장마다 "Gemini 대화" 또는 "Claude 세션"을 표기한다. 원문은 `sources/`에 둔다 |
| 흐름 | `DESIGN.md` → `study-design.html` → 블로그 사본. push는 내가 확인한 뒤에 |

4부의 장 후보 (2부와 같은 These / Antithese / Synthese 형식):

| 장 | These (그때 쓴 문장) | 원문 |
| --- | --- | --- |
| 1. 구조체를 숨기는 문법 | "typedef라는 말 없이 struct 뒤에 본명, 그리고 이름 일치시켜주는 느낌으로?" | Gemini Q0–Q3 |
| 2. `record.c`를 include해야 하나 | "그래야 Rec의 정의가 완벽해지니까?", "주소가 0000으로 꽉차있을 것 같은데" | Gemini Q4, Q8–Q10 |
| 3. 두 값을 return해야 하나 | "return이 두 개일 수는 없잖아", "그 함수가 알아서 가공된 name하고 minutes로 바꿔줌" | Gemini Q5–Q7, Q11–Q18 |
| 4. 함수 포인터 typedef 문법 | "*result가 하나의 타입인건가?" | Gemini Q19–Q26 |
| 5. 선언했는데 undeclared, 그다음 link 에러 | "print_result가 19라인에 있잖아." | Gemini Q27, Claude 세션 |

2장과 5장은 이어진다. 2장에서 예측한 link 실패가 5장에서 실제로 일어났다. Q1 순서 역전은 3부 Q1 행에 주석 한 줄로 단다.

열린 질문에 추가할 것: 채워넣기(output parameter) 방식의 확장. 다른 agent와 따로 다루려고 handoff를 만들어 두었다 (Gemini Q16).

Stage 7을 마칠 때 정할 것: 4부 제목, 4부의 "지금의 코드" 스냅숏, 머리말의 날짜·stage 줄, index 카드 문구.

## 방향 전환 (2026-09-30)

grilling으로 정한 결정. 프로그램의 최종 모습을 "CLI로 기록하고 TUI로 조회"로 정하고, stage를 그 목표 아래의 확인 지점으로 두었다.

| # | 결정 | 이유 |
| --- | --- | --- |
| Q1 | TUI의 목적은 상호작용 탐색, 한 화면에 여러 정보, C로 터미널 프로그램을 만드는 경험 | §1의 목적(기록하는 재미, 성취감을 눈으로 확인, C 이해도)과 맞다. 입력 편의는 `add` 한 줄로 충분하다 |
| Q2 | 열어 보고 닫는다 | 시작할 때 한 번 읽으면 CLI와 process 모델이 거의 같다 |
| Q3 | 조회 전용, 쓰기는 CLI만 | 입력 폼과 UTF-8 편집이 빠지고, 쓰는 프로그램이 하나라 동시 수정 문제가 없다 |
| Q4 | Stage 10 직후에 시작하고, TUI까지가 프로젝트의 끝. allocator·scheduler 모형은 미룬다 | 하나의 프로그램을 끝까지 만드는 것이 목표다 |
| Q5 | 한 화면: 위 잔디밭, 아래 list, 하단 total 줄. 잔디밭에서 고른 날짜가 list를 필터 | 탐색이 잔디밭과 list의 연동으로 드러나고, pane 사이 포커스 관리가 없다 |
| Q6 | 과목 필터는 저장된 목록에서 고른다 | 문자열 입력(UTF-8 편집)이 다시 들어오지 않는다 |
| Q7 | 날짜별 집계는 TUI가 순회 callback 안에서 한다 | Stage 7의 순회와 함수 포인터가 그 용도다. 두 번째 client가 같은 집계를 원할 때 core로 올린다 |
| Q8 | `termios`·ANSI·`wcwidth`로 직접 제어 | 새 의존성이 없고, 터미널 프로그램을 만드는 경험이 목적이다. "상태 → 프레임"과 "프레임 → 터미널"을 나눈다 |
| Q9 | 별도 실행 파일 `study-tui`, core와 storage를 공유 | CLI의 명령 계약이 그대로이고, CLI가 터미널 제어 코드와 함께 build되지 않는다 |
| Q10 | Stage 8부터 core와 storage는 `exit`하거나 직접 출력하지 않는다 | TUI가 그대로 호출할 수 있어야 한다. 확인은 공통 완료 조건 6(`nm -u`) |
