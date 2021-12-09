/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:39:06 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/09 20:35:37 by toni             ###   ########.fr       */
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

static char	*get_subshell_cmd(char *cmd)
{
	char	*subshell_cmd;
	int		cmd_len;
	int		i;
	int		j;

	cmd_len = ft_strlen(cmd);
	subshell_cmd = ft_calloc(cmd_len + 1, sizeof(*subshell_cmd));
	if (subshell_cmd == NULL)
		return (NULL);
	i = 1;
	j = 0;
	while (i < cmd_len - 2)
	{
		subshell_cmd[j] = cmd[i];
		i++;
		j++;
	}
	return (subshell_cmd);
}

static int	handle_subshell(char *cmd)
{
	pid_t	pid;
	int		status;
	char	*cutted_cmd;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		cutted_cmd = get_subshell_cmd(cmd);
		if (cutted_cmd == NULL)
			return (EXIT_FAILURE);
		status = lexer(cutted_cmd);
		free(cutted_cmd);
		return (status);
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

static bool	is_redir(t_par_tok *par_tok)
{
	if (par_tok->redir_type[is_in] || par_tok->redir_type[is_in_heredoc] \
	|| par_tok->redir_type[is_out] || par_tok->redir_type[is_out_append] \
	|| par_tok->redir_type[is_pipe])
		return (true);
	return (false);
}

char		*interprete_env_var(char *lex_tok);

static int	repinterprete_env_vars(t_par_tok *par_toks[], t_exp_tok *exp_toks[])
{
	int	i;
	int	j;

	i = 0;
	while (par_toks[i] && exp_toks[i] && par_toks[i]->type == std)
	{
		j = 0;
		while (exp_toks[j])
		{
			exp_toks[i]->cmd[j] = interprete_env_var(exp_toks[i]->cmd[j]);
			if (exp_toks[i]->cmd[j] == NULL)
				return (EXIT_FAILURE);
			j++;
		}
	}
	return (EXIT_SUCCESS);
}

static int	handle_tokens(t_exp_tok *exp_toks[], t_par_tok *par_toks[])
{
	int	i;
	int	exit_status;

	i = 0;
	exit_status = EXIT_SUCCESS;
	while (exp_toks[i] && par_toks[i])
	{
		if (par_toks[i]->type == and || par_toks[i]->type == or)
		{
			if ((par_toks[i]->type == and && exit_status != EXIT_SUCCESS) \
			|| (par_toks[i]->type == or && exit_status == EXIT_SUCCESS))
			{
				errno = EXIT_FAILURE;
				return (EXIT_SUCCESS);
			}
			if (repinterprete_env_vars(&par_toks[i], &exp_toks[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		else if (par_toks[i]->type == subshell)
			exit_status = handle_subshell(exp_toks[i]->cmd[0]);
		else if (is_redir(par_toks[i]))
			exit_status = handle_redir(par_toks[i], exp_toks[i]);
		else
			exit_status = executor(exp_toks[i]);
		i++;
	}
	set_err_code(exit_status);
	return (EXIT_SUCCESS);
}

int	expander(t_par_tok *par_toks[])
{
	t_exp_tok	**exp_toks;

	if (get_tokens(par_toks) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exp_toks = get_exp_toks();
	return (free_exp_toks(exp_toks, handle_tokens(exp_toks, par_toks)));
}
