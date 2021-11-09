/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 22:21:31 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/10 00:08:19 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_H
# define BRAIN_H

# include <readline/history.h>
# include <readline/readline.h>

enum
{
	std = -1,
	pipe_redir = 0,
	in_redir = 1,
	out_redir = 2,
	out_append = 3,
	heredoc = 4,
	subshell = 5,
	and = 6,
	or = 7,
	semicolon = 8,	
};

typedef struct s_parser_tok
{
	int		type;
	char	*cmd;
	char	*args;
	char	**in;
	char	**out;
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