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
- [Examples](https://github.com/toni-schmitt/minishell#some-example-outputs)
  - [wrong syntax](https://github.com/toni-schmitt/minishell#wrong-syntax)
  - [invalid command](https://github.com/toni-schmitt/minishell#invalid-command)

## Short description of the subject

The goal of the subject was to recreate some of the functionalities of bash (Version 3.2).<br>
To see the exact requirements, check Chapter III and IV of the [subject pdf](https://github.com/toni-schmitt/minishell/blob/main/readme_additions/en.subject.pdf).<br>
If you find any problems with our minishell, [here](https://github.com/toni-schmitt/minishell/issues/new/choose) is the possibility to open an issue.<br>
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
- this project uses the readline libraries `readline/history.h` and `readline/readline.h` you can install those via `brew install readline` or `apt-get install libreadline-dev`, thanks to those there is a working history of used commands
- there is some memory-leaks caused by the readline-library

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

[back to contents](https://github.com/toni-schmitt/minishell#contents)<br>
[back to basic structure](https://github.com/toni-schmitt/minishell#the-basic-functionalities-of-the-project)<br>

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
[back to contents](https://github.com/toni-schmitt/minishell#contents)<br>
[back to basic structure](https://github.com/toni-schmitt/minishell#the-basic-functionalities-of-the-project)<br>

----------

### Expander
The expander will take the parser tokens as argument.<br>
The expander will interprete the environment variables into their corresponding value.<br>
It also handles subshells, creates pipes and handles all the opening of input-/output-redirections and storing the correct ones in the executor tokens.<br>
Subshells are executed by creating a child process which runs minishell without readline reading the input, but directly handing the correct, unparsed commands to it. And after the lexer is done, it will call the parser and so on.<br>
After passing every of those parts without errors, it calls the executor in a loop and gives the executor the correct values to work with.<br>
After a call of the executor, an error value, similar to errno, is set to the exit code of the executor.<br>
This error value can be checked by running `echo $?` and is used for the `&&` and `||` logic.<br><br>
This is the way the data is stored in the expander tokens and handed to the executor:<br>
```
typedef struct s_expander_tokens
{
	char			**cmd;
	int				in;
	int				out;
	bool			is_pipe;
}	t_exp_tok;
```

[back to contents](https://github.com/toni-schmitt/minishell#contents)<br>
[back to basic structure](https://github.com/toni-schmitt/minishell#the-basic-functionalities-of-the-project)<br>

----------

### Executor
The executor does as it is called, it executes the command.<br>
If the given command is an inbuilt, it will just run the command in the same process, if it isn't it will create a child process to run the command in.<br>
After this is decided, the redirections of input and output are done and the command is executed.<br>
The executor always returns the exit code of whatever it did.<br>

[back to contents](https://github.com/toni-schmitt/minishell#contents)<br>
[back to basic structure](https://github.com/toni-schmitt/minishell#the-basic-functionalities-of-the-project)<br>

----------

### Some example outputs

#### wrong syntax
If some form of wrong syntax gets detected, `Invalid Syntax at token` is printed and the error value `$?` is set to `258`<br>
![syntax_error](https://github.com/toni-schmitt/minishell/blob/main/readme_additions/syntax_error.jpg)<br>
#### invalid command
If there was an invalid command used, `command not found` is printed and the error value `$?` is set to `127`<br>
![invalid_command](https://github.com/toni-schmitt/minishell/blob/main/readme_additions/invalid_command.jpg)<br>
[back to contents](https://github.com/toni-schmitt/minishell#contents)<br>
