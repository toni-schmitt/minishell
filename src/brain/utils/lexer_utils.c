/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 22:23:11 by toni              #+#    #+#             */
/*   Updated: 2021/11/09 22:09:15 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"

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

static bool	token_is_subshell(char *token)
{
	if (ft_strchr(token, '(') != NULL \
	|| ft_strchr(token, ')') != NULL)
		return (true);
	return (false);
}

// echo hi && ( echo hi ; ( echo hi )) && ( echo hi )
static int	get_subshell_count(char *tokens[], int i)
{
	int	count;
	int	opened_brackets;

	count = 0;
	opened_brackets = 0;
	while (tokens[i])
	{
		if (ft_strchr(tokens[i], '('))
		{
			opened_brackets++;
			count++;
		}
		else if (ft_strchr(tokens[i], ')'))
		{
			opened_brackets--;
			count++;
		}
		if (opened_brackets == 0)
			break ;
		i++;
	}
	return (count);
}

static int	jump_to_end_of_subshell(char *tokens[], int i)
{
	int	subshell_count;

	subshell_count = get_subshell_count(tokens, i);
	while (tokens[i] && subshell_count)
	{
		if (token_is_subshell(tokens[i]))
			subshell_count--;
		i++;
	}
	return (i);
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
		{
			i = jump_to_end_of_subshell(tokens, i);
			size++;
		}
		else if (token_is_unadjusted(tokens[i]))
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
