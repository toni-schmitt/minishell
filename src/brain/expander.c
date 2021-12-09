/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:39:06 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/09 18:40:41 by tblaase          ###   ########.fr       */
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
		free(exp_toks[i]);
		i++;
	}
	free(exp_toks);
	reset_exp_toks();
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

static int	init(t_exp_tok **exp_tok)
{
	*exp_tok = malloc(sizeof(**exp_tok));
	if (*exp_tok == NULL)
		return (EXIT_FAILURE);
	(*exp_tok)->cmd = NULL;
	(*exp_tok)->in = 0;
	(*exp_tok)->out = 1;
	return (EXIT_SUCCESS);
}

static int	get_tokens(t_par_tok *par_toks[])
{
	t_exp_tok	**exp_toks;
	int			i;

	exp_toks = ft_calloc(get_tok_size(par_toks) + 1, sizeof(*exp_toks));
	if (exp_toks == NULL)
		return (EXIT_FAILURE);
	set_exp_toks(exp_toks);
	i = 0;
	while (par_toks[i])
	{
		if (init(&exp_toks[i]) == EXIT_FAILURE)
			return (free_exp_toks(exp_toks, EXIT_FAILURE));
		if (par_toks[i]->cmd)
		{
			exp_toks[i]->cmd = ft_str_arr_dup(par_toks[i]->cmd);
			if (exp_toks[i]->cmd == NULL)
				return (free_exp_toks(exp_toks, EXIT_FAILURE));
		}
		if (par_toks[i]->redir_type[is_in_heredoc])
			if (wait_for_heredoc(par_toks[i], exp_toks[i]) == EXIT_FAILURE)
				return (free_exp_toks(exp_toks, EXIT_FAILURE));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	expander(t_par_tok *par_toks[])
{
	t_exp_tok	**exp_toks;
	int			i;
	int			exit_status;

	i = 0;
	exit_status = 0;
	if (get_tokens(par_toks) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exp_toks = get_exp_toks();
	while (par_toks && par_toks[i] && exp_toks && exp_toks[i])
	{
		printf("success, entering while loop in expander\n");
		if (par_toks[i]->type != and && par_toks[i]->type != or)
		{
			printf("found cmd without && and ||: %s\n", exp_toks[i]->cmd[0]);
			// if (par_toks[i]->in != NULL || par_toks[i]->out != NULL)
			if (handle_redir(par_toks[i], exp_toks[i]) == EXIT_SUCCESS)
				exit_status = executor(exp_toks[i]);
			else
				exit_status = 1;
		}
		else if (exit_status == 0 && par_toks[i]->type == and)
		{
			i++;
			if (handle_redir(par_toks[i], exp_toks[i]) == EXIT_SUCCESS)
				exit_status = executor(exp_toks[i]);
			else
				exit_status = 1;
		}
		else if (exit_status != 0 && par_toks[i]->type == or)
		{
			i++;
			if (handle_redir(par_toks[i], exp_toks[i]) == EXIT_SUCCESS)
				exit_status = executor(exp_toks[i]);
			else
				exit_status = 1;
		}
		else
		{
			printf("sth went wrong, exiting now with %d\n", exit_status);
			return (exit_status);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
