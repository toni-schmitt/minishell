/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_two.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/16 22:07:38 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/20 15:18:54 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "executor_utils.h"
#include "env_var_utils.h"

int	execute_child(t_exp_tok *exp_tok, char *abs_cmd_path, int status)
{
	int		s;

	if (exp_tok->in != STDIN_FILENO && dup2(exp_tok->in, STDIN_FILENO) == -1)
		return (ft_perror(EXIT_FAILURE, "dup2 error"));
	if (exp_tok->out != STDOUT_FILENO)
	{
		s = dup(STDOUT_FILENO);
		if (s == -1 || dup2(exp_tok->out, STDOUT_FILENO) == -1)
			return (ft_perror(EXIT_FAILURE, "dup error"));
	}
	status = execve(abs_cmd_path, exp_tok->cmd, get_envv()->env_var);
	perror(NULL);
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
	exit(status);
	return (status);
}

int	execute_inbuilt_child(t_exp_tok *exp_tok)
{
	pid_t	pid;
	int		exit_status;

	pid = fork();
	if (pid == -1)
		return (EXIT_FAILURE);
	else if (pid == 0)
	{
		exit_status = execute_inbuilt(exp_tok);
		exit(exit_status);
		return (exit_status);
	}
	waitpid(pid, &exit_status, 0);
	return (exit_status);
}

int	execute_inbuilt_reset_fds(t_exp_tok *exp_tok, int saved_fds[2])
{
	if (exp_tok->in != STDIN_FILENO)
	{
		dup2(saved_fds[STDIN_FILENO], STDIN_FILENO);
		close(saved_fds[STDIN_FILENO]);
	}
	if (exp_tok->out != STDOUT_FILENO)
	{
		dup2(saved_fds[STDOUT_FILENO], STDOUT_FILENO);
		close(saved_fds[STDOUT_FILENO]);
	}
	return (EXIT_SUCCESS);
}
