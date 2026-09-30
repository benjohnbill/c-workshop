---
scope: Stage 8 behavior specification
truth: This file defines a scratch-file persistence version, not the Stage 9 storage contract
updated: 2026-09-30
---

# Stage 8 — Save and Load

## Usage

1. `save`에 파일 경로와 기록을 전달해 파일에 저장합니다.
2. 이후 `list`나 `total`에 같은 경로를 전달해 저장된 기록을 확인합니다.
3. 쓰기 실패 때 파일이 불완전하게 남을 수 있으므로 실험용 파일만 사용합니다.

## Try it

```sh
./study save /tmp/study-stage8.tsv C 30 OS 45
./study list /tmp/study-stage8.tsv
./study total /tmp/study-stage8.tsv
```

`list`에서 두 기록을 확인하고 `total`에서 `Total: 75 minutes`를 확인합니다.

## Behavior

- 문법은 `study save PATH [SUBJECT MINUTES ...]`, `study list PATH`, `study total PATH`입니다.
- `save`는 전체 목록을 기록합니다. 파일이 있으면 교체하며, 빈 목록도 저장할 수 있습니다.
- 과목·시간과 종료 상태는 [공통 규칙](../README.md#shared-contract)을 따릅니다. 잘못된 명령 입력은 기존 파일을 바꾸지 않습니다.
- 파일 첫 줄은 `subject`, `minutes` 두 field의 TSV header입니다. 이후 한 줄마다 한 기록이며 field는 tab, 행은 newline으로 구분합니다.
- header만 있는 파일은 빈 목록입니다. header 누락, field 수 오류, 잘못된 값은 손상된 파일입니다.
- `list`·`total`은 파일 전체가 유효할 때 결과를 출력합니다. 손상된 파일은 행 번호를 포함한 오류를 알리고 exit `1`로 종료하며 원본을 유지합니다.
- 없는 파일이나 읽기·쓰기 실패는 실행 오류입니다. 쓰기 실패를 성공으로 보고하지 않습니다.
- 기존 파일을 안전하게 보존하는 저장은 Stage 9에서 추가합니다.

필수 연습: `FILE *`를 통한 입출력을 별도 module로 만들고 기록 배열과 연결합니다.
읽기 버퍼가 재사용돼도 앞서 읽은 기록은 유지되어야 합니다. 정상·실패 경로에서
열었던 파일과 확보한 메모리를 정리합니다.

## Carries over / Changes in Stage 9

- Stage 9까지 이어집니다: 파일을 읽어 전체가 유효할 때만 받아들이는 동작, 행 번호를
  담은 오류, 읽기 버퍼와 기록의 수명, 파일과 메모리 정리, 과목·시간 규칙과 종료 상태.
- Stage 9에서 바뀝니다: 명령 문법(`save PATH …` → 옵션), 대상 파일을 직접 덮어쓰는
  방식(→ 임시 파일과 `rename()`), 2 field 형식(→ v1 형식).

## Done when

- 저장 후 다른 process에서 같은 내용·순서·합계를 확인합니다. 빈 목록도 왕복합니다.
- 과목에 공백·한국어가 있는 기록, 배열 확장이 필요한 많은 기록을 왕복합니다.
- 파일 중간에 잘못된 시간을 넣어 전체 결과가 거부되고 원본은 유지되는지 확인합니다.
- 없는 입력 경로와 쓸 수 없는 출력 경로에서 오류를 확인하고 [공통 완료 조건](../../../CURRICULUM.md#shared-completion-gates)을 통과합니다.

다음 버전: [정식 명령과 안전한 저장](09-daily-cli.md).
Stage 9에서는 ID·날짜·메모가 있는 v1 형식을 사용하며 이 실험 파일의 변환은 요구하지 않습니다.
