/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:35:35 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/10 00:08:08 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_parser_tok	*get_tokens(char *lexer_tokens[])
{
	t_parser_tok	*tokens;

	(void)lexer_tokens;
	tokens = NULL;
	return (tokens);
}

int	parser(char *lexer_tokens[])
{
	t_parser_tok	*tokens;

	tokens = get_tokens(lexer_tokens);
	if (tokens == NULL)
		return (EXIT_FAILURE);
	if (expander(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
