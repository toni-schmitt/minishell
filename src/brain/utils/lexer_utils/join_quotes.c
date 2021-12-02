/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:23 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/02 19:56:17 by tblaase          ###   ########.fr       */
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

static int	combine_loop(char ***tokens, t_quotes *quo)
{
	while (*tokens && (*tokens)[quo->i]
		&& ft_strhas((*tokens)[quo->i], quo->quote) == false)
	{
		(*tokens)[quo->j] = ft_strstrjoin((*tokens)[quo->j],
				(*tokens)[quo->i], " ");
		if ((*tokens)[quo->j] == NULL)
			return (EXIT_FAILURE);
		ft_free_single_str(tokens, quo->i);
	}
	return (EXIT_SUCCESS);
}

static int	start_one(char ***tokens, t_quotes *quo)
{
	*tokens = ft_add_single_str(tokens, quo->i, quo->start);
	if (*tokens == NULL)
		return (EXIT_FAILURE);
	(*tokens)[quo->i] = ft_realloc_str((*tokens)[quo->i], quo->len);
	if ((*tokens)[quo->i] == NULL)
		return (EXIT_FAILURE);
	quo->i++;
	if (ft_strlen(quo->start) > 1 && ft_strhas(quo->start + 1, quo->quote))
	{
		quo->end = ft_strdup(ft_strchr(quo->start + 1, *quo->quote) + 1);
		(*tokens)[quo->i] = ft_realloc_str((*tokens)[quo->i],
				ft_strclen(quo->start + 1, *quo->quote) + 2);
		if (ft_strlen(quo->end) >= 1)
			*tokens = ft_add_single_str(tokens, quo->i, quo->end);
		return (EXIT_SUCCESS);
	}
	quo->j = quo->i;
	quo->i++;
	return (2);
}

/*static int	double_start_one(char ***tokens, t_quotes *quo)
{
	*tokens = ft_add_single_str(tokens, quo-> i, quo->start);
	if (*tokens == NULL)
		return (EXIT_FAILURE);
	(*tokens)[quo->i] = ft_realloc_str((*tokens)[quo->i], quo->len);
	if ((*tokens)[quo->i] == NULL)
		return (EXIT_FAILURE);
	quo->i++;
	if (ft_strlen(quo->start) > 1 && ft_strhas(quo->start + 1, "\""))
	{
		quo->end = ft_strdup(ft_strchr(quo->start + 1, '\"') + 1);
		(*tokens)[quo->i] = ft_realloc_str((*tokens)[quo->i],
				ft_strclen(quo->start + 1, '\"') + 2);
		if (ft_strlen(quo->end) >= 1)
			*tokens = ft_add_single_str(tokens, quo->i, quo->end);
		ft_free_str(&quo->end);
		ft_free_str(&quo->start);
		return (EXIT_SUCCESS);
	}
	ft_free_str(&quo->start);
	quo->j = quo->i;
	quo->i++;
	return (2);
}*/

static int	start_two(char ***tokens, t_quotes *quo)
{
	quo->i++;
	if (ft_strhas((*tokens)[quo->i], quo->quote) == true)
	{
		(*tokens)[quo->j] = ft_strstrjoin((*tokens)[quo->j],
				(*tokens)[quo->i], " ");
		if ((*tokens)[quo->j] == NULL)
			return (EXIT_FAILURE);
		quo->end = ft_strchr((*tokens)[quo->j] + 1, *quo->quote);
		if (ft_strlen(quo->end) >= 2)
		{
			quo->end = ft_strdup(quo->end + 1);
			if (quo->end == NULL)
				return (EXIT_FAILURE);
			(*tokens)[quo->j] = ft_realloc_str((*tokens)[quo->j],
					ft_strclen((*tokens)[quo->j] + 1, '\'') + 2);
			if ((*tokens)[quo->j] == NULL)
				return (EXIT_FAILURE);
		}
		else
			quo->end = NULL;
		if (ft_strlen(quo->end) >= 1)
		{
			ft_free_str(&(*tokens)[quo->i]);
			(*tokens)[quo->i] = ft_strdup(quo->end);
			if ((*tokens)[quo->i] == NULL)
				return (EXIT_FAILURE);
		}
		else
			ft_free_single_str(tokens, quo->i);
		return (EXIT_SUCCESS);
	}
	return (2);
}

static int	end(char ***tokens, t_quotes *quo)
{
	quo->end = ft_strdup((*tokens)[quo->i]);
	if (quo->end == NULL)
		return (EXIT_FAILURE);
	quo->len = ft_strclen(quo->end, *quo->quote) + 1;
	(*tokens)[quo->j] = ft_append_len_div(&(*tokens)[quo->j],
			quo->end, quo->len, " ");
	if ((*tokens)[quo->j] == NULL)
		return (EXIT_FAILURE);
	if (quo->end[quo->len] == '\0')
		ft_free_single_str(tokens, quo->i);
	else
	{
		ft_free_str(&(*tokens)[quo->i]);
		(*tokens)[quo->i] = ft_strdup(quo->end + quo->len);
		if ((*tokens)[quo->i] == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
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
	// take care of start=\"hi\" and "hi""yolo""lul"
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
	if (quo->len > 0)
	{
		check = start_one(tokens, quo);
		if (check != 2)
			return (end_token_join(quo, check));
	}
	/*else if (quo->is_single == false && quo->len > 0)
	{
		check = start_double_one(tokens, quo);
		if (check != 2)
			return (end_token_join(quo, check));
	}*/
	else
	{
		check = start_two(tokens, quo);
		if (check != 2)
			return (end_token_join(quo, check));
	}
	/*
	else if (quo->is_single == false)
	{
		quo->i++;
		if (ft_strhas((*tokens)[quo->i], "\"") == true)
		{
			(*tokens)[quo->j] = ft_strstrjoin((*tokens)[quo->j],
					(*tokens)[quo->i], " ");
			quo->end = ft_strchr((*tokens)[quo->j] + 1, *quo->quote);
			if (ft_strlen(quo->end) >= 2)
			{
				quo->end = ft_strdup(quo->end + 1);
				(*tokens)[quo->j] = ft_realloc_str((*tokens)[quo->j],
						ft_strclen((*tokens)[quo->j] + 1, '\"') + 2);
			}
			else
				quo->end = NULL;
			if (ft_strlen(quo->end) >= 1)
			{
				ft_free_str(&(*tokens)[quo->i]);
				(*tokens)[quo->i] = ft_strdup(quo->end);
			}
			else
				ft_free_single_str(tokens, quo->i);
			ft_free_str(&quo->start);
			ft_free_str(&quo->end);
			return (EXIT_SUCCESS);
		}
	}*/
	if (combine_loop(tokens, quo) == EXIT_FAILURE)
		return (end_token_join(quo, EXIT_FAILURE));
	if ((*tokens)[quo->i] == NULL)
		return (end_token_join(quo, EXIT_SUCCESS));
	if (end(tokens, quo) == EXIT_FAILURE)
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
		if ((*tokens)[i] && (ft_strhas((*tokens)[i], "\"") == true
			|| ft_strhas((*tokens)[i], "\'") == true))
		{
			if (token_join(tokens, i) == EXIT_FAILURE)
				return (EXIT_FAILURE);
			else
			{
				if (ft_strhas((*tokens)[i], "\'") == false
					&& ft_strhas((*tokens)[i], "\"") == false)
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
