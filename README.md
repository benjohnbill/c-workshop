---
scope: C Workshop repository overview
truth: CURRICULUM.md defines current stages and completion gates
updated: 2026-09-23
---

# C Workshop

구조체·함수 포인터·메모리 소유권을 연습하고, 하나의 `study` CLI를 단계적으로
만들며 C에 익숙해지는 작업장입니다. 각 버전을 터미널에서 직접 사용해 검증합니다.

## Goals

- **Minimum — Stage 8:** 기록을 저장하고 다른 실행에서 다시 읽는 프로그램을
  만들고, 구조체·메모리·파일의 수명을 설명합니다.
- **Target — Stage 10:** 터미널에서 실제로 사용하는 `study` CLI를 완성해요.
- **Extra — Stage 12:** malloc-lab과 PintOS에서 다시 만날 표현을 작은 모형으로
  먼저 다뤄요.

전체 순서와 통과 기준은 [CURRICULUM.md](CURRICULUM.md)에 있어요. 코드에서
드러나지 않는 학습 근거는 [LEARNING_LOG.md](LEARNING_LOG.md)에 남겨요.

## Workflow

각 단계 폴더의 `README.md`를 문제 명세로 읽고, 소스 파일과 필요한 모듈은
직접 만들어요. 단계별 문서에는 정답 코드와 함수 원형이 들어 있지 않아요.
Stage 6–10은 `projects/study-cli/`에서 같은 코드베이스를 확장합니다.
Stage 6–10 brief는 이번 기능, 터미널 사용 예시, 동작 조건, 완료 확인으로 구성합니다.

Stage 1–6의 단일 파일은 개인 compile wrapper를 사용해요.

```sh
c main.c
c dbg main.c
```

`c dbg`는 런타임 상태를 확인할 이유가 있을 때만 사용해요. GDB 명령 수행
자체는 단계 통과 조건이 아니에요. 동적 메모리를 쓰기 시작하면 sanitizer와
Valgrind 검증을 별도로 실행해요.

## Repository map

- `practice/`: Stage 1–5 연습과 Stage 6–8의 버전별 명세
- `projects/study-cli/`: Stage 6–10의 구현 위치와 공통 계약, Stage 9–10 명세
- `bridges/`: malloc-lab과 PintOS를 위한 Stage 11–12 모형
- `CURRICULUM.md`: 앞으로 갈 지도와 단계 상태
- `LEARNING_LOG.md`: 실제로 확인한 이해와 코드 근거

현재 단계와 다음 문제는 `CURRICULUM.md`의 `Status` 열에서 한 곳에서만 관리해요.
