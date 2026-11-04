---
scope: 2분 발표 "C에서 객체지향 프로그래밍하기"의 목차와 대본 초안
status: deck built (2026-10-01), 리허설 전
deck: oop-in-c.html (공개 사본: benjohnbill.github.io/study/week05/oop-in-c.html)
source: projects/study-cli @ 4010305 (줄 번호는 이 커밋 기준)
---

# OOP in C: 2-minute talk

## Decisions

| Item | 결정 |
|---|---|
| Title | C에서 객체지향 프로그래밍하기 |
| Structure | 설명형, 7장 (표지 뒤에 5초짜리 구조도) |
| Scope | 캡슐화와 정보 은닉만. 5장은 "은닉이 양쪽에서 일어난다"로 설명 |
| Audience | C를 같이 공부하는 정글 사람들. 절반 이상은 내용을 안다고 가정. 강의장 대형 모니터 |
| Design | week04 덱 재사용: IBM Plex Sans KR/Mono, 흰 바탕·먹색·`#ff3300` 강조, `data-step` reveal |
| Code panels | 얇은 테두리 머리띠에 파일명(왼쪽)과 줄 범위(오른쪽). week04의 검은 띠 대신 |
| Q&A | 없음 |

## Outline

### S1 · Cover

- Label: `Krafton Jungle · Week 05`, 오른쪽 아래 `2 MIN`
- Tags: `Troubleshooting`, `study-cli` (`study-cli`는 프로그램 이름이라 대문자로 바꾸지 않아요)
- Title: **C에서 객체지향 프로그래밍하기**
- Subtitle: Encapsulation
- Footer: `projects/study-cli` · `main.c` · `record.c` · `record.h`

### S1b · 구조도 (5초)

설명하지 않고 5초쯤 보여 주는 장이에요. 표지에서 하던 두 번째 문장을 이 장에서 말해요.

- Thesis: main.c는 **헤더로만** core에 닿는다
- Diagram (inline SVG, 화살표 = `#include`)

  ```text
   CLI 쪽 (interface)   core
   ┌────────┐           ┌───────────┐           ┌──────────────────┐
   │ main.c │──────────▶│ record.h  │◀──────────│ record.c         │
   │ argv   │           │ typedef … │           │ struct _Record { │  ← 빨강
   │ printf │           └───────────┘    ┌──────│ count, capacity… │
   │        │                  ▲─────────┘      └──────────────────┘
   │        │           ┌───────────┐           ┌──────────────────┐
   │        │──────────▶│ storage.h │◀──────────│ storage.c        │
   └────────┘           │ file_read │           │ Sub_add(r, …)    │
                        └───────────┘           └──────────────────┘
  ```

- Caption: 구조체 정의는 **record.c 안에만** 있다
- Footer: Makefile · study = main.o + record.o + storage.o
- Evidence (4010305): `main.c`는 `record.h`·`storage.h`, `record.c`는 `record.h`, `storage.c`는 `storage.h`·`record.h`를 include해요. `storage.c`도 `r->`를 쓰지 않고 `Sub_add`로만 기록을 넣어요.

### S2 · 불완전 타입으로 만든 opaque pointer

- Panel `record.h · 10`

  ```c
  typedef struct _Record Rec;
  ```

- Panel `main.c · 51, 83`

  ```c
  Rec *r = new_record();
  ...
  Read_total(r, print_total);
  ```

- Thesis: main.c(CLI 쪽)는 Rec의 **이름만** 알고, 구조체의 정의는 모른다
- Machine panel `gcc · main.c 에서 구조체 내부를 보면`

  ```text
  r->count;
  error: invalid use of incomplete typedef 'Rec'
  ```

  2026-10-01에 `r->count`로 재현해서 확인했어요. gcc는 뒤에 `{aka 'struct _Record'}`를 붙이고 따옴표를 ‘ ’로 찍는데, 화면 폭이 모자라면 그 부분은 잘라도 돼요.
- Punch: 포인터로 가리킬 수는 있지만, **내부는 볼 수 없다**. 이게 불완전 타입입니다.

### S3 · 어떻게 가능한가: 컴파일과 링크

윗줄은 두 번 눌러서 `main.c` → `record.h` → `record.c` 순서로 열어요. 아랫줄(링크 전후)은 처음부터 보여요.

- Thesis: 컴파일러는 **포인터 자리(8바이트)**만 잡고, 링커는 **함수 주소**를 채운다
- Step 0 · `main.c`: O는 실제 코드에 있는 줄, X는 쓸 수 없는 줄이에요.

  ```text
  Rec *r = new_record();  O
  r->count;               X
  ```

- Step 1 · `record.h · 10, 15`

  ```c
  typedef struct _Record Rec;
  Rec *new_record(void);
  ```

- Step 2 · `record.c · 12–16, 19`

  ```c
  struct _Record{
      size_t count;
      size_t capacity;
      Sub **list;
  };
  Rec *r = malloc(sizeof *r);
  ```

- Bottom row (machine panels, 처음부터 보임)

  ```text
  main.o  링크 전   call new_record   e8 00 00 00 00
          ② link · 0을 new_record까지의 거리로 채운다 ▶
  study   링크 후   call new_record   e8 41 02 00 00
  ```

- Punch: `r`에 들어갈 주소는 실행 중에 `new_record`가 `malloc`으로 만들어 돌려준다. 구조체 내부 정의는 끝까지 `main.c`에 보이지 않는다.
- Footer: C17 6.2.5p28 · 구조체 포인터는 모두 같은 표현
- Evidence (4010305, `make`로 만든 빌드)
  - `main.c`에 `Rec r;`을 쓰면 `error: storage size of 'r' isn't known`가 나요. 컴파일러는 Rec의 자리를 빈 공간으로도 잡지 못해요.
  - `sizeof r`는 `main.c`에서 8, `sizeof *r`는 `record.c`에서 24예요.
  - `main.o`의 `call`은 `e8 00 00 00 00`이고 `R_X86_64_PLT32 new_record` 재배치 항목이 붙어 있어요. `study`에서는 `e8 41 02 00 00`, 즉 `call 1877 <new_record>`로 채워져 있어요. 채워진 `0x241`은 절대 주소가 아니라 다음 명령어(`0x1636`)에서 `new_record`(`0x1877`)까지의 거리예요.
  - 세 시점이 서로 달라요. 컴파일러는 `r`의 칸(`-0x10(%rbp)`)만 정하고, 링커는 `call`의 거리만 채워요. `r`의 값은 실행 중에 정해져요. gdb에서 `&r = 0x7fffffffcd80`([stack]), `r = 0x55555555a010`([heap])이었어요.

### S4 · `Read_total(r, print_total)`

세 패널을 단계별로 보여 줘요(Q7 A안). 강조: `Minutes`, `func`, `func(total)`, `printf`.

- Step 1 · `record.h · 27–28`

  ```c
  typedef void (*Minutes)(int minutes);
  void Read_total(const Rec *r, Minutes func);
  ```

- Step 2 · `record.c · 1–3, 94–99`

  ```c
  #include <stdlib.h>
  #include <string.h>
  #include "record.h"   // stdio.h 없음

  void Read_total(const Rec *r, Minutes func){
      int total = 0;
      for (size_t i = 0; i < r->count; i++){
          total += r->list[i]->minutes;
      } func(total);
  }
  ```

- Step 3 · `main.c · 11–13`

  ```c
  void print_total(int minutes){
      printf("Total: %d minutes\n", minutes);
  }
  ```

- Punch: `record.c`는 언제 부를지만 알고, 무엇을 할지는 `main`이 정한다
- Side note: `record.c`의 include는 `<stdlib.h>`, `<string.h>`, `"record.h"` 세 줄이 전부예요. `nm record.o`에는 `printf`도 `print_total`도 없어요.

### S5 · 정보 은닉은 양쪽에서 일어난다

- Thesis: **Why?** Core는 그대로 두고 main.c에서 재사용 가능

- Two columns

  | `main.c`가 모르는 것 | `record.c`가 모르는 것 |
  |---|---|
  | 저장 방식: `r->list`, `count`, `capacity` | 출력 방식: `printf`인지 `stderr`인지 |

- Middle: 둘이 공유하는 것은 모양 하나, `Minutes` = `void (*)(int)`
- Panel `main.c (예시)`: 실제 코드에는 없는 함수라서 "예시" 라벨이 꼭 필요해요.

  ```c
  void print_total_err(int minutes){
      fprintf(stderr, "Total: %d minutes\n", minutes);
  }

  Read_total(r, print_total);      // stdout
  Read_total(r, print_total_err);  // stderr
  ```

  `main.c`에는 추가하지 않았어요. `record.c`를 그대로 두고 이 함수와 링크해서, 같은 합계가 stdout과 stderr로 갈라져 나오는 것을 2026-10-01에 확인했어요.

- Punch: `record.c`를 한 줄도 고치지 않고, 같은 모양의 함수만 바꿔 넣는다

### S6 · 가져가실 것

- Thesis: C에 class는 없어도, 숨길 수는 있다
- Checklist
  - 헤더에 이름만 두면 정의부분을 숨길 수 있다 (불완전 타입)
  - 할 일은 함수 포인터로 넘긴다 (콜백)
- Footer: `WEEK 05 · study-cli`

## Script

`[누름]`은 다음 단계로 넘기는 클릭이에요.

### S1

> 안녕하세요. 'C에서 객체지향 프로그래밍하기'입니다.

### S1b

> CLI를 만들다가 구조체를 record.c 안에 숨겼더니, main이 할 수 없는 일이 생겼습니다.

### S2

> main.c는 r이라는 포인터를 계속 넘깁니다. 그런데 main.c가 보는 헤더에는 Rec라는 이름만 있고, 몸체가 없습니다. 불완전 타입이죠. 그래서 r->count처럼 안을 보면 바로 컴파일 에러가 납니다.

### S3

> 그럼 어떻게 컴파일될까요? [누름] 컴파일러는 r이 들어갈 8바이트만 잡고, 비워 둔 함수 주소는 링커가 채웁니다. [누름] 구조체는 실행할 때 record.c가 만들고요.

### S4

> Read_total(r, print_total)은 더 재미있습니다. [누름] 헤더에는 print_total이 없고, int 하나를 받는 함수라는 모양만 있습니다. [누름] record.c는 합계를 구해서 받은 함수에 넘길 뿐, stdio.h조차 없습니다. [누름] 출력은 main.c의 print_total이 합니다.

### S5

> 왜 이렇게 할까요? main은 저장 방식을 모르고, record.c는 출력 방식을 모릅니다. 숨김이 양쪽에서 일어나죠. 그래서 record.c를 고치지 않고 함수만 바꿔 넣으면, stderr로도 출력할 수 있습니다.

### S6

> 정리하면, C에 클래스는 없어도 이름만 보여 주면 몸체를 숨길 수 있고, 할 일은 함수 포인터로 넘기면 됩니다. 감사합니다.

## Timing

공백을 뺀 글자 수로 쟀어요. week04 대본과 같은 방식이에요.

| Slide | 글자 수 |
|---|---|
| S1 | 26 |
| S1b | 44 |
| S2 | 94 |
| S3 | 68 |
| S4 | 137 |
| S5 | 96 |
| S6 | 52 |
| **합계** | **517** |

- 예상 시간: 초당 4.5자로 말하면 115초, 3.8자로 말하면 136초예요.
- 비교: week04 최종 대본은 549자(122–144초)였어요.
- 주의: `Read_total`, `r->count` 같은 식별자는 글자 수보다 소리 내어 읽는 시간이 더 길어요. S3의 클릭 두 번과 S4의 클릭 세 번도 시간에 들어가요. 그래서 위 숫자는 하한으로 보는 게 맞아요.
- 리허설에서 2분을 넘기면 아래 순서로 잘라요(합계 약 −53자, 차분한 속도로 약 122초).
  1. S4 첫 문장 "Read_total(r, print_total)은 더 재미있습니다." (화면에 이미 보여요)
  2. S2 "그런데 main.c가 보는 헤더에는" → "헤더에는"
  3. S5 "왜 이렇게 할까요?"
  4. S1b "CLI를 만들다가"

## Open items

- 리허설로 실제 시간을 재고, 2분을 넘기면 Timing 절의 순서대로 잘라요.
- 덱의 대본 주석과 이 파일의 Script 절은 같은 내용이에요. 한쪽을 고치면 다른 쪽도 같이 고쳐요.
