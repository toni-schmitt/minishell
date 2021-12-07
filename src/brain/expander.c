/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:39:06 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/07 16:42:23 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"

static int	free_exp_toks(t_exp_tok *exp_toks[], int exit_status)
{
	int	i;

	i = 0;
	while (exp_toks[i])
	{
		ft_free_str_array(&exp_toks[i]->cmd);
		// free(exp_toks[i]->in);
		// free(exp_toks[i]->out);
		free(exp_toks[i]);
		i++;
	}
	free(exp_toks);
	return (exit_status);
}

static size_t	get_tok_size(t_par_tok *par_toks[])
{
	size_t	size;

	size = 0;
	while (par_toks[size])
		size++;
	return (size);
}

static int	get_tokens(t_par_tok *par_toks[])
{
	t_exp_tok	**exp_toks;
	int			i;

	exp_toks = ft_calloc(get_tok_size(par_toks) + 1, sizeof(*exp_toks));
	if (exp_toks == NULL)
		return (EXIT_FAILURE);
	set_exec_toks(exp_toks);
	i = 0;
	while (par_toks[i])
	{
		exp_toks[i] = ft_calloc(1, sizeof(*exp_toks[i]));
		if (exp_toks[i] == NULL)
			return (free_exp_toks(exp_toks, EXIT_FAILURE));
		if (par_toks[i]->cmd)
		{
			exp_toks[i]->cmd = ft_str_arr_dup(par_toks[i]->cmd);
			if (exp_toks[i]->cmd == NULL)
				return (free_exp_toks(exp_toks, EXIT_FAILURE));
		}
		if (par_toks[i]->redir_type[is_in_heredoc])
		{
			if (wait_for_heredoc(par_toks[i], exp_toks[i]) == EXIT_FAILURE)
				return (free_exp_toks(exp_toks, EXIT_FAILURE));
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

int	expander(t_par_tok *parser_tokens[])
{
	t_exp_tok	**exp_toks;

	if (get_tokens(parser_tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exp_toks = get_exec_toks();
	if (executor(exp_toks) == EXIT_FAILURE)
	{
		free_exp_toks(exp_toks, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	free_exp_toks(exp_toks, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

/* for checking if a command is valid
	if (access(argv[1], F_OK) != 0)
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
*/