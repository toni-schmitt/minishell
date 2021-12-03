/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 13:44:26 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/03 13:57:27 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static int	start_two_utils(char ***tokens, t_quotes *quo)
{
	if (ft_strlen(quo->end) >= 2)
	{
		quo->end = ft_strdup(quo->end + 1);
		if (quo->end == NULL)
			return (EXIT_FAILURE);
		(*tokens)[quo->j] = ft_realloc_str((*tokens)[quo->j],
				ft_strclen((*tokens)[quo->j] + 1, *quo->quote) + 2);
		if ((*tokens)[quo->j] == NULL)
			return (EXIT_FAILURE);
	}
	else
		quo->end = NULL;
	return (EXIT_SUCCESS);
}

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
		if (start_two_utils(tokens, quo) == EXIT_FAILURE)
			return (EXIT_FAILURE);
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

static int	special_start(char ***tokens, t_quotes *quo, int i)
{
	quo->end = ft_strchr(quo->start + 1, *quo->quote);
	if (ft_strlen(quo->end) > 1)
	{
		quo->end = ft_strdup(quo->end + 1);
		if (quo->end == NULL)
			return (EXIT_FAILURE);
	}
	else
		quo->end = NULL;
	quo->start = ft_realloc_str(quo->start,
			ft_strclen(quo->start + 1, *quo->quote) + 2);
	if (quo->start == NULL)
		return (EXIT_FAILURE);
	ft_free_str(&(*tokens)[i]);
	(*tokens)[i] = ft_strdup(quo->start);
	if (quo->end != NULL)
		ft_add_single_str(tokens, i, quo->end);
	return (EXIT_SUCCESS);
}

int	token_join_all_starts(char ***tokens, t_quotes *quo, int i)
{
	int	check;

	if (ft_strchr(quo->start + 1, *quo->quote) != NULL)
	{
		if (special_start(tokens, quo, i) == EXIT_FAILURE)
			return (EXIT_FAILURE);
		else
			return (EXIT_SUCCESS);
	}
	if (quo == NULL)
		return (EXIT_FAILURE);
	if (quo->len > 0)
	{
		check = start_one(tokens, quo);
		if (check != 2)
			return (check);
	}
	else
	{
		check = start_two(tokens, quo);
		if (check != 2)
			return (check);
	}
	return (2);
}
