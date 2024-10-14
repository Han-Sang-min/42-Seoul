# 개요
간략하게 Bash를 모방하여 만든 프로젝트입니다.

프로젝트에 사용한 함수는 다음과 같습니다. 해당하는 함수 호출을 위한 **라이브러리**를 제외한 것들은 **사용하지 않았습니다**.
```
readline, rl_clear_history, rl_on_new_line,
rl_replace_line, rl_redisplay, add_history,
printf, malloc, free, write, access, open, read,
close, fork, wait, waitpid, wait3, wait4, signal,
sigaction, sigemptyset, sigaddset, kill, exit,
getcwd, chdir, stat, lstat, fstat, unlink, execve,
dup, dup2, pipe, opendir, readdir, closedir,
strerror, perror, isatty, ttyname, ttyslot, ioctl,
getenv, tcsetattr, tcgetattr, tgetent, tgetflag,
tgetnum, tgetstr, tgoto, tputs
```

명령어 입력 시, PATH 환경변수가 가지는 경로를 그대로 탐색하되, 직접 구현한 내부 명령어(Builtin)를 우선적으로 실행하도록 src/builtin의 동작을 먼저 처리하게 구현했습니다.
# 실행방법
- `make all` - 컴파일을 수행합니다.
- `make clean` - object 파일을 제거합니다.
- `make fclean` - clean을 수행한 후에, 실행파일을 제거합니다.
- `make re` - fclean을 수행한 후에, all을 수행합니다.

# 명세사항
- 새로운 명령을 기다릴 때 프롬프트를 표시해야 합니다.
- 작동하는 히스토리가 있어야 합니다.
- 적절한 실행 파일을 검색하고 실행해야 합니다. (PATH 변수에 기반하거나 상대 경로 또는 절대 경로를 사용)
- 수신된 신호를 나타내기 위해 **하나 이상의 전역 변수를 사용하지 않도록** 해야 합니다. 이를 고려하면, 신호 핸들러가 메인 데이터 구조에 접근하지 않도록 보장해야 합니다.
- 닫히지 않은 따옴표나 `\` (백슬래시), `;` (세미콜론) 같은 특수 문자는 해석하지 말아야 합니다.
- **싱글 쿼트**(`'`)를 처리해야 하며, 이는 따옴표 안에 있는 메타문자를 쉘이 해석하지 않도록 해야 합니다.
- **더블 쿼트**(`"`)를 처리해야 하며, 이는 따옴표 안에 있는 메타문자를 해석하지 않도록 해야 하지만, `$` (달러 기호)는 예외로 둡니다.
- 다음과 같은 **리다이렉션**을 구현해야 합니다:
    - `<` 는 입력을 리다이렉트해야 합니다.
    - `>` 는 출력을 리다이렉트해야 합니다.
    - `<<` 는 구분 기호를 받아서, 그 구분 기호가 포함된 줄이 나타날 때까지 입력을 읽어야 합니다. 그러나 히스토리는 업데이트하지 않아도 됩니다.
    - `>>` 는 출력을 덧붙이는 모드로 리다이렉트해야 합니다.
- **파이프**(`|` 문자)를 구현해야 합니다. 파이프라인의 각 명령어 출력은 다음 명령어의 입력으로 연결되어야 합니다.
- **환경 변수**를 처리해야 합니다. `$` 다음에 나오는 문자들의 시퀀스는 해당 변수의 값으로 확장되어야 합니다.
- **`$?`** 는 가장 최근에 실행된 전경 파이프라인의 종료 상태로 확장되어야 합니다.
- *ctrl-C, ctrl-D, ctrl-**의 동작은 bash에서처럼 처리해야 합니다:
    - **ctrl-C**는 새로운 줄에 새로운 프롬프트를 표시합니다.
    - **ctrl-D**는 쉘을 종료합니다.
    - *ctrl-**는 아무 동작도 하지 않습니다.
- **인터랙티브 모드**에서:
    - **ctrl-C**는 새로운 줄에 새로운 프롬프트를 표시해야 합니다.
    - **ctrl-D**는 쉘을 종료해야 합니다.
    - *ctrl-**는 아무 동작도 하지 않아야 합니다.
- 다음과 같은 **내장 명령어(builtins)**를 구현해야 합니다:
    - `echo` (옵션 `n` 지원)
    - `cd` (상대 또는 절대 경로만 사용)
    - `pwd` (옵션 없이)
    - `export` (옵션 없이)
    - `unset` (옵션 없이)
    - `env` (옵션 또는 인수 없이)
    - `exit` (옵션 없이)
- `readline()` 함수는 메모리 누수를 일으킬 수 있습니다. 이를 수정할 필요는 없습니다. 하지만 여러분이 작성한 코드에서는 메모리 누수가 발생하면 안 됩니다.
# 시연
<div align="left">
  <img src="https://github.com/user-attachments/assets/005d7296-ee90-455a-9464-42249a79961e" alt="Make miniShell" width="400">
  <p><em>history 기능</em></p>
</div>
<div align="left">
  <img src="https://github.com/user-attachments/assets/4928350a-9f69-43ce-8b5f-7a8d1029e319" alt="Make miniShell" width="400">
  <p><em>history 실행 파일 탐색 및 실행</em></p>
</div>
<div align="left">
  <img src="https://github.com/user-attachments/assets/09570e53-e3cc-4a4a-89ab-338aaa0075b7" alt="Make miniShell" width="400">
  <p><em>history 환경 변수 처리</em></p>
</div>
<div align="left">
  <img src="https://github.com/user-attachments/assets/5ac0e9e8-6296-4e78-ad7a-9ee2dfe557df" alt="Make miniShell" width="400">
  <p><em>리다이렉션 기능</em></p>
</div>
<div align="left">
  <img src="https://github.com/user-attachments/assets/476e497a-0bec-41e9-9ad0-e31d99880889" alt="Make miniShell" width="400">
  <p><em>파이프 기능</em></p>
</div>
