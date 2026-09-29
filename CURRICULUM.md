---
scope: Twelve-stage C Workshop curriculum
truth: This file defines stage focus, status, and shared completion gates; each stage README defines behavior
updated: 2026-09-29
---

# Curriculum

단계 번호는 같은 간격의 난이도 점수가 아니에요. 뒤로 갈수록 새 문법보다
여러 상태와 소유권을 한 프로그램 안에서 동시에 유지하는 부담이 커져요.

Stage 1–5에서 익힌 구조체·함수 포인터·소유권을 Stage 6–10의 하나의 `study`
프로그램에서 반복해서 사용합니다. 각 버전을 터미널에서 검증하고 같은 코드를
확장합니다. 개념 설명은 필요할 때 다루며, brief는 기능과 완료 조건을 정의합니다.

## Milestones

- **Minimum:** Stage 8에서 기록을 저장하고 다른 실행에서 읽으며 객체 수명을 설명해요.
- **Target:** Stage 10의 `study` CLI를 실제 터미널에서 지속해서 사용해요.
- **Extra:** Stage 11–12로 malloc-lab과 PintOS의 핵심 표현을 미리 경험해요.

## Stages

| Stage | Status | Focus | Brief |
| --- | --- | --- | --- |
| 1 | Passed | 함수 포인터의 타입, 교체, 간접 호출 | [Function pointers](practice/01-function-pointers/README.md) |
| 2 | Passed | 구조체 인스턴스별 데이터와 callback | [Struct callbacks](practice/02-struct-callbacks/README.md) |
| 3 | Passed | 구조체 주소, `->`, 호출자의 원본 변경 | [Struct pointers](practice/03-struct-pointers/README.md) |
| 4 | Deferred | callback에 `self` 전달 | [Self callbacks](practice/04-self-callbacks/README.md) |
| 5 | Deferred | heap 객체, deep copy, 생성과 파괴 | [Owned objects](practice/05-owned-objects/README.md) |
| 6 | Passed | 인자로 기록 입력, 구조체·deep copy·동적 배열 | [Study Records](practice/06-dynamic-array/README.md) |
| 7 | Next | list·total, module 분리, 함수 포인터로 처리 동작 전달 | [List and Total](practice/07-linked-collection/README.md) |
| 8 | Not started | TSV 저장·불러오기, 읽기 버퍼와 기록의 수명, 실패 경로 정리 | [Save and Load](practice/08-integrated-system/README.md) |
| 9 | Not started | 정식 명령·옵션 검증, ID·날짜·메모, 안전한 저장 | [Daily CLI](projects/study-cli/README.md#stage-9--daily-cli) |
| 10 | Not started | 수정·삭제·필터, 오류 복구, 통합 테스트와 실사용 | [Edit and Filter](projects/study-cli/README.md#stage-10--edit-and-filter) |
| 11 | Not started | alignment, block metadata, split/coalesce | [Allocator model](bridges/11-allocator-model/README.md) |
| 12 | Not started | intrusive list, priority, state, callback | [Scheduler model](bridges/12-scheduler-model/README.md) |

Stage 6–10의 구현 위치는 `projects/study-cli/`입니다. 기존 학습자 파일을
보존하기 위해 Stage 6–8 brief의 경로는 유지합니다. 연결 리스트와 배송 센터는
CLI 필수 경로에서 제외합니다. Stage 12에 진입할 때 필요한 연결 리스트 기초를
확인하고 보충하며, Stage 11–12는 선택 확장입니다.

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

개인 `c` wrapper는 C17과 엄격한 warning, `-g3 -O0`으로 컴파일해요. Stage 7에
진입할 때 multi-file build가 필요하므로 wrapper 확장은 그 시점의 별도 작업으로
판단해요. 그 전에는 wrapper를 바꾸지 않아요.

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
