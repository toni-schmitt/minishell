/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:18:33 by toni              #+#    #+#             */
/*   Updated: 2021/12/14 16:21:15 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "executor_utils.h"

static char	*get_clean_cmd(char *cmd)
{
	char	*cleaned;
	int		cmd_len;
	int		i;
	int		j;

	cmd_len = ft_strlen(cmd);
	if (cmd[0] != '\'' && cmd[0] != '\"')
		return (cmd);
	if (cmd[cmd_len - 1] != cmd[0])
		return (cmd);
	cleaned = ft_calloc(ft_strlen(cmd) + 1, sizeof(*cleaned));
	if (cleaned == NULL)
	{
		free(cmd);
		return (NULL);
	}
	i = 1;
	j = 0;
	while (i < cmd_len - 1)
		cleaned[j++] = cmd[i++];
	free(cmd);
	return (cleaned);
}

int	clean_exp_tok_cmds(t_exp_tok *exp_tok)
{
	int		i;

	i = 0;
	while (exp_tok && exp_tok->cmd && exp_tok->cmd[i])
	{
		exp_tok->cmd[i] = get_clean_cmd(exp_tok->cmd[i]);
		if (exp_tok->cmd[i] == NULL)
		{
			ft_free_split(exp_tok->cmd);
			return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief  This is stolen from somewhere, idk from where
 * @note   i have no clue how or why this is working
 * @param  *exp_tok:
 * @retval the exit status of the inbuilt function
 */
int	handle_inbuilt_redir(t_exp_tok *exp_tok)
{
	int	exit_status;
	int	s;

	if (exp_tok->in != STDIN_FILENO && dup2(exp_tok->in, STDIN_FILENO) == -1)
		return (ft_perror(EXIT_FAILURE, "dup2 error"));
	if (exp_tok->out != STDOUT_FILENO)
	{
		s = dup(STDOUT_FILENO);
		if (s == -1)
			return (ft_perror(EXIT_FAILURE, "dup error"));
		if (dup2(exp_tok->out, STDOUT_FILENO) == -1)
			return (ft_perror(EXIT_FAILURE, "dup2 error"));
	}
	exit_status = execute_inbuilt(exp_tok->cmd);
	if (exp_tok->in != STDIN_FILENO)
	{
		close(exp_tok->in);
		dup2(0, exp_tok->in);
	}
	if (exp_tok->out != STDOUT_FILENO)
	{
		dup2(s, STDOUT_FILENO);
		close(s);
	}
	return (exit_status);
}

bool	is_inbuilt(char *cmd)
{
	if (ft_strcmp(cmd, "echo") == 0)
		return (true);
	if (ft_strcmp(cmd, "export") == 0)
		return (true);
	if (ft_strcmp(cmd, "env") == 0)
		return (true);
	if (ft_strcmp(cmd, "cd") == 0)
		return (true);
	if (ft_strcmp(cmd, "unset") == 0)
		return (true);
	if (ft_strcmp(cmd, "pwd") == 0)
		return (true);
	if (ft_strcmp(cmd, "exit") == 0)
		return (true);
	return (false);
}

int	execute_inbuilt(char *cmd[])
{
	if (ft_strcmp(cmd[0], "echo") == 0)
		return (echo(cmd));
	if (ft_strcmp(cmd[0], "export") == 0)
		return (export(cmd));
	if (ft_strcmp(cmd[0], "env") == 0)
		return (env(cmd));
	if (ft_strcmp(cmd[0], "cd") == 0)
		return (cd(cmd));
	if (ft_strcmp(cmd[0], "unset") == 0)
		return (unset(cmd));
	if (ft_strcmp(cmd[0], "pwd") == 0)
		return (pwd());
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (exit_inbuilt(cmd));
	return (EXIT_FAILURE);
}
