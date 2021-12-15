/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_signal.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 14:16:12 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/15 18:50:35 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <signal.h>
#include <readline/readline.h>
#include <readline/history.h>

static void	handle_cmd_signal(int sig)
{
	if (sig == SIGINT)
	{
		set_err_code(130);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
	}
}

static void	handle_global_signal(int sig)
{
	if (sig == SIGINT)
	{
		set_err_code(1);
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_cmd_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_cmd_signal);
}

void	handle_global_signals(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGINT, handle_global_signal);
}
