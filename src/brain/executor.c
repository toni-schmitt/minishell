/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:44:55 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/13 15:51:35 by tschmitt         ###   ########.fr       */
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
		return (false);
	i = 0;
	while (path_splitted[i])
	{
		absolute_cmd_path = get_abs_cmd_path(path_splitted[i], cmd);
		if (absolute_cmd_path == NULL)
			return (false);
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
	t_env	*envv;

	envv = get_envv();
	pid = fork();
	if (pid < 0)
		return (EXIT_FAILURE);
	if (pid == 0)
	{
		// fprintf(stderr, "changed stdin to %d\n", exp_tok->in);// remove after testing
		if (dup2(exp_tok->in, STDIN_FILENO) == -1)
			return (EXIT_FAILURE);
		// fprintf(stderr, "changed stdout to %d\n", exp_tok->out);//remove after testing
		if (dup2(exp_tok->out, STDOUT_FILENO) == -1)
			return (EXIT_FAILURE);
		status = execve(abs_cmd_path, exp_tok->cmd, get_envv()->env_var);
		perror(NULL);
		if (exp_tok->in != STDIN_FILENO) // this might cause a double close - > error
		{
			if (close(exp_tok->in) == -1)
				status = ft_perror(EXIT_FAILURE, "close error");
		}
		if (exp_tok->out != STDOUT_FILENO && exp_tok->out != envv->subshell_out)
		{
			if (close(exp_tok->out) == -1)
				status = ft_perror(EXIT_FAILURE, "close error");
		}
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
 * @brief  those dup / dup2 mix is due to it working in any other way
 * @note   i have no clue how or why this is working
 * @param  *exp_tok: the expander-token containing all the necessary info
 * @retval the exit status of the inbuilt function
 */
static int	handle_inbuilt_redir(t_exp_tok *exp_tok)
{
	int		exit_status;
	int		s;
	t_env	*envv;

	envv = get_envv();
	if (exp_tok->in != STDIN_FILENO)
	{
		if (dup2(exp_tok->in, STDIN_FILENO) == -1)
			return (ft_perror(EXIT_FAILURE, "dup2 error"));
	}
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
		if (dup2(0, exp_tok->in) == -1)
			exit_status = ft_perror(EXIT_FAILURE, "dup2 error");
		if (close(exp_tok->in) == -1)
			exit_status = ft_perror(EXIT_FAILURE, "close error");
	}
	if (exp_tok->out != STDOUT_FILENO && exp_tok->out != envv->subshell_out)
	{
		if (dup2(s, envv->subshell_out) == -1)
			exit_status = ft_perror(EXIT_FAILURE, "dup2 error");
		if (close(s) == -1)
			exit_status = ft_perror(EXIT_FAILURE, "close error");
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
	abs_cmd_path = NULL;
	if (!is_valid_cmd(exp_tok->cmd[0], &abs_cmd_path))
	{
		ft_putstr_fd(exp_tok->cmd[0], STDERR_FILENO);
		ft_putstr_fd(": command not found\n", STDERR_FILENO);
		return (EXIT_CMD_NOT_FOUND);
	}
	exit_status = execute_cmd(exp_tok, abs_cmd_path);
	free(abs_cmd_path);
	return (exit_status);
}
