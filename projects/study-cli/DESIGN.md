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

확장 후보 (Stage 10 이후, 계약 밖):

- GitHub 잔디밭처럼 날짜별 기록을 시각화하는 조회. 한 칸은 그날의 total.
- 과목별 합계와 총합을 함께 보여 주는 total (group by).
- yazi 같은 TUI: list와 total을 한 화면에 보여 주고, 과목 분류와 검색을
  UI 안에서 한다. 기록 로직은 그대로 두고 입력과 출력 쪽만 바꾸는 확장.

## 2. 명령 표

<!-- 명령마다: 입력 → 출력 → 실패 조건 (exit code 포함). 여러 문장이면 행을 나누고 명령 칸은 비운다 -->

| 명령 | 입력 | 출력 |
| --- | --- | --- |
| **help** | 없음 | flag와 각 명령어의 작동 방식 |
| **add** | subject, minutes | 기록 하나를 만든다 |
| | date: 기본값은 실행한 날, 명시하면 덮어쓰기 | |
| | note: 커밋 메시지처럼 내용을 남긴다 | |
| **list** | flag가 없으면 전부 (components default) | 고른 기록의 components: ID, date, subject, minutes, note |
| | flag로 특정 과목이나 날짜(하루)를 고를 수 있다 | ID는 edit·remove가 가리키는 번호 |
| | 둘을 함께 주면 둘 다 만족하는 기록만 | |
| **total** | list와 같은 filter | 고른 기록의 minutes 합 |

빈 결과의 출력 문구와 실패 조건은 stage를 마칠 때 README와 대조하는 checklist로 확인한다.

## 3. 경계선

### 3.1 층 구조

```
[interface]  argv 해석, stdout/stderr 출력, exit code     ← 사용자와 맞닿는 쪽
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

### 3.3 Module별 세 질문

<!--
module(파일)마다 세 질문에 답합니다.
1. 무엇 때문에 바뀌나?
2. 무엇을 소유하나? (생성과 해제를 모두 맡는 자원)
3. 누구를 알고, 누구에게 알려지나?
-->

Stage 7을 마친 뒤 `record`와 `main`(interface)마다 채운다.

## 4. Stage별 변화

<!-- stage를 마칠 때마다: 새로 들어온 것 → 생기거나 옮겨진 경계와 그 이유 -->

### Stage 7 진입 (2026-09-29)

grilling으로 정하고 기초 세팅에 적용한 결정. `practice6.c`를 interface(`main.c`)와 core(`record.c`)로 나누면서 경계를 막는 방법을 정했다.

| # | 결정 | 이유 |
| --- | --- | --- |
| Q1 | 구조체 정의를 `record.c`로 숨긴다 (opaque type) | main이 배열이라는 비밀을 알면 core를 바꿀 때 main이 깨진다. 출력 반복문만 남았고, Stage 7 순회가 그것을 대체한 뒤 정의를 옮긴다. 옮긴 뒤 컴파일이 통과하면 경계가 막힌 것이다 |
| Q2 | `new_record` 하나가 배열까지 확보한다 | 생성이 한 번의 호출로 끝나면 호출하는 쪽은 `NULL`만 확인하면 된다 |
| Q3 | core는 출력하지 않는다 | 문구와 출력 위치는 interface의 약속. TUI와 테스트 `main`도 같은 core를 쓴다 |
| Q4 | minutes·subject 검사는 core의 함수 | 유효한 기록의 정의. add 입력, edit 입력, 파일 읽기가 모두 호출한다 |
| Q5 | 함수마다 실패는 한 종류 | 검사 실패는 exit 2, `NULL`은 메모리 부족이라 exit 1. interface가 매핑한다 |
| Q6 | 연속 subject 경고는 interface가 argv만으로 판단 | 입력 습관에 대한 확인이지 기록의 규칙이 아니다. 파일에서는 경고할 이유가 없다 |
