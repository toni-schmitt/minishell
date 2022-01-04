# minishell - 42 Heilbronn (October 2021, Version 6)
## As beautiful as a shell.<br>
## from [@tschmitt](https://github.com/toni-schmitt) and [@tblaase](https://github.com/tblaase)<br>
![result](https://github.com/toni-schmitt/minishell/blob/main/readme_additions/minishell_result.jpg)
## Contents
- [Introduction](https://github.com/toni-schmitt/minishell#introduction)
- [Our Minishell](https://github.com/toni-schmitt/minishell#our-minishell)
  - [Lexer](https://github.com/toni-schmitt/minishell#lexer)
  - [Parser](https://github.com/toni-schmitt/minishell#parser)
  - [Expander](https://github.com/toni-schmitt/minishell#expander)
  - [Executor](https://github.com/toni-schmitt/minishell#executor)

## Short description of the subject

The goal of the subject was to recreate some of the functionalities of bash (Version 3.2).<br>
To see the exact requirements, check Chapter III and IV of the [subject pdf](https://github.com/toni-schmitt/minishell/blob/main/readme_additions/en.subject.pdf).
## From the [subject pdf](https://github.com/toni-schmitt/minishell/blob/main/readme_additions/en.subject.pdf)
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
![subject_restrctions](https://github.com/toni-schmitt/minishell/blob/main/readme_additions/minishell_from_subject_pdf.jpg)

## Our Minishell
### The basic functionalities of the project
- this is a shell that can be compiled by running<br>`make all`<br>and then to run it<br>`./minishell`<br>or instead you can run<br>`make run`
- now you are greeted with a prompt `minishell$ `&nbsp;waiting for input just like any other shell
- this project uses the readline libraries `readline/history.h` and `readline/readline.h` you can install those via `brew install readline` or `apt-get install libreadline-dev`
- thanks to those there is a working history of used commands

### The basic structure of our minishell
Just like most of the other shells we have divided our shell into 4 parts:
1. [Lexer](https://github.com/toni-schmitt/minishell#lexer)
2. [Parser](https://github.com/toni-schmitt/minishell#parser)
3. [Expander](https://github.com/toni-schmitt/minishell#expander)
4. [Executor](https://github.com/toni-schmitt/minishell#executor)

Those parts all have different tasks.<br>

----------

### Lexer
The lexer will get the input from the prompt once the user pressed `enter` and create so called `lexer_tokens` from it<br>
The lexer_tokens are a 2D char array `char *lexer_tokens[]`<br>
Now the given input i.e. `cat <<eof >file1 && cat file1 && abc || wc <file1 | cat >file2` will result in `lexer_tokens` like<br>
| lex_tok[0] | lex_tok[1] | lex_tok[2] | lex_tok[3] | lex_tok[4] | lex_tok[5] | lex_tok[6] | lex_tok[7] | lex_tok[8] | lex_tok[9] | lex_tok[10] | lex_tok[11] | lex_tok[12] | lex_tok[13] |
| ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- | ----------- |
| `cat` | `<<eof` | `>file1` | `&&` | `cat` | `file1` | `&&` | `abc` | `\|\|` | `wc` | `<file1` | `\|` | `cat` | `>file2` |

----------

### Parser
The parser will then check for invalid syntax and create a kind of command table called `parser_tokens`<br>
This is one element of the `t_par_tok \*parser_tokens[]`:<br>
```
typedef struct s_parser_tok
{
	t_par_tok_type	type;
	t_redir_type	redir_type[5];
	char			**cmd;
	size_t			cmd_size;
	char			**in;
	size_t			in_size;
	char			**out;
	size_t			out_size;
}	t_par_tok;
```
So after the syntax-check the parser is able to get the command and its arguments as well as the redirections connected to the command.<br>
[back to basic structure](https://github.com/toni-schmitt/minishell#the-basic-functionalities-of-the-project)

----------

### Expander
[back to basic structure](https://github.com/toni-schmitt/minishell#the-basic-functionalities-of-the-project)

----------

### Executor
[back to basic structure](https://github.com/toni-schmitt/minishell#the-basic-functionalities-of-the-project)

----------

### Some example outputs

wrong syntax:<br>
If some form of wrong syntax gets detected, `Invalid Syntax` is printed and the error value `$?` is set to `258`<br>
![syntax_error](https://github.com/toni-schmitt/minishell/blob/main/readme_additions/syntax_error.jpg)
