/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:34:02 by tschmitt          #+#    #+#             */
/*   Updated: 2021/10/29 22:18:45 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	lexer(char *line)
{
	char	**tokens;

	tokens = ft_split_set(line, " \t\r\v\f\n");
	if (tokens == NULL)
		return (EXIT_FAILURE);
	if (parser(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
