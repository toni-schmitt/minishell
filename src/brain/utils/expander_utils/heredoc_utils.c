/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:59:04 by toni              #+#    #+#             */
/*   Updated: 2021/12/09 19:33:29 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"

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
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
	// remove after testing until next //
	// fprintf(stderr, "read end of the pipe: %d\n", end[0]);
	// fprintf(stderr, "write end of the pipe: %d\n", end[1]);
	//
	exp_tok->in = end[0];
	heredoc = get_heredoc(par_tok);
	if (heredoc == NULL)
	{
		close(end[0]);
		close(end[1]);
		return (EXIT_FAILURE);
	}
	while (true)
	{
		buf = readline("> ");
		if (buf == NULL)
		{
			if (close(end[1]) != 0)
			{
				close(end[0]);
				return (EXIT_FAILURE);
			}
			return (EXIT_SUCCESS);
		}
		if (ft_strcmp(buf, heredoc) == 0)
			break ;
		write(end[1], buf, ft_strlen(buf));
		write(end[1], "\n", 1);
		free(buf);
	}
	free(buf);
	if (close(end[1]) != 0)
	{
		close(end[0]);
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

/**
 * @brief  Searches for heredoc in par_toks and waits if found
 * @note
 * @param  *par_toks[]:
 * @retval int to indicate success or failure
 */
int	check_for_heredoc(t_par_tok *par_toks[])
{
	int	i;

	i = 0;
	while (par_toks[i])
	{
		if (par_toks[i]->redir_type[is_in_heredoc])
			return (wait_for_heredoc(par_toks[i], NULL));
		i++;
	}
	return (EXIT_SUCCESS);
}
