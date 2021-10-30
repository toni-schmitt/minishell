/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:34:02 by tschmitt          #+#    #+#             */
/*   Updated: 2021/10/31 01:21:57 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"

static void	*free_tokens(char **tokens, char **adjusted)
{
	ft_free_split(tokens),
	ft_free_split(adjusted);
	return (NULL);
}

static char	*get_next_token(char **token)
{
	char	*next_token;
	char	*tmp;
	char	next_special;
	int		i;

	tmp = *token;
	next_special = get_next_special(tmp);
	next_token = ft_calloc(get_next_token_size(tmp, next_special) + 1, \
			sizeof(*next_token));
	if (next_token == NULL)
		return (NULL);
	i = 0;
	if (*tmp == next_special)
		while (*tmp && *tmp == next_special)
			next_token[i++] = *tmp++;
	else
		while (*tmp && *tmp != next_special)
			next_token[i++] = *tmp++;
	tmp = ft_substr(*token, i, ft_strlen(*token));
	if (*token == NULL)
		return (ft_free((void **)&next_token));
	free(*token);
	*token = tmp;
	return (next_token);
}

static char	**adjust_tokens(char **tokens)
{
	char	**adjusted;
	int		i;
	int		j;

	adjusted = ft_calloc(get_new_tokens_size(tokens) + 1, sizeof(*adjusted));
	if (adjusted == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (!token_is_unadjusted(tokens[i]))
		{
			adjusted[j] = ft_strdup(tokens[i]);
			i++;
		}
		else
			adjusted[j] = get_next_token(&tokens[i]);
		if (adjusted[j] == NULL)
			return (free_tokens(tokens, adjusted));
		j++;
	}
	ft_free_split(tokens);
	return (adjusted);
}

int	lexer(char *line)
{
	char	**tokens;

	tokens = ft_split_set(line, " \t\r\v\f\n");
	if (tokens == NULL)
		return (EXIT_FAILURE);
	tokens = adjust_tokens(tokens);
	if (tokens == NULL)
		return (EXIT_FAILURE);
	if (parser(tokens) == EXIT_FAILURE)
	{
		ft_free_split(tokens);
		return (EXIT_FAILURE);
	}
	ft_free_split(tokens);
	return (EXIT_SUCCESS);
}
