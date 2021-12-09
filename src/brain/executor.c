/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:44:55 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/09 17:17:54 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "env_var_utils.h"
#include <sys/wait.h>
#include <sys/types.h>

static char	*get_abs_cmd_path(char *path_splitted, char *cmd)
{
	char	*abs_cmd_path;

	abs_cmd_path = ft_strjoin(path_splitted, "/");
	if (abs_cmd_path == NULL)
		return (NULL);
	abs_cmd_path = ft_append(&abs_cmd_path, cmd);
	if (abs_cmd_path == NULL)
		return (NULL);
	return (abs_cmd_path);
}

static int	init(char **path_splitted[])
{
	char	*path;

	path = get_env_var_value(get_envv(), "PATH");
	if (path == NULL)
		return (EXIT_FAILURE);
	*path_splitted = ft_split(path, ':');
	free(path);
	if (*path_splitted == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

static bool	is_valid_cmd(char *cmd, char **abs_cmd_path)
{
	char	**path_splitted;
	char	*absolute_cmd_path;
	int		i;

	if (init(&path_splitted) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	i = 0;
	while (path_splitted[i])
	{
		absolute_cmd_path = get_abs_cmd_path(path_splitted[i], cmd);
		if (absolute_cmd_path == NULL)
			return (EXIT_FAILURE);
		if (access(absolute_cmd_path, F_OK) == 0)
		{
			ft_free_split(path_splitted);
			*abs_cmd_path = absolute_cmd_path;
			return (true);
		}
		free(absolute_cmd_path);
		i++;
	}
	ft_free_str_array(&path_splitted);
	*abs_cmd_path = NULL;
	return (false);
}

/**
 * @brief  Executes command in child process
 * @note   Waits for child process to finish
 * @param  *exp_tok:
 * @param  *abs_cmd_path:
 * @retval exit status of child process
 */
static int	execute_cmd(t_exp_tok *exp_tok, char *abs_cmd_path)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		if (exp_tok->in != STDIN_FILENO) // this check is not needed in theory
		{
			printf("changed stdin to %d\n", exp_tok->in);// remove after testing
			dup2(exp_tok->in, STDIN_FILENO); // add protection
		}
		if (exp_tok->out != STDOUT_FILENO)
		{
			printf("changed stdout to %d\n", exp_tok->out);//remove after testing
			dup2(exp_tok->out, STDOUT_FILENO); // add protection
		}
		return (execve(abs_cmd_path, exp_tok->cmd, get_envv()->env_var));
	}
	waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	execute_pipe_cmds(t_exp_tok *exp_toks[])
{
	(void)exp_toks;
	return (EXIT_FAILURE);
}

static bool	is_inbuilt(char *cmd)
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
	return (false);
}

static int	execute_inbuilt(char *cmd[])
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
	return (EXIT_FAILURE);
}

int	executor(t_exp_tok *exp_tok, bool is_pipe)
{
	int		exit_status;
	char	*abs_cmd_path;

	if (!is_inbuilt(exp_tok->cmd[0]))
	{
		abs_cmd_path = NULL;
		if (!is_valid_cmd(exp_tok->cmd[0], &abs_cmd_path))
		{
			printf("%s: command not found\n", exp_tok->cmd[0]);
			return (EXIT_CMD_NOT_FOUND);
		}
		exit_status = execute_cmd(exp_tok, abs_cmd_path);
		free(abs_cmd_path);
	}
	else if (!is_pipe)
		return (execute_inbuilt(exp_tok->cmd));
	return (exit_status);
}
