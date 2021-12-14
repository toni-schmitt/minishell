/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:59:04 by toni              #+#    #+#             */
/*   Updated: 2021/12/14 16:33:52 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"
#include <readline/history.h>
#include <readline/readline.h>

/**
 * @brief  Gets heredoc to wait for
 * @note
 * @param  *par_tok:
 * @retval char pointer to (by parser) allocated heredoc
 */
static char	*get_heredoc(t_par_tok *par_tok)
{
	int	i;

	i = 0;
	while (par_tok->in[i])
	{
		if (ft_strcmp(par_tok->in[i], "<<") == 0)
			return (par_tok->in[i + 1]);
		i++;
	}
	return (NULL);
}

static int	exit_close_fds(int fd1, int fd2, int exit_status)
{
	if (fd1 != -1)
		close(fd1);
	if (fd1 != -1)
		close(fd2);
	return (exit_status);
}

/**
 * @brief  Waits in readline-prompt as long as heredoc is not typed
 * @note
 * @param  *par_tok:
 * @retval int to indicate success or failure
 */
int	wait_for_heredoc(t_par_tok *par_tok, t_exp_tok *exp_tok)
{
	char	*buf;
	char	*heredoc;
	int		end[2];

	if (pipe(end) == -1)
		return (ft_perror(EXIT_FAILURE, "pipe error"));
	exp_tok->in = end[0];
	heredoc = get_heredoc(par_tok);
	if (heredoc == NULL)
		return (exit_close_fds(end[0], end[1], EXIT_FAILURE));
	while (true)
	{
		buf = readline("> ");
		if (buf == NULL)
			return (exit_close_fds(end[1], -1, EXIT_SUCCESS));
		if (ft_strcmp(buf, heredoc) == 0)
			break ;
		write(end[1], buf, ft_strlen(buf));
		write(end[1], "\n", 1);
		free(buf);
	}
	free(buf);
	if (close(end[1]) != 0)
		return (exit_close_fds(end[0], -1, EXIT_FAILURE));
	if (exp_tok->cmd == NULL && exp_tok->out != STDOUT_FILENO)
	{
		close(exp_tok->out);
		exp_tok->out = STDOUT_FILENO;
	}
	return (EXIT_SUCCESS);
}
