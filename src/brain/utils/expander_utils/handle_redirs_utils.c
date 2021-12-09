/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:51:20 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/09 19:20:42 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"

static int	open_in(t_par_tok *par_tok, t_exp_tok *exp_tok)
{
	int		i;
	int		fd;

	i = 0;
	fd = 0;
	while (par_tok->redir_type[is_in])
	{
		i++;
		if (par_tok->redir_type[is_in])
			fd = open(par_tok->in[i], O_RDONLY);
		if (fd == -1)
		{
			dprintf(stderr, "something with %s is wrong\n", par_tok->in[i]);//remove after testing
			perror("ERROR_in");//change this after finished debugging to ERROR
			return (EXIT_FAILURE);
		}
		if (par_tok->in[i + 1] == NULL)
			break ;
		i++;
	}
	exp_tok->in = fd;
	dprintf(stderr, "the new fd for input is now %d\n", exp_tok->in);//remove after testing
	return (EXIT_SUCCESS);
}

static int	open_out(t_par_tok *par_tok, t_exp_tok *exp_tok)
{
	int		i;
	int		fd;

	i = 0;
	fd = 1;
	while (par_tok->redir_type[is_out] || par_tok->redir_type[is_out_append])
	{
		if (par_tok->redir_type[is_out]
			&& ft_strcmp(par_tok->out[i++], ">") == 0)
			fd = open(par_tok->out[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (par_tok->redir_type[is_out_append]
			&& ft_strcmp(par_tok->out[i++], ">>") == 0)
			fd = open(par_tok->out[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("ERROR_out");//change this after finished debugging to ERROR
			return (EXIT_FAILURE);
		}
		if (par_tok->out[i + 1] == NULL)
			break ;
		i++;
	}
	exp_tok->out = fd;
	dprintf(stderr, "the new fd for output is now %d\n", exp_tok->out);//remove after testing
	return (EXIT_SUCCESS);
}

int	handle_redir(t_par_tok *par_tok, t_exp_tok *exp_tok)//remove comments after testing
{
	dprintf(stderr, "entering handle_redir\n");
	if (open_in(par_tok, exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	dprintf(stderr, "successfully set in redirection\n");
	if (open_out(par_tok, exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	dprintf(stderr, "successfully set out redirection\n");
	return (EXIT_SUCCESS);
}
