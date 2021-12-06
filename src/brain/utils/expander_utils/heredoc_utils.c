/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 21:59:04 by toni              #+#    #+#             */
/*   Updated: 2021/12/06 19:40:01 by toni             ###   ########.fr       */
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
static int	wait_for_heredoc(t_par_tok *par_tok)
{
	char	*buf;
	char	*heredoc;

	heredoc = get_heredoc(par_tok);
	if (heredoc == NULL)
		return (EXIT_FAILURE);
	buf = readline("> ");
	if (buf == NULL)
		return (EXIT_FAILURE);
	while (ft_strcmp(buf, heredoc) != 0)
	{
		free(buf);
		buf = readline("> ");
		if (buf == NULL)
			return (EXIT_FAILURE);
	}
	free(buf);
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
			return (wait_for_heredoc(par_toks[i]));
		i++;
	}
	return (EXIT_SUCCESS);
}
