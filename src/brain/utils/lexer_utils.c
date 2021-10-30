/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 22:23:11 by toni              #+#    #+#             */
/*   Updated: 2021/10/31 00:24:52 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_special_char(char curr, char next)
{
	if (curr == '|')
		return (true);
	if (curr == '>')
		return (true);
	if (curr == '<')
		return (true);
	if (curr == ';')
		return (true);
	if (curr == '&' && next && next == '&')
		return (true);
	return (false);
}

size_t	get_next_token_size(char *token, char next_special)
{
	size_t	size;

	size = 0;
	if (*token == next_special && *(token + 1) && *(token + 1) == next_special)
		return (2);
	else if (*token == next_special)
		return (1);
	while (*token && *token != next_special)
	{
		size++;
		token++;
	}
	return (size);
}

size_t	get_new_tokens_size(char **tokens)
{
	size_t	size;
	int		i;
	int		j;

	size = 0;
	i = 0;
	while (tokens[i])
	{
		if (token_is_unadjusted(tokens[i]))
		{
			j = 0;
			while (tokens[i][j])
			{
				if (is_special_char(tokens[i][j], tokens[i][j + 1]))
					size += 2;
				j++;
			}
			if (!is_special_char(tokens[i][j - 2], tokens[i][j - 1]))
				size++;
		}
		else
			size++;
		i++;
	}
	return (size);
}

char	get_next_special(char *token)
{
	while (*token)
	{
		if (*token == '|' || *token == '<' \
			|| *token == '>' || *token == ';')
			return (*token);
		if (*token == '&' && *(token + 1) && *(token + 1) == '&')
			return (*token);
		token++;
	}
	return ('\0');
}

bool	token_is_unadjusted(char *token)
{
	if (ft_strchr(token, '|') || ft_strchr(token, '<') \
	|| ft_strchr(token, '>') || ft_strchr(token, ';'))
		if (ft_strlen(token) != 1)
			return (true);
	if (ft_strstr(token, "&&"))
		if (ft_strlen(token) != 2)
			return (true);
	return (false);
}
