/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:11:39 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/02 17:33:48 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# define EXIT_BREAK 3
# define EXIT_SYNTAX_ERROR 4
# include <stdbool.h>

typedef struct s_func_args
{
	char		**lex_toks;
	t_par_tok	**par_toks;
	t_iter		*iter;
}	t_func_args;

// GET TOKENS

int			get_tok_type(char *lex_tok, t_iter *iter);
int			get_tok_cmd(char *lex_tok, t_par_tok *par_tok, t_iter *iter);
int			get_tok_redir(char *lex_toks[], t_iter *iter);
int			get_special_tok( \
	char *lex_toks[], t_par_tok *par_toks[], t_iter *iter \
	);

// GET TOKENS UTILS

int			set_tok_type_pipe(t_par_tok *par_tok, t_iter *iter);
int			get_subshell_tok(t_iter *iter);

// PARSER UTILS

int			init_curr_par_tok(void);
int			free_parser(t_par_tok *par_tok[], t_iter *iter, int exit_status);
size_t		get_tokens_size(char *lex_toks[]);

// REDIR UTILS

int			get_tok_redir_type(char *lex_tok);
bool		try_get_tok_redir_buf( \
	char ****buf, size_t **buf_size, t_iter **buf_iter \
	);

char		*interprete_vars(char *lex_tok);
void	free_par_toks(t_par_tok *par_toks[]);

#endif