/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:35:27 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/26 20:23:33 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"

bool	is_special_char(char curr, char next)
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
		if (token_is_subshell(tokens[i]))
			i = jump_to_end_of_subshell(tokens, i) - 1;
		else if (token_is_unadjusted(tokens[i]))
		{
			j = 0;
			while (tokens[i][j])
			{
				if (is_special_char(tokens[i][j], tokens[i][j + 1]))
					size += 2;
				j++;
			}
		}
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
	if ((ft_strchr(token, '|') && !ft_strstr(token, "||")) \
	|| (ft_strchr(token, '<') && !ft_strstr(token, "<<")) \
	|| (ft_strchr(token, '>') && !ft_strstr(token, ">>")))
		if (ft_strlen(token) != 1)
			return (true);
	if (ft_strstr(token, "&&") || ft_strstr(token, "<<") \
	|| ft_strstr(token, ">>") || ft_strstr(token, "||"))
		if (ft_strlen(token) != 2)
			return (true);
	return (false);
}
