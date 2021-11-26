/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:23 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/26 18:18:18 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	token_join(char ***tokens, int i)
{
	int		j;
	char	**split;

	j = 0;
	split = ft_split(*tokens[i], '\"');
	while (split[j])
		printf("split: '%s'\n", split[j++]);
	// ft_free_str(&(*tokens[i]));
	// if (ft_str_arr_len(split) > 1)
	// {
	// 	while (ft_strhas(split[j], '\"') == false)
	// 	{
	// 		*tokens[i] = ft_strstrjoin(*tokens[i], split[j], NULL);
	// 		j++;
	// 	}

	// }

	return (EXIT_SUCCESS);
}

int	join_quotes(char ***tokens)
{
	int		i;
	// char	*start;
	// char	*end;

	// FOR TESTING TO COMPILE WHILE NOT FINISHEd ONLY
	// return (EXIT_SUCCESS);
	//
	i = 0;
	while (*tokens[i] && ft_strhas(*tokens[i], "\"")  == false)
		i++;
	if (*tokens[i] != NULL)
		token_join(tokens, i);
	return (EXIT_SUCCESS);
}
