/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:44:55 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/11 13:36:33 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "env_var_utils.h"

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
		// fprintf(stderr, "changed stdin to %d\n", exp_tok->in);// remove after testing
		dup2(exp_tok->in, STDIN_FILENO); // add protection
		// fprintf(stderr, "changed stdout to %d\n", exp_tok->out);//remove after testing
		dup2(exp_tok->out, STDOUT_FILENO); // add protection
		status = execve(abs_cmd_path, exp_tok->cmd, get_envv()->env_var);
		if (exp_tok->in != STDIN_FILENO)
			close(exp_tok->in);
		if (exp_tok->out != STDOUT_FILENO)
			close(exp_tok->out);
		return (status);
	}
	waitpid(pid, &status, 0);
	status = WEXITSTATUS(status); // added for debugging
	return (status);
}

// int	prepare_pipe_cmds(t_exp_tok *exp_toks[])
// {
// 	int	i;

// 	i = 0;
// 	while (exp_toks[i]->type[is_pipe] && exp_toks[i + 1]->type[is_pipe])
// 	{
// 		if (pipe(exp_toks[i]->end) != 0)
// 		{
// 			perror("ERROR");
// 			return (EXIT_FAILURE);
// 		}
// 		if (i == 0 && exp_toks[i + 1]->type[is_pipe] && exp_toks[i]->out == 1)
// 			exp_toks->out = end[1];
// 		i++;
// 	}
// 	return (EXIT_FAILURE);
// }

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
	if (ft_strcmp(cmd, "exit") == 0)
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
	if (ft_strcmp(cmd[0], "exit") == 0)
		return (exit_inbuilt(cmd));
	return (EXIT_FAILURE);
}
/**
 * @brief  This is stolen from somewhere, idk from where
 * @note   i have no clue how or why this is working
 * @param  *exp_tok:
 * @retval the exit status of the inbuilt function
 */
static int	handle_inbuilt_redir(t_exp_tok *exp_tok)
{
	int	exit_status;
	int	s;

	if (exp_tok->in != STDIN_FILENO)
		dup2(exp_tok->in, STDIN_FILENO);
	if (exp_tok->out != STDOUT_FILENO)
	{
		s = dup(STDOUT_FILENO);
		dup2(exp_tok->out, STDOUT_FILENO);
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

int	executor(t_exp_tok *exp_tok)
{
	int		exit_status;
	char	*abs_cmd_path;

	if (is_inbuilt(exp_tok->cmd[0]))
		return (handle_inbuilt_redir(exp_tok));
	abs_cmd_path = NULL;
	if (!is_valid_cmd(exp_tok->cmd[0], &abs_cmd_path))
	{
		printf("%s: command not found\n", exp_tok->cmd[0]); // pls print to stderr
		return (EXIT_CMD_NOT_FOUND);
	}
	exit_status = execute_cmd(exp_tok, abs_cmd_path);
	free(abs_cmd_path);
	return (exit_status);
}
