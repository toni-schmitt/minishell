/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:11:39 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/29 18:42:53 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_UTILS_H
# define PARSER_UTILS_H

# define TOKEN_FOUND 1
# define TOKEN_NOT_FOUND 0
# define EXIT_BREAK 3
# define EXIT_SYNTAX_ERROR 4
# include <stdbool.h>

typedef struct s_func_args
{
	char		**lex_toks;
	t_par_tok	**par_toks;
	t_iter		*iter;
}	t_func_args;

// PARSER UTILS
int			init_curr_par_tok(void);
int			free_parser(t_par_tok *par_tok[], t_iter *iter, int exit_status);
size_t		get_tokens_size(char *lex_toks[]);
int			get_subshell_tok(t_iter *iter);

// REDIR UTILS
bool		try_get_tok_redir_buf(char ****buf, size_t **buf_size, \
t_iter **buf_iter);
int			get_tok_redir_type(char *lex_tok);

// CHECK SYNTAX
int			check_syntax(t_par_tok *par_toks[]);

// interprete_vars
int			interprete_vars(t_par_tok *par_toks[]);

#endif