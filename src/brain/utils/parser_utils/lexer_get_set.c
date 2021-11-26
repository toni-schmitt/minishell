/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_get_set.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:15:41 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/24 20:37:07 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "parser_utils.h"

static char	**_get_lex_toks(char **lex_toks)
{
	static char	**static_lex_toks = NULL;

	if (lex_toks == NULL)
		return (static_lex_toks);
	static_lex_toks = lex_toks;
	return (static_lex_toks);
}

char	*get_curr_lex_tok(void)
{
	return (get_lex_toks()[get_iter()[lex]]);
}

char	**get_lex_toks(void)
{
	return (_get_lex_toks(NULL));
}

void	set_lex_toks(char **lex_toks)
{
	_get_lex_toks(lex_toks);
}
