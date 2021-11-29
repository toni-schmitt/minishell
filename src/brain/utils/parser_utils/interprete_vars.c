/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete_vars.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:13:27 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/29 19:48:11 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "minishell.h"
#include "parser_utils.h"

/**
 * @brief  Interprets enviroment variables of current lexer token
 * @note   Frees current lex_tok if necessary
 * @param  *lex_tok: Current lexer token
 * @retval Returns interpreted lexer token
 */
char	*interprete_vars(char *lex_tok)
{
	char	*interpreted_token;

	(void)lex_tok;
	interpreted_token = NULL;
	return (interpreted_token);
}
