/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:28:36 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/02 15:27:44 by tschmitt         ###   ########.fr       */
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

int	main(int argc, char *argv[], char *envp[])
{
	if (argc != 1)
		return (EXIT_FAILURE);
	(void)argv;
	set_envp(envp);
	if (routine() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
