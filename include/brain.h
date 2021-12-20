/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 22:21:31 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/20 14:20:52 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_H
# define BRAIN_H

# include <stdlib.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <stdbool.h>

typedef enum e_parser_tok_type
{
	std = 0,
	subshell = 1,
	and = 2,
	or = 3,
}	t_par_tok_type;

typedef enum e_parser_redirection_type
{
	is_pipe = 0,
	is_in = 1,
	is_in_heredoc = 2,
	is_out = 3,
	is_out_append = 4,
}	t_redir_type;

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

typedef enum e_iterator
{
	lex = 0,
	par = 1,
	cmd = 2,
	in = 3,
	out = 4,
}	t_iter;

typedef struct s_expander_tokens
{
	char			**cmd;
	int				in;
	int				out;
	bool			is_pipe;
}	t_exp_tok;

// BRAIN
int			lexer(char *line);
int			parser(char *lexer_tokens[]);
int			expander(t_par_tok *parser_tokens[]);
int			executor(t_exp_tok *exp_tok);

// BRAIN UTILS

// GETTER / SETTER
void		set_envp(char *envp[]);
char		**get_envp(void);
void		reset_envp(void);

void		set_lex_toks(char **lex_toks);
char		**get_lex_toks(void);
char		*get_curr_lex_tok(void);
void		reset_lex_toks(void);

void		set_iter(t_iter *iter);
t_iter		*get_iter(void);
void		reset_iter(void);

void		set_par_toks(t_par_tok **par_toks);
t_par_tok	**get_par_toks(void);
t_par_tok	*get_curr_par_tok(void);
void		reset_par_toks(void);

void		set_exp_toks(t_exp_tok *exp_toks[]);
t_exp_tok	**get_exp_toks(void);
void		reset_exp_toks(void);

#endif