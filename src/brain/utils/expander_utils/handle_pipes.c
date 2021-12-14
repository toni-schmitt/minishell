/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_pipes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 10:44:24 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/14 16:55:45 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"

static int	not_a_pipe(int	last_pipe_out)
{
	if (last_pipe_out != 0 && last_pipe_out != 1)
	{
		close(last_pipe_out);
		ft_putstr_fd("Error opening pipe\n", 2);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

static int	pipe_type_zero(int	*last_pipe_out, t_exp_tok *exp_tok)
{
	if (*last_pipe_out == 0)
	{
		ft_putstr_fd("Error opening pipe\n", 2);
		return (EXIT_FAILURE);
	}
	if (exp_tok->in == 0)
		exp_tok->in = *last_pipe_out;
	else if (*last_pipe_out != 0 && *last_pipe_out != 1)
		close(*last_pipe_out);
	*last_pipe_out = 0;
	return (EXIT_SUCCESS);
}

static int	pipe_type_one(int *last_pipe_out, t_exp_tok *exp_tok)
{
	int			end[2];

	if (pipe(end) != 0)
		return (ft_perror(EXIT_FAILURE, "pipe error"));
	*last_pipe_out = end[0];
	if (exp_tok->out == 1)
		exp_tok->out = end[1];
	else
		close(end[1]);
	return (EXIT_SUCCESS);
}

static int	pipe_type_two(int	*last_pipe_out, t_exp_tok *exp_tok)
{
	int			end[2];

	if (*last_pipe_out == 0)
	{
		ft_putstr_fd("Error opening pipe\n", 2);
		return (EXIT_FAILURE);
	}
	if (exp_tok->in == 0)
		exp_tok->in = *last_pipe_out;
	else if (*last_pipe_out != 0 && *last_pipe_out != 1)
		close(*last_pipe_out);
	*last_pipe_out = 0;
	if (pipe(end) != 0)
		return (ft_perror(EXIT_FAILURE, "pipe error"));
	*last_pipe_out = end[0];
	if (exp_tok->out == 1)
		exp_tok->out = end[1];
	else
		close(end[1]);
	return (EXIT_SUCCESS);
}

int	handle_pipes(t_exp_tok *exp_tok, int pipe_type)
{
	static int	last_pipe_out;

	if (pipe_type == -1)
		return (not_a_pipe(last_pipe_out));
	else if (pipe_type == 0)
		return (pipe_type_zero(&last_pipe_out, exp_tok));
	else if (pipe_type == 1)
		return (pipe_type_one(&last_pipe_out, exp_tok));
	else if (pipe_type == 2)
		return (pipe_type_two(&last_pipe_out, exp_tok));
	return (EXIT_SUCCESS);
}
