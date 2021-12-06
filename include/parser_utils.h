/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:11:39 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/04 23:04:00 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# define EXIT_BREAK 3
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
	char *lex_tok, t_par_tok *par_toks[], t_iter *iter \
	);

// GET TOKENS UTILS

int			set_tok_type_pipe(t_par_tok *par_tok, t_iter *iter);
int			get_subshell_tok(t_iter *iter);
bool		is_quote_token(char *lex_tok);
bool		is_redir_token(char *lex_tok);
bool		is_special_token(char *lex_tok);

// PARSER UTILS

int			init_curr_par_tok(void);
int			free_parser(t_par_tok *par_tok[], t_iter *iter, int exit_status);
size_t		get_tokens_size(char *lex_toks[]);

// REDIR UTILS

int			get_tok_redir_type(char *lex_tok);
bool		try_get_tok_redir_buf( \
	char ****buf, size_t **buf_size, t_iter **buf_iter \
	);

char		*interprete_env_var(char *lex_tok);
void		free_par_toks(t_par_tok *par_toks[]);

#endif