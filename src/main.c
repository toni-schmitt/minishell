/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:28:36 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/14 17:01:23 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "env_var_utils.h"
#include <readline/history.h>
#include <readline/readline.h>

/*
 * STILL USES clear_history INSTEAD OF rl_clear_history
 * SUBJECT.PDF DOES NOT ALLOW CLEAR_HISTORY
 * GITHUB ACTION ONLY KNOWS clear_history!!!
 */
static int	exit_routine(void *to_free, int exit_status)
{
	clear_history(); // CHANGE TO rl_clear_history();
	free(to_free);
	free_envv(get_envv());
	return (exit_status);
}

static int	routine(void)
{
	char	*buf;
	int		exit_code;

	while (true)
	{
		buf = readline("minishell$ ");
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (buf == NULL)
			return (exit_routine((void *)buf, EXIT_CTRL_D));
		exit_code = lexer(buf);
		if (exit_code == EXIT_FAILURE)
			return (exit_routine((void *)buf, EXIT_FAILURE));
		if (exit_code == EXIT_CTRL_D)
		{
			printf("exit\n");
			return (exit_routine((void *)buf, EXIT_CTRL_D));
		}
		free(buf);
	}
	return (exit_routine((void *)buf, EXIT_FAILURE));
}

static int	handle_flags(int argc, char *argv[])
{
	int	exit_code;

	if (argc != 3 || ft_strcmp(argv[1], "-c") != 0)
	{
		ft_fprintf(STDERR_FILENO, "Usage: ./minishell [Flag] \"[Command]\"\n");
		ft_fprintf(STDERR_FILENO, "\t-c\tExecute Command without promot\n");
		return (EXIT_FAILURE);
	}
	exit_code = lexer(argv[2]);
	free_envv(get_envv());
	return (exit_code);
}

static int	hide_ctrl_echo(void)
{
	t_exp_tok	*stty_tok;

	stty_tok = malloc(sizeof(*stty_tok));
	if (stty_tok == NULL)
		return (EXIT_FAILURE);
	stty_tok->cmd = ft_calloc(3, sizeof(*stty_tok->cmd));
	if (stty_tok->cmd == NULL)
		return (EXIT_FAILURE);
	stty_tok->cmd[0] = ft_strdup("stty");
	if (stty_tok->cmd[0] == NULL)
		return (EXIT_FAILURE);
	stty_tok->cmd[1] = ft_strdup("-echoctl");
	if (stty_tok->cmd[1] == NULL)
		return (EXIT_FAILURE);
	stty_tok->in = STDIN_FILENO;
	stty_tok->out = STDOUT_FILENO;
	if (executor(stty_tok) == EXIT_FAILURE)
	{
		ft_free_split(stty_tok->cmd);
		free(stty_tok);
		return (EXIT_FAILURE);
	}
	ft_free_split(stty_tok->cmd);
	free(stty_tok);
	return (EXIT_SUCCESS);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*envv;

	handle_signals();
	envv = init_envv(envp);
	if (envv == NULL)
		return (EXIT_FAILURE);
	set_envp(envp);
	set_envv(envv);
	if (hide_ctrl_echo() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (argc != 1)
		return (handle_flags(argc, argv));
	if (routine() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
