---
scope: Stage 1–5 drills and the Stage 6–11 study program: focus, status, shared completion gates
truth: This file defines stage focus, status, and shared completion gates; each stage brief defines behavior
updated: 2026-09-30
---

# Curriculum

단계 번호는 같은 간격의 난이도 점수가 아니에요. 뒤로 갈수록 새 문법보다
여러 상태와 소유권을 한 프로그램 안에서 동시에 유지하는 부담이 커져요.

Stage 1–5에서 익힌 구조체·함수 포인터·소유권을 Stage 6–11의 하나의 `study`
프로그램에서 반복해서 사용합니다. Stage 6–11은 프로그램이 할 수 있는 일이
늘어나는 확인 지점이고, 최종 모습은 기록을 CLI로 남기고 TUI로 조회하는 하나의
프로그램이에요. 각 버전을 터미널에서 검증하고 같은 코드를 확장합니다. 개념
설명은 필요할 때 다루며, brief는 기능과 완료 조건을 정의합니다.

## Milestones

- **Minimum:** Stage 8에서 기록을 저장하고 다른 실행에서 읽으며 객체 수명을 설명해요.
- **Usable:** Stage 10의 `study` CLI를 실제 터미널에서 지속해서 사용해요.
- **Target:** Stage 11의 `study-tui`로 같은 기록을 조회해요. 프로젝트는 여기서 끝나요.
- **Deferred extension:** allocator·scheduler 모형(malloc-lab, PintOS 대비)은 Target 이후에 정해요.

## Stages

| Stage | Status | Focus | Brief |
| --- | --- | --- | --- |
| 1 | Passed | 함수 포인터의 타입, 교체, 간접 호출 | [Function pointers](practice/01-function-pointers/README.md) |
| 2 | Passed | 구조체 인스턴스별 데이터와 callback | [Struct callbacks](practice/02-struct-callbacks/README.md) |
| 3 | Passed | 구조체 주소, `->`, 호출자의 원본 변경 | [Struct pointers](practice/03-struct-pointers/README.md) |
| 4 | Deferred | callback에 `self` 전달 | [Self callbacks](practice/04-self-callbacks/README.md) |
| 5 | Deferred | heap 객체, deep copy, 생성과 파괴 | [Owned objects](practice/05-owned-objects/README.md) |
| 6 | Passed | 인자로 기록 입력, 구조체·deep copy·동적 배열 | [Study Records](projects/study-cli/stages/06-study-records.md) |
| 7 | Passed | list·total, module 분리, 함수 포인터로 처리 동작 전달 | [List and Total](projects/study-cli/stages/07-list-and-total.md) |
| 8 | Next | TSV 저장·불러오기, 읽기 버퍼와 기록의 수명, 실패 경로 정리 | [Save and Load](projects/study-cli/stages/08-save-and-load.md) |
| 9 | Not started | 정식 명령·옵션 검증, ID·날짜·메모, 안전한 저장 | [Daily CLI](projects/study-cli/stages/09-daily-cli.md) |
| 10 | Not started | 수정·삭제·필터, 오류 복구, 통합 테스트와 실사용 | [Edit and Filter](projects/study-cli/stages/10-edit-and-filter.md) |
| 11 | Not started | 조회 전용 TUI: 상태→프레임 분리, 터미널 복원, 한글 표시 폭 | [Terminal Viewer](projects/study-cli/stages/11-terminal-viewer.md) |

Stage 6–11의 구현 위치는 `projects/study-cli/`입니다. 연결 리스트와 배송 센터는
CLI 필수 경로에서 제외해요. 아래 확장은 Target 이후에 정하며, 진입할 때 필요한
연결 리스트 기초를 확인하고 보충해요.

| Extension | Status | Focus | Brief |
| --- | --- | --- | --- |
| Allocator model | Deferred | alignment, block metadata, split/coalesce | [Allocator model](bridges/allocator-model/README.md) |
| Scheduler model | Deferred | intrusive list, priority, state, callback | [Scheduler model](bridges/scheduler-model/README.md) |

## Review exercises

| Exercise | Status | Focus | Brief |
| --- | --- | --- | --- |
| Stage 5.5 | Passed | 원본과 독립적인 문자열 소유권, 정상 경로 정리 | [Owned string](practice/review-03-05/README.md) |

## Shared completion gates

각 단계는 해당 brief의 완료 조건과 다음 조건을 모두 만족해야 통과해요.

1. Workshop warning policy로 컴파일되고 문제 명세의 동작과 경계 사례가 맞아요.
2. Stage 5부터 sanitizer와 Valgrind에서 invalid access와 소유 메모리 leak이 없어요.
3. 이번 단계의 핵심 pointer·state·ownership 관계를 말로 설명할 수 있어요.
4. 작은 입력 또는 요구 변형을 정답 코드 없이 처리할 수 있어요.
5. 도움 수준과 검증 evidence가 `LEARNING_LOG.md`에 기록돼요.
6. Stage 8부터 record·file 로직을 담은 object file에는 실행 중단이나 출력 호출이
   없어요. Makefile의 한 변수(`LOGIC_OBJS`)에 그 object들을 적고, 목록의 모든
   object에 `nm -u`를 적용했을 때 `exit`, `_exit`, `_Exit`, `abort`, `printf`,
   `__printf_chk`, `vprintf`, `puts`, `putchar`, `perror`, `err`, `errx`, `warn`,
   `warnx`, `stdout`, `stderr`, `__assert_fail`이 나오지 않아야 해요. 목록에 없는
   object는 interface object(`main`을 정의하는 것, 인자 해석, 결과·help 출력,
   terminal 그리기)여야 하고, 통과 항목의 Evidence에 그 이름을 적어요. Stage 11부터
   `LOGIC_OBJS`는 `study`와 `study-tui`가 함께 링크하는 object 전부예요. 실패는
   호출한 쪽에 돌려주고, message와 exit status는 그쪽이 정해요. 자신이 연
   `FILE *`이나 caller가 넘긴 `FILE *`에 쓰는 것은 허용해요.

새 기능의 필요성을 느끼면 다음 brief를 살펴볼 수 있습니다. 기능을 미리
구현한 경우에도 단계 통과는 해당 조건의 검증 근거로 판단합니다.

## Assistance scale

학습 로그는 완성 여부뿐 아니라 완성까지 필요했던 도움을 다음 값으로 구분해요.

| Value | Meaning |
| --- | --- |
| `independent` | 문제 명세만 보고 설계·구현·검증함 |
| `clarification` | 언어·도구 사실만 직접 답변받음 |
| `conceptual-hint` | 다음에 생각할 개념이나 상태를 안내받음 |
| `concrete-hint` | 확인할 위치나 필요한 다음 동작을 안내받음 |
| `direct-fix` | 잘못된 줄이나 대체 코드를 직접 제공받음 |

이 값은 평가 점수가 아니라 다음 tutor가 설명의 시작점을 정하기 위한 근거예요.

## Build policy

Stage 1–6의 단일 파일은 다음 명령을 기본으로 사용해요.

```sh
c FILE.c
c dbg FILE.c
```

프로그램 인자는 파일명 뒤에 붙입니다. 예: `c main.c C 30 OS 45`.

Stage 7부터 `study`는 `projects/study-cli/`의 Makefile로 build하고, `sc`가 build 후
실행해요(`sc ARGS`, `sc dbg ARGS`, `sc vg ARGS`). 개인 `c` wrapper는 C17과 엄격한
warning, `-g3 -O0`으로 컴파일하는 단일 파일 전용으로 유지해요. `study-tui`를 실행하는
방법은 Stage 11에 진입할 때 정해요.

## Debugging policy

GDB는 필수 의식이 아니라 runtime 가설을 검증하는 evidence 도구예요.

- compiler error와 warning은 실행 전 단계에서 먼저 해결해요.
- 실행 결과가 예상한 pointer, ownership, callback 또는 자료구조 상태와 다를 때
  `c dbg`를 사용해요.
- sanitizer나 Valgrind가 찾은 메모리 문제의 상태와 호출 흐름을 더 조사할 때
  GDB를 사용할 수 있어요.
- 어떤 단계도 정해진 GDB 명령 수행을 통과 조건으로 요구하지 않아요.

GDB를 썼다면 명령 transcript 대신 확인하거나 기각한 가설을 learning log의
`Evidence`에 남겨요.
