/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 22:21:31 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/16 21:01:32 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_H
# define BRAIN_H

# include <readline/history.h>
# include <readline/readline.h>

typedef enum e_parser_tok_type
{
	std = 0,
	pipe_redir = 1,
	in_out_redir = 2,
	subshell = 3,
	and = 4,
	or = 5,
	heredoc = 6,
}	t_par_tok_type;

typedef struct s_parser_tok
{
	t_par_tok_type	type;
	char			**cmd;
	char			**in;
	char			**out;
}	t_parser_tok;

// BRAIN
int		lexer(char *line);
int		parser(char *lexer_tokens[]);
int		expander(t_parser_tok *parser_tokens);
int		executor(void);

// BRAIN UTILS

// ENVP UTILS
void	set_envp(char *envp[]);
char	**get_envp(void);

#endif