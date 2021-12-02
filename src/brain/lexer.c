/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:34:02 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/02 15:06:51 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
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

static char	*get_subshell_token(char *tokens[], int *i)
{
	char	*subshell_token;
	int		subshell_count;

	subshell_token = NULL;
	subshell_count = get_subshell_count(tokens, *i);
	while (tokens[*i] && subshell_count)
	{
		if (ft_strchr(tokens[*i], ')') && subshell_count == 1)
			return (get_end_of_subshell(tokens, i, subshell_token));
		subshell_token = ft_append(&subshell_token, tokens[*i]);
		if (subshell_token == NULL)
			return (NULL);
		subshell_token = ft_append(&subshell_token, " ");
		if (subshell_token == NULL)
			return (NULL);
		if (token_is_subshell(tokens[*i]))
			subshell_count--;
		(*i)++;
	}
	return (subshell_token);
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
		if (token_is_subshell(tokens[i]))
			adjusted[j] = get_subshell_token(tokens, &i);
		else if (!token_is_unadjusted(tokens[i]))
			adjusted[j] = ft_strdup(tokens[i++]);
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
	if (join_quotes(&tokens) == EXIT_FAILURE)
	{
		ft_free((void *)&tokens);
		return (EXIT_FAILURE);
	}
	if (tokens == NULL)
		return (EXIT_FAILURE);
	tokens = adjust_tokens(tokens);
	if (tokens == NULL)
		return (EXIT_FAILURE);
	if (!is_valid_syntax(tokens))
	{
		printf("minishell: Invalid Syntax at unspecified token\n");
		ft_free_str_array(&tokens);
		return (EXIT_SUCCESS);
	}
	if (parser(tokens) == EXIT_FAILURE)
	{
		ft_free_str_array(&tokens);
		return (EXIT_FAILURE);
	}
	ft_free_str_array(&tokens);
	return (EXIT_SUCCESS);
}
