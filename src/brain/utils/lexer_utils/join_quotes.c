/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:23 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/30 22:55:32 by tblaase          ###   ########.fr       */
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
	//printf("len: %d\n", len);
	start = ft_strdup(start + len);
	if (*start == '\'')
		is_single = true;
	else
		is_single = false;
	//printf("start:@%s@, is_single=%d\n", start, is_single);
	//*tokens = ft_add_single_str(tokens, ++j, start); // try to implement the new function!!!!!!!!!!!!!!!!!!!!!
	if (*(*tokens)[j] != '\'' && *(*tokens)[j] != '\"')
	{
		(*tokens)[j++] = ft_realloc_str((*tokens)[i++], len);
		if ((*tokens)[j - 1] == NULL)
			return (EXIT_FAILURE);
		(*tokens)[j] = ft_in_front_div(&(*tokens)[i++], start, " ");
		if ((*tokens)[j] == NULL)
			return (EXIT_FAILURE);
	}
	else
	{
		i++;
		(*tokens)[j] = ft_strstrjoin((*tokens)[j], (*tokens)[i], " ");
		if ((*tokens)[j] == NULL)
			return (EXIT_FAILURE);
		ft_free_single_str(tokens, i);
	}
	if (is_single)
	{
		while ((*tokens)[i] != NULL && ft_strhas((*tokens)[i], "\'") == false)
		{
			(*tokens)[j] = ft_strstrjoin((*tokens)[j], (*tokens)[i], " ");
			//printf("appended:@%s@\n", (*tokens)[j]);
			ft_free_single_str(tokens, i);
		}
	}
	else
	{
		while ((*tokens)[i] != NULL && ft_strhas((*tokens)[i], "\"") == false)
		{
			(*tokens)[j] = ft_strstrjoin((*tokens)[j], (*tokens)[i], " ");
			//printf("appended:@%s@\n", (*tokens)[j]);
			ft_free_single_str(tokens, i);
		}
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
	//printf("end:@%s@\n", (*tokens)[j]);
	//if (is_single)
	//	end = ft_strdup(ft_strchr((*tokens)[i], '\''));
	//else
	//	end = ft_strdup(ft_strchr((*tokens)[i], '\"'));
	if (ft_strlen(end) == 1)
		ft_free_single_str(tokens, i);
	else
	{
		ft_free_str(&(*tokens)[i]);
		(*tokens)[i] = ft_strdup(end + len);
	}
	ft_free_str(&start);
	ft_free_str(&end);
	return (EXIT_SUCCESS);
}

int	join_quotes(char ***tokens)
{
	int		i;

	//return (EXIT_SUCCESS);
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
