/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:39:06 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/17 16:33:58 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"
#include "env_var_utils.h"

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

int	handle_subshell(t_exp_tok *exp_tok)
{
	pid_t	pid;
	int		status;
	char	*cutted_cmd;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		cutted_cmd = get_subshell_cmd(exp_tok->cmd[0]);
		if (cutted_cmd == NULL)
			return (EXIT_FAILURE);
		status = lexer(cutted_cmd);
		free(cutted_cmd);
		exit(get_err_code());
	}
	waitpid(pid, &status, 0);
	set_err_code(WEXITSTATUS(status));
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

static int	handle_tokens(t_exp_tok *exp_toks[], t_par_tok *par_toks[])
{
	int	i;

	i = 0;
	while (exp_toks[i] && par_toks[i])
	{
		if (par_toks[i]->type == and || par_toks[i]->type == or)
		{
			if ((par_toks[i]->type == and && get_err_code() != EXIT_SUCCESS) \
			|| (par_toks[i]->type == or && get_err_code() == EXIT_SUCCESS))
			{
				set_err_code(EXIT_FAILURE);
				i++;
			}
			repinterprete_env_vars(&par_toks[i + 1], &exp_toks[i + 1]);
		}
		else if (par_toks[i]->type == subshell)
			set_err_code(handle_subshell(exp_toks[i]));
		else if (is_redir(par_toks[i]))
			set_err_code(handle_redir(par_toks[i], exp_toks[i], \
			set_pipe_type(par_toks, i)));
		else if (exp_toks[i]->cmd != NULL)
			set_err_code(executor(exp_toks[i]));
		i++;
	}
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
