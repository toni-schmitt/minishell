/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_redir_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 19:21:14 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/26 19:21:39 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "minishell.h"
#include "parser_utils.h"

int	get_tok_redir_type(char *lex_tok)
{
	if (ft_strlen(lex_tok) == 1)
	{
		if (ft_strchr(lex_tok, '>'))
			return (is_out);
		if (ft_strchr(lex_tok, '<'))
			return (is_in);
		if (ft_strchr(lex_tok, '|'))
			return (is_pipe);
	}
	if (ft_strlen(lex_tok) == 2)
	{
		if (ft_strstr(lex_tok, ">>"))
			return (is_out_append);
		if (ft_strstr(lex_tok, "<<"))
			return (is_in_heredoc);
	}
	return (0);
}

bool	try_get_tok_redir_buf(char ****buf, size_t **buf_size, \
t_iter **buf_iter)
{
	if ((ft_strchr(get_curr_lex_tok(), '>') \
	&& ft_strlen(get_curr_lex_tok()) == 1) \
	|| (ft_strstr(get_curr_lex_tok(), ">>") \
	&& ft_strlen(get_curr_lex_tok()) == 2))
	{
		*buf = &get_curr_par_tok()->out;
		*buf_size = &get_curr_par_tok()->out_size;
		*buf_iter = &get_iter()[out];
		return (true);
	}
	else if ((ft_strchr(get_curr_lex_tok(), '<') \
	&& ft_strlen(get_curr_lex_tok()) == 1) \
	|| (ft_strstr(get_curr_lex_tok(), "<<") \
	&& ft_strlen(get_curr_lex_tok()) == 2))
	{
		*buf = &get_curr_par_tok()->in;
		*buf_size = &get_curr_par_tok()->in_size;
		*buf_iter = &get_iter()[in];
		return (true);
	}
	return (false);
}
