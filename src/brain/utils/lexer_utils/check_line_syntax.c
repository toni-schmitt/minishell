/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:42:45 by toni              #+#    #+#             */
/*   Updated: 2021/12/17 16:03:26 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "lexer_utils.h"

int	exit_on_syntax_error(void)
{
	ft_fprintf(STDERR_FILENO, "minishell: Invalid Syntax at token\n");
	set_err_code(EXIT_SYNTAX_ERROR);
	ft_free_split(get_lex_toks());
	return (EXIT_SYNTAX_ERROR);
}

bool	is_valid_line_syntax(char *line)
{
	(void)line;
	return (true);
}
