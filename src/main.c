/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:28:36 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/04 22:05:37 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"

/*
 * STILL USES clear_history INSTEAD OF rl_clear_history
 * SUBJECT.PDF DOES NOT ALLOW CLEAR_HISTORY
 * GITHUB ACTION ONLY KNOWS clear_history!!!
 */
static int	exit_routine(void *to_free, int exit_status)
{
	clear_history(); // CHANGE TO rl_clear_history();
	free(to_free);
	return (exit_status);
}

static int	routine(void)
{
	char	*buf;

	while (true)
	{
		buf = readline("minishell$ ");
		if (ft_strlen(buf) > 0)
			add_history(buf);
		if (lexer(buf) == EXIT_FAILURE)
			return (exit_routine((void *)buf, EXIT_FAILURE));
		free(buf);
	}
	return (exit_routine((void *)buf, EXIT_FAILURE));
}

static int	handle_flags(int argc, char *argv[])
{
	if (argc != 3)
		return (EXIT_FAILURE);
	if (ft_strcmp(argv[1], "-c") != 0)
		return (EXIT_FAILURE);
	return (exit_routine(NULL, lexer(argv[2])));
}

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 1)
		return (handle_flags(argc, argv));
	set_envp(envp);
	if (routine() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
