/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   subshell_token_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 22:35:19 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/26 22:28:28 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"

bool	token_is_subshell(char *token)
{
	if (token[0] == '(' || ft_strchr(token, ')') != NULL)
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

char	*get_end_of_subshell(char *tokens[], int *i, char *sub_tok)
{
	char	*tmp;
	int		sub_len;

	sub_len = ft_strchr(tokens[*i], ')') - tokens [*i];
	tmp = ft_substr(tokens[*i], 0, sub_len + 1);
	sub_tok = ft_append(&sub_tok, tmp);
	free(tmp);
	tmp = tokens[*i];
	tokens[*i] = ft_substr(tmp, sub_len + 1, ft_strlen(tokens[*i]));
	free(tmp);
	return (sub_tok);
}
