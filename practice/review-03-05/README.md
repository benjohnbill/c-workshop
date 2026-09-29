---
scope: Stage 5.5 ownership checkpoint before the Study CLI
truth: This file defines the agreed completion boundary for this review
updated: 2026-09-23
---

# Stage 5.5 — Owned String

## This version

구조체가 문자열의 독립적인 사본을 소유하는지 확인합니다. 원본 입력을
수정한 후에도 사본은 처음 내용을 유지해야 합니다. 6번에서는 같은 소유권
관계를 여러 공부 기록으로 확장합니다.

## Try it

`practice/` 디렉터리에서는 다음처럼 실행합니다.

```sh
c review-03-05/extra_practice.c
```

원본을 `original`에서 `changed`로 바꾼 뒤, 저장된 문자열에는 여전히
`original`이 보여야 합니다. 출력 형식은 자유입니다.

## Behavior

- 지역 문자 배열에서 구조체가 소유할 별도 문자열 공간으로 내용과 `\0`을 복사합니다.
- 원본 배열을 수정해도 구조체에 저장된 문자열은 바뀌지 않습니다.
- 정상 종료에 소유한 문자열과 구조체를 모두 정리합니다.

## Done when

- 복사본과 변경된 원본을 같은 실행에서 확인합니다.
- 포인터 주소만 바꾼 경우와 실제 문자를 복사한 경우를 구분해 설명합니다.
- 정상 실행 경로의 workshop warning policy, sanitizer, Valgrind 검사를 통과합니다.

이 checkpoint의 통과 범위는 소유 문자열의 독립성과 정상 경로 정리입니다.
할당 실패 복구는 [Stage 6](../06-dynamic-array/README.md), 문자열 교체는
[Stage 10](../../projects/study-cli/README.md#stage-10--edit-and-filter)에서 확인합니다.
타이머 callback은 [Stage 4](../04-self-callbacks/README.md)의 별도 과제입니다.
