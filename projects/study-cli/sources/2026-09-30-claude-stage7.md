---
scope: 오라버니's own sentences and the tool output from one Claude Code session, a source for the study design note
truth: Quotes are verbatim; times are file mtimes; outputs are copied from the session
source: Claude Code session in c-workshop, 2026-09-30 01:40–02:10 (KST)
born: 2026-09-30
---

# Claude — undeclared, then undefined (Stage 7)

Chapter 5 of the 4부 후보 continues from Gemini Q27
([2026-09-29-gemini-stage7.md](2026-09-29-gemini-stage7.md)). Gemini named two
causes for the undeclared error: a missing `#include "record.h"`, and
`print_input` defined below `main`. Neither was the cause.

## Timeline

| Time | Event |
| --- | --- |
| 09-29 21:39 | `study` binary last built (before the struct moved) |
| 09-29 23:43 | `af23ba0` commits the struct definition inside `record.c` while `main.c` still reads `r->list`; this commit does not build |
| 09-30 01:33–01:34 | `print_result` declaration and definition written in `lab/split6/record.h`, `lab/split6/record.c` |
| 09-30 01:37 | `projects/study-cli/main.c` calls `print_result(r, print_input);` |
| 09-30 01:46 | declaration added to `projects/study-cli/record.h` |
| 09-30 01:48 | definition added to `projects/study-cli/record.c`; build passes |

## Quotes and evidence

### 1. "작동하는지 판단해줄래?"

> 지금 main.c, record.h, record.c 등을 실제로 작성했거든? 현재 상태 기준으로 작동하는 지 여부를 판단해줄래?

```text
main.c:40:5: error: implicit declaration of function 'print_result'; did you mean 'print_input'? [-Wimplicit-function-declaration]
```

`af23ba0` (HEAD at that time had the same sources) did not build either:

```text
main.c:37:29: error: invalid use of incomplete typedef 'Rec' {aka 'struct _Record'}
```

The directory's `study` binary was older than all three sources, so running
`./study` would have run the old code.

### 2. The declaration is in another file

> 선언 되어있지 않나? record.h에. print_result가 19라인에 있잖아.

```text
./lab/split6/record.h:19:  void print_result(const Rec *r, result func);
./lab/split6/record.c:55:  void print_result(const Rec *r, result func){
./projects/study-cli/main.c:40:  print_result(r, print_input);
```

`#include "record.h"` searches the directory of `main.c` first, so the build
read only `projects/study-cli/record.h`. Both files had the same name.

### 3. Compile passes, link fails

> 아. 이게 내가 split 쪽에 수정해버려서 문제가 된거구나? 지금은 문제 없어?

With the declaration in `projects/study-cli/record.h` and the definition still
only in `lab/split6/record.c`:

```text
main.c:40: undefined reference to `print_result'
collect2: error: ld returned 1 exit status
```

This is the case 오라버니 predicted in Gemini Q10 ("주소가 0000으로 꽉차있을 것
같은데"): the linker refuses to write the executable.

### 4. Works; rename the lab copy

> 이제 된거지? .. 이게, 지금 lab/split/ 하고 겹쳐서 보다보니까, 이런 참사가 일어났네. 하필이면 이름도 완전히 같ㅇ아버려서. 이거 다 끝나면 lab/split은 이름이라고 outdated이런 식으로 바꿔야지.

After the definition moved (01:48), on a scratch copy:

| Check | Result |
| --- | --- |
| `make` with the workshop flags | pass, links |
| empty input and 11 bad inputs | expected exit (0 or 2) and stderr |
| 25 pairs (two `realloc`) | 25 records in order; ASan clean; Valgrind 0 leaks |
| input error at pair 15 | exit 2, no record printed, 0 leaks |
| `malloc`/`realloc` failure at N = 1…54 | every N exit 1, 0 leaks |

Then `lab/split6/{main.c,record.c,record.h}` became `archived_*` (`git mv`),
and the two `.c` files now include `"archived_record.h"`.

### 5. One command to build and run

> 결론적으로 내가 complie, run, dbg 등을 하고 싶으면 어떻게 해야 해? 사실, 가장 주된 사용처는 아마 이전처럼 c C 40 OS 30 이런 식으로 입력해보고 그 결괏값을 확인(지금은 fprintf()이지만, 나중에는 파일 생성이나 TUI도 모두 포함. 최소한, 진짜 shell 커맨드로 잇기 전까지.)하는 것이 될거 같아서.

Result: `~/.local/bin/sc`. It runs `make -s` in `projects/study-cli` first, so
a stale binary never runs. `sc ARGS`, `sc dbg ARGS` (gdb; `rerun` rebuilds via
make), `sc vg ARGS` (Valgrind, exit 99 on a memory error).
