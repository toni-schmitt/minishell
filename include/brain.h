/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 22:21:31 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/29 18:43:03 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_H
# define BRAIN_H

# include <readline/history.h>
# include <readline/readline.h>

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

// BRAIN
int			lexer(char *line);
int			parser(char *lexer_tokens[]);
int			expander(t_par_tok *parser_tokens[]);
int			executor(void);

// BRAIN UTILS

// GETTER / SETTER
t_par_tok	**get_par_toks(void);
t_par_tok	*get_curr_par_tok(void);
void		set_par_toks(t_par_tok **par_toks);
t_iter		*get_iter(void);
void		set_iter(t_iter *iter);
char		**get_lex_toks(void);
char		*get_curr_lex_tok(void);
void		set_lex_toks(char **lex_toks);

// ENVP UTILS
void		set_envp(char *envp[]);
char		**get_envp(void);

#endif