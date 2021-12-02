/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:23 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/01 19:45:43 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int combine_loop(char ***tokens, int i, int j, bool is_single)
{
	while (is_single && *tokens && (*tokens)[i] && ft_strhas((*tokens)[i], "\'") == false)
	{
		(*tokens)[j] = ft_strstrjoin((*tokens)[j], (*tokens)[i], " ");
		if ((*tokens)[j] == NULL)
			return (EXIT_FAILURE);
		ft_free_single_str(tokens, i);
	}
	while (is_single == false && *tokens && (*tokens)[i] && ft_strhas((*tokens)[i], "\"") == false)
	{
		(*tokens)[j] = ft_strstrjoin((*tokens)[j], (*tokens)[i], " ");
		if ((*tokens)[j] == NULL)
			return (EXIT_FAILURE);
		ft_free_single_str(tokens, i);
	}
	return (EXIT_SUCCESS);
}

static int	single_start_one(char ***tokens, int *i, int *j, char *start)
{
	// implement the lexer struct
	/**tokens = ft_add_single_str(tokens, i, start);
	if (*tokens == NULL)
	{
		ft_free_str(&start);
		return (EXIT_FAILURE);
	}
	(*tokens)[i] = ft_realloc_str((*tokens)[i], len);
	i++;
	if (ft_strlen(start) > 1 && ft_strhas(start + 1, "\'"))
	{
		end = ft_strdup(ft_strchr(start + 1, '\'') + 1);
		(*tokens)[i] = ft_realloc_str((*tokens)[i], ft_strclen(start + 1, '\'') + 2);
		if (ft_strlen(end) >= 1)
			*tokens = ft_add_single_str(tokens, i, end);
		ft_free_str(&end);
		ft_free_str(&start);
		return (EXIT_SUCCESS);
	}
	ft_free_str(&start);
	j = i;
	i++;*/
	return (EXIT_SUCCESS);
	(void)tokens,
	(void)i;
	(void)j,
	(void)start;
}

static int	token_join(char ***tokens, int i)
{
	char	*start = NULL;
	char	*end = NULL;
	int		len;
	int		j;
	bool	is_single;

	j = i;
	start = (*tokens)[i];
	len = get_quotes_pos(start);
	start = ft_strdup(start + len);
	if (start == NULL)
		return (EXIT_FAILURE);
	if (*start == '\'')
		is_single = true;
	else
		is_single = false;
	if (is_single == true && len > 0)
	{
		if (single_start_one(tokens, &i, &j, start) == EXIT_FAILURE)
			return (EXIT_FAILURE);
	}
	else if (is_single == false && len > 0)
	{
		*tokens = ft_add_single_str(tokens, i, start);
		if (*tokens == NULL)
			return (EXIT_FAILURE);
		(*tokens)[i] = ft_realloc_str((*tokens)[i], len);
		i++;
		if (ft_strlen(start) > 1 && ft_strhas(start + 1, "\""))
		{
			end = ft_strdup(ft_strchr(start + 1, '\"') + 1);
			(*tokens)[i] = ft_realloc_str((*tokens)[i], ft_strclen(start + 1, '\"') + 2);
			if (ft_strlen(end) >= 1)
				*tokens = ft_add_single_str(tokens, i, end);
			ft_free_str(&end);
			ft_free_str(&start);
			return (EXIT_SUCCESS);
		}
		ft_free_str(&start);
		j = i;
		i++;
	}
	else if (is_single == true)
	{
		i++;
		if (ft_strhas((*tokens)[i], "\'") == true)
		{
			(*tokens)[j] = ft_strstrjoin((*tokens)[j], (*tokens)[i], " ");
			end = ft_strchr((*tokens)[j] + 1, '\'');
			if (ft_strlen(end) >= 2)
			{
				end = ft_strdup(end + 1);
				(*tokens)[j] = ft_realloc_str((*tokens)[j], ft_strclen((*tokens)[j] + 1, '\'') + 2);
			}
			else
				end = NULL;
			if (ft_strlen(end) >= 1)
			{
				ft_free_str(&(*tokens)[i]);
				(*tokens)[i] = ft_strdup(end);
			}
			else
				ft_free_single_str(tokens, i);
			ft_free_str(&start);
			ft_free_str(&end);
			return (EXIT_SUCCESS);
		}
	}
	else if (is_single == false)
	{
		i++;
		if (ft_strhas((*tokens)[i], "\"") == true)
		{
			(*tokens)[j] = ft_strstrjoin((*tokens)[j], (*tokens)[i], " ");
			end = ft_strchr((*tokens)[j] + 1, '\"');
			if (ft_strlen(end) >= 2)
			{
				end = ft_strdup(end + 1);
				(*tokens)[j] = ft_realloc_str((*tokens)[j], ft_strclen((*tokens)[j] + 1, '\"') + 2);
			}
			else
				end = NULL;
			if (ft_strlen(end) >= 1)
			{
				ft_free_str(&(*tokens)[i]);
				(*tokens)[i] = ft_strdup(end);
			}
			else
				ft_free_single_str(tokens, i);
			ft_free_str(&start);
			ft_free_str(&end);
			return (EXIT_SUCCESS);
		}
	}
	if (combine_loop(tokens, i, j, is_single) == EXIT_FAILURE)
	{
		ft_free_str(&start);
		return (EXIT_FAILURE);
	}
	if ((*tokens)[i] == NULL)
	{
		ft_free_str(&start);
		return (EXIT_SUCCESS);
	}
	end = ft_strdup((*tokens)[i]);
	if (is_single)
		len = ft_strclen(end, '\'') + 1;
	else
		len = ft_strclen(end, '\"') + 1;
	(*tokens)[j] = ft_append_len_div(&(*tokens)[j], end, len, " ");
	if (end[len] == '\0')
		ft_free_single_str(tokens, i);
	else
	{
		ft_free_str(&(*tokens)[i]);
		(*tokens)[i] = ft_strdup(end + len);
	}
	ft_free_str(&end);
	return (EXIT_SUCCESS);
}

int	join_quotes(char ***tokens)
{
	int		i;

	i = 0;
	if (*tokens == NULL)
		return (EXIT_FAILURE);
	while ((*tokens)[i])
	{
		if ((*tokens)[i] && (ft_strhas((*tokens)[i], "\"") == true
			|| ft_strhas((*tokens)[i], "\'") == true))
		{
			if (token_join(tokens, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			else
			{
				if (ft_strhas((*tokens)[i], "\'") == false && ft_strhas((*tokens)[i], "\"") == false)
					i+=2;
				else
					i++;
			}
		}
		else
			i++;
	}
	return (EXIT_SUCCESS);
}
