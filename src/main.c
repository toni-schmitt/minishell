/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:28:36 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/11 13:16:30 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "env_var_utils.h"

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
		if (buf == NULL || ft_strcmp(buf, "exit") == 0)
		{
			printf("exit\n");
			return (exit_routine((void *)buf, EXIT_CTRL_D));
		}
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
		printf("Usage: ./minishell [Flag] \"[Command]\"\n");
		printf("\t-c\tExecute Command without promot\n");
		return (EXIT_FAILURE);
	}
	exit_code = lexer(argv[2]);
	free_envv(get_envv());
	return (exit_code);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_env	*envv;

	envv = init_envv(envp);
	if (envv == NULL)
		return (EXIT_FAILURE);
	set_envp(envp);
	set_envv(envv);
	if (argc != 1)
		return (handle_flags(argc, argv));
	if (routine() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
