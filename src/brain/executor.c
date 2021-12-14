/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:44:55 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/14 15:50:31 by toni             ###   ########.fr       */
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

/**
 * @brief  Returns absolute command path of cmd or NULL if not found or error
 * @note   
 * @param  *cmd: 
 * @retval 
 */
static char	*get_abs_cmd(char *cmd)
{
	char	**path_splitted;
	char	*absolute_cmd_path;
	int		i;

	if (access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	if (init(&path_splitted) == EXIT_FAILURE)
		return (NULL);
	i = 0;
	while (path_splitted[i])
	{
		absolute_cmd_path = get_abs_cmd_path(path_splitted[i], cmd);
		if (absolute_cmd_path == NULL)
			return (NULL);
		if (access(absolute_cmd_path, F_OK) == 0)
		{
			ft_free_split(path_splitted);
			return (absolute_cmd_path);
		}
		ft_free((void *)&absolute_cmd_path);
		i++;
	}
	ft_free_split(path_splitted);
	return (NULL);
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
		if (dup2(exp_tok->in, STDIN_FILENO) == -1)
			return (ft_perror(EXIT_FAILURE, "dup2 error"));
		// fprintf(stderr, "changed stdout to %d\n", exp_tok->out);//remove after testing
		if (dup2(exp_tok->out, STDOUT_FILENO) == -1)
			return (ft_perror(EXIT_FAILURE, "dup2 error"));
		status = execve(abs_cmd_path, exp_tok->cmd, get_envv()->env_var);
		perror(NULL);
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

static int	clean_exp_tok_cmds(t_exp_tok *exp_tok)
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

int	executor(t_exp_tok *exp_tok)
{
	int		exit_status;
	char	*abs_cmd_path;

	if (exp_tok->cmd == NULL)
		return (EXIT_SUCCESS);
	if (clean_exp_tok_cmds(exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (is_inbuilt(exp_tok->cmd[0]))
		return (handle_inbuilt_redir(exp_tok));
	abs_cmd_path = get_abs_cmd(exp_tok->cmd[0]);
	if (abs_cmd_path == NULL)
	{
		ft_putstr_fd(exp_tok->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (EXIT_CMD_NOT_FOUND);
	}
	exit_status = execute_cmd(exp_tok, abs_cmd_path);
	free(abs_cmd_path);
	return (exit_status);
}
