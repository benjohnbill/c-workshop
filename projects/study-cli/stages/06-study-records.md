---
scope: Stage 6 behavior specification
truth: This file defines this version's behavior and required practice; implementation is learner-owned
updated: 2026-09-23
---

# Stage 6 — Study Records

## Usage

1. 한 번 실행할 때 과목과 공부 시간의 쌍을 여러 개 전달합니다.
2. 각 쌍은 별도 기록으로 입력 순서대로 표시됩니다. 같은 과목도 합치지 않습니다.
3. 기록은 이번 실행에서만 유지되며 다음 실행으로 이어지지 않습니다.

소스는 [study-cli](../)에서 단일 C 파일로 시작합니다. 아래 `main.c`는 예시 파일명입니다.

## Try it

```sh
c main.c C 30 OS 45
c main.c "C pointers" 20 자료구조 40 C 10 C 15
c main.c
```

두 번째 실행에서 `C` 기록이 두 개 따로 표시되는지, 마지막 실행에서 `No entries.`가 나오는지 확인합니다. 출력 꾸밈은 자유입니다.

## Behavior

- 입력은 `SUBJECT MINUTES` 쌍의 반복입니다. [공통 입력 규칙](../README.md#shared-contract)을 적용합니다.
- 기록 수를 늘려도 앞서 입력한 기록의 내용과 순서가 유지됩니다.
- 짝이 맞지 않거나 값이 잘못되면 오류로 종료하며, 일부 기록만 정상 결과처럼 출력하지 않습니다.
- 메모리 확보에 실패하면 오류를 알리고 확보한 자원을 정리합니다.
- 파일 저장, 날짜, ID, 메모는 아직 다루지 않습니다.

필수 연습: 구조체로 기록을 표현하고, 과목 문자열의 사본을 소유합니다.
배열은 `count/capacity`를 구분하고 `realloc`으로 확장합니다. 확장 실패 시에도
기존 기록은 유효해야 합니다. 구체적인 구조체와 함수 설계는 직접 결정합니다.

## Done when

- 빈 입력, 한 기록, 초기 용량을 여러 번 넘는 입력으로 내용과 순서를 확인합니다.
- `C`, `C nope`, `C 0`, `C 1441`은 오류이며 `C 30`은 정상입니다.
- 생성에 사용한 문자열을 바꿔도 보관된 기록은 유지되는지 작은 검증으로 확인합니다.
- 정상·실패 경로의 메모리 검사와 [공통 완료 조건](../../../CURRICULUM.md#shared-completion-gates)을 통과합니다.

다음 버전: [list와 total](07-list-and-total.md).
