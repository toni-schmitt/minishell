/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_tokens_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 19:08:20 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/03 18:15:52 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "parser_utils.h"

/**
 * @brief  Sets current and next token type to pipe
 * @note   Helper function of get_tok_type
 * @param  *par_tok: Current parser token to set type to
 * @param  *iter: Iterator of parser, lexer, cmd, in, out
 * @retval 
 */
int	set_tok_type_pipe(t_par_tok *par_tok, t_iter *iter)
{
	par_tok->redir_type[is_pipe] = true;
	iter[lex]++;
	iter[par]++;
	if (init_curr_par_tok() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	get_curr_par_tok()->redir_type[is_pipe] = true;
	return (EXIT_BREAK);
}

/**
 * @brief  Gets subshell token for current parser token
 * @note   Helper function of get_special_tok
 * @param  *iter: 
 * @retval int to indicate success or failure
 */
int	get_subshell_tok(t_iter *iter)
{
	char		*lex_tok;
	t_par_tok	*par_tok;

	if (init_curr_par_tok() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	lex_tok = get_curr_lex_tok();
	par_tok = get_curr_par_tok();
	par_tok->cmd_size++;
	par_tok->cmd = ft_str_arr_realloc(par_tok->cmd, par_tok->cmd_size);
	if (par_tok->cmd == NULL)
		return (EXIT_FAILURE);
	par_tok->cmd[iter[cmd]] = ft_strdup(lex_tok);
	if (par_tok->cmd[iter[cmd]] == NULL)
		return (EXIT_FAILURE);
	iter[cmd]++;
	par_tok->type = subshell;
	iter[lex]++;
	// iter[par]++;
	return (EXIT_BREAK);
}

bool	is_quote_token(char *lex_tok)
{
	if (ft_strchr(lex_tok, '\'') || ft_strchr(lex_tok, '\"'))
		return (true);
	return (false);
}

bool	is_redir_token(char *lex_tok)
{
	if (ft_strlen(lex_tok) == 2)
	{
		if (ft_strstr(lex_tok, "<<") || ft_strstr(lex_tok, ">>"))
			return (true);
	}
	if (ft_strlen(lex_tok) == 1)
	{
		if (ft_strchr(lex_tok, '<') || ft_strchr(lex_tok, '>'))
			return (true);
		if (ft_strchr(lex_tok, '|'))
			return (true);
	}
	return (false);
}

bool	is_special_token(char *lex_tok)
{
	if (ft_strlen(lex_tok) == 2)
	{
		if (ft_strstr(lex_tok, "&&") || ft_strstr(lex_tok, "||"))
			return (true);
	}
	return (false);
}