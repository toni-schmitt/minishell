/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:39:06 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/04 23:23:39 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"

static int	get_tokens(t_par_tok *par_toks[])
{
	t_exp_tok	**exp_toks;

	exp_toks = NULL;
	set_exec_toks(exp_toks);
	(void)par_toks;
	return (EXIT_FAILURE);
}

static void	free_exp_toks(t_exp_tok *exp_toks[])
{
	int	i;

	i = 0;
	while (exp_toks[i])
	{
		ft_free_str_array(&exp_toks[i]->cmd);
		free(exp_toks[i]->in);
		free(exp_toks[i]->out);
		free(exp_toks[i]);
		i++;
	}
	free(exp_toks);
}

int	expander(t_par_tok *parser_tokens[])
{
	t_exp_tok	**exp_toks;

	if (check_for_heredoc(parser_tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (get_tokens(parser_tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exp_toks = get_exec_toks();
	if (executor(exp_toks) == EXIT_FAILURE)
	{
		free_exp_toks(exp_toks);
		return (EXIT_FAILURE);
	}
	free_exp_toks(exp_toks);
	return (EXIT_SUCCESS);
}
