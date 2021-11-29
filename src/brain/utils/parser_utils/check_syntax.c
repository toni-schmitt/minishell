/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 20:28:49 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/29 19:45:14 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "minishell.h"
#include "parser_utils.h"

/**
 * @brief  Checks if current lexer tokens has valid syntax
 * @note   
 * @param  *lex_tok: Token to check syntax from
 * @retval true if is valid syntax, false if is invalid syntax
 */
bool	is_valid_syntax(char *lex_tok)
{
	(void)lex_tok;
	return (EXIT_FAILURE);
}
