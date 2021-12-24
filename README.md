# minishell - 42 Heilbronn (October 2021, Version 6)
As beautiful as a shell <br>
from [@tschmitt](https://github.com/toni-schmitt) and [@tblaase](https://github.com/tblaase)

## Short description of the subject

The goal of the subject was to recreate some of the functionalities of bash (Version 3.2).<br>
## From the subject pdf
### Introduction
```
The existence of shells is linked to the very existence of IT. At the time, all coders agreed
that communicating with a computer using aligned 1/0 switches was seriously
irritating. It was only logical that they came up with the idea to communicate with
a computer using interactive lines of commands in a language somewhat close
to english.
With Minishell, you’ll be able to travel through time and come back to problems
people faced when Windows didn’t exist.
```
### Some of the restrictions
![grafik](https://user-images.githubusercontent.com/85116019/147352152-0c597a42-7a7b-4a0b-b1c3-bb57f5e2cd49.png)

## Our Minishell
### The basic functionalities of the project
- this is a shell that can be compiled by running<br>`make all`<br>and then<br>`./minishell`<br>or instead you can run<br>`make run`
- now you are greeted with a prompt `minishell$ `&nbsp;waiting for input
- this project uses the readline libraries `readline/history.h` and `readline/readline.h`
- thanks to those there is a working history of used commands

### The basic structure of our minishell
Just like most of the other shells we have divided our shell into 4 parts:
1. lexer
2. parser
3. expander
4. executor
Those parts all have different tasks.
#### Lexer
The lexer will get the input from the prompt once the user pressed `enter` and create to called `lexer_tokens` from it.<br>
The lexer_tokens are a 2D char array `char *lexer_tokens[]`<br>
Now the given input i.e. `cat <<eof >file1 && cat file1 && abc || wc <file1`.<br>
| lex_tok[0] | lex_tok[1] | lex_tok[2] | lex_tok[3] | lex_tok[4] | lex_tok[5] | lex_tok[6] | lex_tok[7] | lex_tok[8] | lex_tok[9] | lex_tok[10] |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| `cat` | `<<eof` | `>file1` | `&&` | `cat` | `file1` | `&&` | `abc` | `\|\|` | `wc` | `<file1` |
#### Parser
The parser will then check for invalid syntax and create a kind of command table called `parser_tokens`
[WIP]
