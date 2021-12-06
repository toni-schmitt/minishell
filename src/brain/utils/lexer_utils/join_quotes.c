/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:23 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/04 23:24:37 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer_utils.h"

static int	get_quotes_pos(char *tok)
{
	int	pos_single;
	int	pos_double;

	pos_single = ft_strclen(tok, '\'');
	pos_double = ft_strclen(tok, '\"');
	if (pos_single < pos_double)
		return (pos_single);
	return (pos_double);
}

static t_quotes	*init_quo(char ***tokens, int i)
{
	t_quotes	*quo;

	quo = ft_calloc(1, sizeof(t_quotes));
	quo->i = i;
	quo->j = i;
	quo->start = (*tokens)[i];
	quo->len = get_quotes_pos(quo->start);
	quo->start = ft_strdup(quo->start + quo->len);
	if (quo->start == NULL)
	{
		free(quo);
		quo = NULL;
		return (NULL);
	}
	if (*quo->start == '\'')
		quo->quote = ft_strdup("\'");
	else
		quo->quote = ft_strdup("\"");
	if (quo->quote == NULL)
	{
		ft_free_str(&quo->start);
		free(quo);
		return (NULL);
	}
	return (quo);
}

static int	end_token_join(t_quotes *quo, int ret_status)
{
	ft_free_str(&quo->start);
	ft_free_str(&quo->end);
	ft_free_str(&quo->quote);
	free(quo);
	return (ret_status);
}

static int	token_join(char ***tokens, int i)
{
	t_quotes	*quo;
	int			check;

	quo = init_quo(tokens, i);
	if (quo == NULL)
		return (EXIT_FAILURE);
	check = token_join_all_starts(tokens, quo, i);
	if (check != 2)
		return (end_token_join(quo, check));
	if (combine_loop(tokens, quo) == EXIT_FAILURE)
		return (end_token_join(quo, EXIT_FAILURE));
	if ((*tokens)[quo->i] == NULL)
		return (end_token_join(quo, EXIT_SUCCESS));
	if (token_join_end_one(tokens, quo) == EXIT_FAILURE)
		return (end_token_join(quo, EXIT_FAILURE));
	return (end_token_join(quo, EXIT_SUCCESS));
}

int	join_quotes(char ***tokens)
{
	int		i;

	i = 0;
	if (*tokens == NULL)
		return (EXIT_FAILURE);
	while ((*tokens)[i])
	{
		if ((*tokens)[i] && (ft_strhas((*tokens)[i], "\'\"") == true))
		{
			if (token_join(tokens, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			else
			{
				if (ft_strhas((*tokens)[i], "\'\"") == false)
					i += 2;
				else
					i++;
			}
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
