/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_line_syntax.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/17 15:42:45 by toni              #+#    #+#             */
/*   Updated: 2021/12/17 17:18:33 by toni             ###   ########.fr       */
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

static int	jump_to_end_of_symbol(char *line, char symbol, int i)
{
	while (line[i] && line[i] != symbol)
		i++;
	return (i);
}

static bool	is_correct_subshell(char *line, int i)
{
	while (i > 0 && line[i] && ft_isspace(line[i]))
		i--;
	if (i > 0 && (line[i] != '&' && line[i] != '|'))
		return (false);
	return (true);
}

bool	is_valid_line_syntax(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '\'')
			i = jump_to_end_of_symbol(line, '\'', i);
		if (line[i] == '\"')
			i = jump_to_end_of_symbol(line, '\"', i);
		if (line[i] == '(')
			if (!is_correct_subshell(line, i - 1))
				return (false);
		if (line[i] == ';' || line[i] == '\\')
			return (false);
		i++;
	}
	return (true);
}
