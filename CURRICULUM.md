---
scope: Twelve-stage C Workshop curriculum
truth: This file defines stage focus, status, and shared completion gates; each stage README defines behavior
updated: 2026-09-22
---

# Curriculum

단계 번호는 같은 간격의 난이도 점수가 아니에요. 뒤로 갈수록 새 문법보다
여러 상태와 소유권을 한 프로그램 안에서 동시에 유지하는 부담이 커져요.

## Milestones

- **Minimum:** Stage 8을 빈 파일에서 설계하고 객체 수명을 설명해요.
- **Target:** Stage 10의 `study` CLI를 실제 터미널에서 지속해서 사용해요.
- **Extra:** Stage 11–12로 malloc-lab과 PintOS의 핵심 표현을 미리 경험해요.

## Stages

| Stage | Status | Focus | Brief |
| --- | --- | --- | --- |
| 1 | Passed | 함수 포인터의 타입, 교체, 간접 호출 | [Function pointers](practice/01-function-pointers/README.md) |
| 2 | Passed | 구조체 인스턴스별 데이터와 callback | [Struct callbacks](practice/02-struct-callbacks/README.md) |
| 3 | Next | 구조체 주소, `->`, 호출자의 원본 변경 | [Struct pointers](practice/03-struct-pointers/README.md) |
| 4 | Not started | callback에 `self` 전달 | [Self callbacks](practice/04-self-callbacks/README.md) |
| 5 | Not started | heap 객체, deep copy, 생성과 파괴 | [Owned objects](practice/05-owned-objects/README.md) |
| 6 | Not started | `realloc`, `count/capacity`, 동적 배열 | [Dynamic array](practice/06-dynamic-array/README.md) |
| 7 | Not started | 연결 노드, 제거 순서, 전체 정리 | [Linked collection](practice/07-linked-collection/README.md) |
| 8 | Not started | 복수 구조체, policy, 객체 배열과 수명 | [Integrated system](practice/08-integrated-system/README.md) |
| 9 | Not started | `argc/argv`, command parsing, TSV load/save | [Study CLI](projects/study-cli/README.md) |
| 10 | Not started | CRUD, filter, 오류 복구, 실사용 | [Study CLI](projects/study-cli/README.md) |
| 11 | Not started | alignment, block metadata, split/coalesce | [Allocator model](bridges/11-allocator-model/README.md) |
| 12 | Not started | intrusive list, priority, state, callback | [Scheduler model](bridges/12-scheduler-model/README.md) |

## Shared completion gates

Stage 1–8은 다음 조건을 모두 만족해야 통과해요.

1. Workshop warning policy로 컴파일되고 문제 명세의 동작과 경계 사례가 맞아요.
2. Stage 5부터 sanitizer와 Valgrind에서 invalid access와 소유 메모리 leak이 없어요.
3. 이번 단계의 핵심 pointer·state·ownership 관계를 말로 설명할 수 있어요.
4. 작은 입력 또는 요구 변형을 정답 코드 없이 처리할 수 있어요.
5. 도움 수준과 검증 evidence가 `LEARNING_LOG.md`에 기록돼요.

Stage 9–12는 각 brief의 acceptance criteria도 함께 만족해야 해요.

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
