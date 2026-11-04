---
scope: The learner's own design notes for study-cli
truth: README.md and the stage briefs define behavior; this file records his reading of them and his design decisions
born: 2026-09-29
---

# study 설계

숙지할 개념은 [CURRICULUM.md](../../CURRICULUM.md)의 stage별 focus를 따릅니다.

## 1. study가 하는 일

만드는 이유: 실제 프로젝트를 통한 직접 경험. C 문법(구조체, 함수 포인터,
표준 라이브러리 등)에 대한 이해도 향상.

- **누가 쓰는가**: 하루하루 공부한 바를 간단하게 기록하고, 나중에 그 기록을
  가공하거나 표·그래프 같은 시각적인 형태로 보고 싶은 사람.
- **언제 쓰는가**: 하루를 마무리할 때 꾸준히 기록한다. journal이나 캘린더와
  역할이 비슷하다.
- **무엇을 위해 쓰는가**: 기록하는 재미를 느끼고, 성취감을 눈으로 확인하기
  위해.

Stage 11의 목표 (조회 전용, 기록은 CLI):

- 날짜별 잔디밭(한 칸은 그날의 total)과 list, total을 한 화면에 보여 주는
  `study-tui`. 기록 로직은 그대로 두고 조회 쪽만 더하는 별도 실행 파일.

확장 후보 (Stage 11 이후, 계약 밖):

- 과목별 합계와 총합을 함께 보여 주는 total (group by).

## 2. 명령 표

<!-- 명령마다: 입력 → 출력 → 실패 조건 (exit code 포함). 여러 문장이면 행을 나누고 명령 칸은 비운다 -->

| 명령 | stage | 입력 | 출력 | 실패 조건 |
| --- | --- | --- | --- | --- |
| **help** | 9 | 없음 | flag와 각 명령어의 작동 방식 | |
| **add** | 9 | subject, minutes | 기록 하나를 만든다 | |
| | | date: 기본값은 실행한 날, 명시하면 덮어쓰기 | | |
| | | note: 커밋 메시지처럼 내용을 남긴다 | | |
| **list** | 9 | flag가 없으면 전부 (components default) | 고른 기록의 components: ID, date, subject, minutes, note | |
| | 10 | flag로 특정 과목이나 날짜(하루)를 고를 수 있다 | ID는 edit·remove가 가리키는 번호 | |
| | 10 | 둘을 함께 주면 둘 다 만족하는 기록만 | | |
| **total** | 9 (filter는 10) | list와 같은 filter | 고른 기록의 minutes 합 | |
| **edit** | 10 | | | |
| **remove** | 10 | | | |
| **study-tui** | 11 | | | |

`stage` 열은 처음 생기는 stage다. 정의는 stage 명세와 README가 맡고, 이 표에는 내가 읽은 대로 적는다. Stage 6–8의 임시 명령(`save PATH …`, `list PATH`)은 stage 명세가 정의하므로 넣지 않는다. 빈 결과의 출력 문구와 실패 조건은 내 해석을 적은 뒤 stage를 마칠 때 README와 대조하는 checklist로 확인한다.

### 2.2 데이터

<!-- 필드 목록만 적는다. 구조체 배치와 파일의 열 순서는 stage에서 내가 정한다. 규칙의 원문: README의 Shared contract, Data rules, Storage -->

| 필드 | 처음 생기는 stage | 값의 규칙 | 남는 곳 |
| --- | --- | --- | --- |
| subject | 6 | 비어 있지 않고 tab·CR·LF가 없다 | 6–7 메모리, 8 파일(TSV), 9~ 파일(v1) |
| minutes | 6 | 십진 정수 1–1440 | 6–7 메모리, 8 파일(TSV), 9~ 파일(v1) |
| id | 9 | 양의 정수. 삭제한 뒤에도 재사용하지 않는다 | 9~ 파일(v1) |
| date | 9 | 실제로 있는 YYYY-MM-DD. 기본값은 실행한 날 | 9~ 파일(v1) |
| note | 9 | 빈 문자열 가능. tab·CR·LF가 없다 | 9~ 파일(v1) |
| next_id | 9 | 저장된 모든 ID보다 큰 양의 정수 | 9~ 파일의 첫 줄(metadata) |

규칙의 원문은 [Shared contract](README.md#shared-contract), [Data rules](README.md#data-rules), [Storage](README.md#storage)에 있다.

## 3. 경계선

### 3.1 층 구조

```
[interface]  study: argv 해석, stdout/stderr 출력, exit code        ← 사용자와 맞닿는 쪽
             study-tui: 화면·키·터미널 복원 (Stage 11, 조회 전용)
     │ 호출
     ▼
[core]       기록 모음과 그 조작 (C·R·U·D)                ← 프로그램의 핵심 지식
     ▲ 호출
     │
[storage]    파일 읽기·쓰기                               ← Stage 8부터
```

- 함수는 동작 하나. module은 비밀(바깥이 몰라도 되는 결정) 하나를 공유하는
  함수들의 묶음.
- 변경 시험: "이 결정을 바꾸면 무엇을 같이 고치나?" 같이 고치는 함수들이 한
  module.
- 호출 방향: interface와 storage가 core를 부른다. core는 둘 다 모른다.
- CRUD는 module을 나누는 기준이 아니다. 네 조작 모두 기록의 모양을 알아야
  하므로 core에 함께 있다.

### 3.2 Stage별 요구 지도

brief가 요구하는 것만 적는다. 함수를 어디에 둘지는 3.3에서 정한다.

| Stage | interface | core | storage |
| --- | --- | --- | --- |
| **6** | argv를 과목·시간 쌍으로 해석, 전체 출력 | C (add), R (전체) | 없음 |
| **7** | command 자리 해석 (`list`, `total`) | C, R (순회 한 곳 + 함수 포인터로 기록별 동작: 목록, 합계) | 없음 |
| | 필수: interface와 core를 별도 module로 분리 | | |
| **8** | `save`, `list PATH`, `total PATH` | C, R | TSV(subject, minutes) 쓰기·읽기, 손상된 행 거부 |
| | | | 필수: `FILE *` 입출력을 별도 module로 |
| **9** | option(`--subject` 등) 해석, `help` | C (ID·date·note 부여), R | v1 형식(`next_id`, header), 임시 파일 + `rename()` 저장 |
| **10** | `edit`, `remove`, filter option | U, D, R + filter, ID로 찾기 | 9와 같음 |
| | 단위 테스트: core와 storage를 argv 없이 검증 | | |
| **11** | `study-tui`: 화면·키·종료 복원 | R (순회 callback으로 날짜별 집계) | 읽기만 |

### 3.3 Module별 세 질문

<!--
module(파일)마다 세 질문에 답합니다.
1. 무엇 때문에 바뀌나?
2. 무엇을 소유하나? (생성과 해제를 모두 맡는 자원)
3. 누구를 알고, 누구에게 알려지나?
-->

Stage 7을 마친 뒤 `record`와 `main`(interface)마다 채운다.

초안(2026-10-01): Claude가 현재 코드와 `nm -u`로 확인해 적었다. 내 말로 확인하기 전이다.

| module | 무엇 때문에 바뀌나 | 무엇을 소유하나 | 누구를 알고, 누구에게 알려지나 |
| --- | --- | --- | --- |
| `main.c` (interface) | 명령 형식, 출력 문구, exit code. stage마다 바뀐다. | `Rec` 한 개의 수명(`new_record`를 한 번 부르고 끝에서 `record_free`). 파일은 열지 않는다. | `record.h`와 `storage.h`의 선언을 안다. `Rec`과 `Sub`는 이름뿐이라 내부 모양은 모른다(멤버 접근 없음). 프로그램의 진입점이라서 이 파일을 부르는 곳은 없다. |
| `record.c` (core) | 기록을 담는 자료구조(지금은 동적 배열)를 바꿀 때: 함수 8개 중 6개의 본문이 바뀌고 선언은 그대로다. 유효한 기록의 정의(과목 이름 규칙, minutes 1–1440)를 바꿀 때: `valid_subject`, `minutes_parse`. | `Rec`, 그 안의 배열, 기록마다 `Sub`와 `name` 문자열(복사본). 생성은 `new_record`와 `Sub_add`, 해제는 `record_free` 한 곳이다. | 표준 라이브러리(`malloc`, `realloc`, `free`, `memcpy`, `strlen`, `strpbrk`)만 안다. 출력, 종료, 파일, argv는 모른다(`nm -u record.o`, 2026-10-01). `main.c`와 `storage.c`가 `record.h`를 통해 호출한다. |

Stage 8에 진입할 때 storage도 채운다. storage와 core의 답은 변경 시험(3.1)과 "`study-tui`가 고치지 않고 부를 수 있는가"로 확인한다(공통 완료 조건 6).

## 4. Stage별 변화

<!-- stage를 마칠 때마다: 새로 들어온 것 → 생기거나 옮겨진 경계와 그 이유 -->
<!-- stage 진입 항목의 틀: 질문에 내 말로 답하고, 마칠 때 어긋났던 답을 '확인'에 적는다. 다음 stage는 Stage 8 항목을 복사해 stage 고유 질문(4번)만 바꾼다. 힌트와 코드는 적지 않는다. -->

지난 stage의 진입·진행 기록과 결정표는 [DESIGN-LOG.md](DESIGN-LOG.md)에 있다. stage를 마치면 그 stage의 항목을 옮긴다.

### Stage 8 진입 (     )

질문에 내 말로 답한다. 답은 명세와 실제 출력으로 확인하고, 어긋났던 것은 마칠 때 아래 "확인"에 적는다.

| # | 질문 | 내 답 |
| --- | --- | --- |
| 1 | 예측·재진술: 이번 stage가 요구하는 동작은? 어디서 실패할 것 같고, 놓치기 쉬운 조건은? | |
| 2 | 상태 그림: `list PATH` 한 번 실행 동안 파일, 읽기 버퍼, 기록은 각각 언제 생기고 언제 사라지나? | |
| 3 | 후보 전략: 이 stage의 핵심 문제(읽기 버퍼와 기록의 수명)를 푸는 방법의 후보와 비교. 무엇을 골랐고 왜인가? | |
| 4 | stage 고유: `list PATH`에서는 argc가 더는 빈 목록을 뜻하지 않는다. "기록이 없다"는 어디서 판단하나? | |
| 5 | 실패 지점: 실패가 날 수 있는 지점마다, 그때 열려 있는 것(파일, 메모리)은? | |
| 6 | 증거: 가설을 무엇으로 확인하나? (출력, 컴파일러, Valgrind, 필요할 때 디버거) | |
| 7 | 스트레스: 무엇이 이 설계를 깨뜨리나? (명세의 Done when 항목을 참고) | |
| 8 | 경계: storage의 세 질문과 두 시험 | 3.3에 적는다 |

**확인** (stage를 마칠 때): 어긋났던 답 → 고친 이해
