/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:51:20 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/08 12:58:57 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"

static int	open_all_redirs(t_par_tok *par_tok, t_exp_tok *exp_tok)
{
	int		i;
	int		fd;

	i = 0;
	fd = 0;
	if (par_tok->in[i] != NULL)
	{
		while (true)
		{
			if (par_tok->redir_type[is_in] || par_tok->redir_type[is_pipe])
				fd = open(par_tok->in[i], O_RDONLY);
			if (fd == -1)
			{
				perror("ERROR");
				return (errno);
			}
			if (par_tok->in[i + 1] == NULL)
			{
				exp_tok->in = fd;
				break ;
			}
			i++;
		}
	}
	i = 0;
	fd = 1;
	if (par_tok->out[i] != NULL)
	{
		while (true)
		{
			if (par_tok->redir_type[is_pipe])
				fd = -2;
			if (par_tok->redir_type[is_out])
				fd = open(par_tok->out[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
			else if (par_tok->redir_type[is_out_append])
				fd = open(par_tok->out[i], O_RDWR | O_CREAT | O_APPEND, 0644);
			if (fd == -1)
			{
				perror("ERROR");
				return (errno);
			}
			if (par_tok->out[i + 1] == NULL)
			{
				exp_tok->out = fd;
				break ;
			}
			i++;
		}
	}
	return (EXIT_SUCCESS);
}

int	handle_redir(t_par_tok **par_toks, t_exp_tok **exp_toks)
{
	int	i;
	int	check;

	i = 0;
	while (par_toks && par_toks[i] && exp_toks && exp_toks[i])
	{
		check = open_all_redirs(par_toks[i], exp_toks[i]);
		if (check != EXIT_SUCCESS)
			return (check);
		i++;
	}
	return (EXIT_SUCCESS);
}
