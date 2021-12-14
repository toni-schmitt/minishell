/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:44:24 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/14 16:54:10 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"

int	handle_pipes(t_exp_tok *exp_tok, int pipe_type)
{
	static int	last_pipe_out;
	int			end[2];

	if (pipe_type == -1)
	{
		if (last_pipe_out != 0 && last_pipe_out != 1)
		{
			close(last_pipe_out);
			ft_fprintf(STDERR_FILENO, "Error opening pipe\n");
			return (EXIT_FAILURE);
		}
		return (EXIT_SUCCESS);
	}
	if (pipe_type == 0)
	{
		if (last_pipe_out == 0)
		{
			ft_fprintf(STDERR_FILENO, "Error opening pipe\n");
			return (EXIT_FAILURE);
		}
		if (exp_tok->in == 0)
			exp_tok->in = last_pipe_out;
		else if (last_pipe_out != 0 && last_pipe_out != 1)
			close(last_pipe_out);
		last_pipe_out = 0;
	}
	else if (pipe_type == 1)
	{
		if (pipe(end) != 0)
			return (ft_perror(EXIT_FAILURE, "pipe error"));
		last_pipe_out = end[0];
		if (exp_tok->out == 1)
			exp_tok->out = end[1];
		else
			close(end[1]);
	}
	else if (pipe_type == 2)
	{
		if (last_pipe_out == 0)
		{
			ft_fprintf(STDERR_FILENO, "Error opening pipe\n");
			return (EXIT_FAILURE);
		}
		if (exp_tok->in == 0)
			exp_tok->in = last_pipe_out;
		else if (last_pipe_out != 0 && last_pipe_out != 1)
			close(last_pipe_out);
		last_pipe_out = 0;
		if (pipe(end) != 0)
			return (ft_perror(EXIT_FAILURE, "pipe error"));
		last_pipe_out = end[0];
		if (exp_tok->out == 1)
			exp_tok->out = end[1];
		else
			close(end[1]);
	}
	return (EXIT_SUCCESS);
}
