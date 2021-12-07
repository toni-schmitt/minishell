/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:44:55 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/07 18:38:34 by toni             ###   ########.fr       */
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
			dup2(exp_tok->in, STDIN_FILENO);
		}
		if (exp_tok->out != 0) // the standard of the out should be 1, not 0
		{
			printf("changed stdout to %d\n", exp_tok->out);//remove after testing
			dup2(exp_tok->out, STDOUT_FILENO);
		}
		if (execve(abs_cmd_path, exp_tok->cmd, get_envv()->env_var) == -1)
			return (EXIT_FAILURE);
	}
	waitpid(pid, &status, 0); // this status will need to be changed with WEXITSTATUS
	return (status);
}

int	executor(t_exp_tok *expander_tokens[])
{
	int		i;
	int		exit_status;
	char	*abs_cmd_path;

	i = 0;
	while (expander_tokens[i])
	{
		abs_cmd_path = NULL;
		if (!is_valid_cmd(expander_tokens[i]->cmd[0], &abs_cmd_path))
		{
			printf("%s: command not found\n", expander_tokens[i]->cmd[0]);
			return (EXIT_CMD_NOT_FOUND);
		}
		exit_status = execute_cmd(expander_tokens[i], abs_cmd_path);
		free(abs_cmd_path);
		i++;
	}
	return (exit_status);
}
