/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/02 15:00:19 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/14 16:01:43 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "lexer_utils.h"

bool	is_quote_token(char *lex_tok);

static bool	is_redir(char *lex_tok)
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
	}
	return (false);
}

static bool	is_special(char *lex_tok)
{
	if (ft_strlen(lex_tok) == 1)
	{
		if ((ft_strchr(lex_tok, '<') && !ft_strstr(lex_tok, "<<")) \
		|| (ft_strchr(lex_tok, '>') && !ft_strstr(lex_tok, ">>")) \
		|| (ft_strchr(lex_tok, '|') && !ft_strstr(lex_tok, "||")))
			return (true);
	}
	if (ft_strlen(lex_tok) == 2)
	{
		if (ft_strstr(lex_tok, "&&") || ft_strstr(lex_tok, "||") \
		|| ft_strstr(lex_tok, "<<") || ft_strstr(lex_tok, ">>"))
			return (true);
	}
	return (false);
}

static bool	is_correct_special(char *lex_tok)
{
	if (ft_strchr(lex_tok, '(') && ft_strchr(lex_tok, ')'))
		return (true);
	if (ft_strlen(lex_tok) != 2)
	{
		if (ft_strstr(lex_tok, "&&") || ft_strstr(lex_tok, "||") \
		|| ft_strstr(lex_tok, "<<") || ft_strstr(lex_tok, ">>"))
			return (false);
		if (ft_strchr(lex_tok, '&'))
			return (false);
	}
	if (ft_strlen(lex_tok) != 1)
	{
		if ((ft_strchr(lex_tok, '<') && !ft_strstr(lex_tok, "<<")) \
		|| (ft_strchr(lex_tok, '>') && !ft_strstr(lex_tok, ">>")) \
		|| (ft_strchr(lex_tok, '|') && !ft_strstr(lex_tok, "||")))
			return (false);
	}
	return (true);
}

static bool	is_correc_pipe(char *curr, char *next)
{
	if (ft_strlen(curr) == 1 && ft_strchr(curr, '|'))
	{
		if (next == NULL)
			return (false);
		if (ft_strlen(next) == 2)
		{
			if (ft_strstr(next, "&&") || ft_strstr(next, "||"))
				return (false);
		}
	}
	return (true);
}

/**
 * @brief  Checks if tokens have correct syntax
 * @note   
 * @param  *lex_toks[]: Tokens to check syntax from
 * @retval true on valid syntax, false on invalid syntax
 */
bool	is_valid_syntax(char *lex_toks[])
{
	int	i;

	i = 0;
	while (lex_toks[i])
	{
		if (!is_quote_token(lex_toks[i]))
		{
			if (i == 0 || get_lex_toks()[i + 1] == NULL)
				if (ft_strlen(lex_toks[i]) == 2 && (ft_strstr(lex_toks[i], "&&")
						|| ft_strstr(lex_toks[i], "||")))
					return (false);
			if (get_lex_toks()[i + 1] == NULL)
				if (is_redir(lex_toks[i]))
					return (false);
			if (!is_correct_special(lex_toks[i]))
				return (false);
			if (!is_correc_pipe(lex_toks[i], lex_toks[i + 1]))
				return (false);
			if (ft_strchr(lex_toks[i], '(') && ft_strchr(lex_toks[i], ')'))
				if (i != 0 && !is_special(lex_toks[i - 1]))
					return (false);
		}
		i++;
	}
	return (true);
}
