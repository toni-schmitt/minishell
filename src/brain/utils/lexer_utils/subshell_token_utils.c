/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:35:19 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/09 22:37:17 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"

bool	token_is_subshell(char *token)
{
	if (ft_strchr(token, '(') != NULL \
	|| ft_strchr(token, ')') != NULL)
		return (true);
	return (false);
}

int	get_subshell_count(char *tokens[], int i)
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

int	jump_to_end_of_subshell(char *tokens[], int i)
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
