/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   join_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 15:39:23 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/26 16:50:39 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	token_join(char ***tokens, int i, int j)
{
	(void)tokens;
	(void)i;
	(void)j;
	return (EXIT_SUCCESS);
}

int	join_quotes(char ***tokens)
{
	int		i;
	int		j;
	// char	*start;
	// char	*end;

	return (EXIT_SUCCESS);
	i = 0;
	while (*tokens && *tokens[i])
	{
		j = 0;
		while (*tokens[i][j] && *tokens[i][j] != '\"')
			j++;
		if (*tokens[i][j] == '\0')
			i++;
		else
			token_join(tokens, i, j);
	}
	return (EXIT_SUCCESS);
}
