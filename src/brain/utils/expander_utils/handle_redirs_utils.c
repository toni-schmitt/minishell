/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:51:20 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/08 17:58:32 by tblaase          ###   ########.fr       */
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
	while (true)
	{
		i++;
		if (par_tok->redir_type[is_in])
			fd = open(par_tok->in[i], O_RDONLY);
		if (fd == -1)
		{
			printf("something with %s is wrong\n", par_tok->in[i]);
			perror("ERROR_in");// change this after finished debugging to ERROR
			return (EXIT_FAILURE); // here we need to set the exit_status to 1 and somehow quit the executor
		}
		if (par_tok->in[i + 1] == NULL)
			break ;
		i++;
	}
	exp_tok->in = fd;
	printf("the new fd for input is now %d\n", exp_tok->in);
	return (EXIT_SUCCESS);
}

static int	open_out(t_par_tok *par_tok, t_exp_tok *exp_tok)
{
	int		i;
	int		fd;

	i = 0;
	fd = 1;
	while (true)
	{
		if (par_tok->redir_type[is_out]
			&& ft_strcmp(par_tok->out[i++], ">") == 0)
			fd = open(par_tok->out[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (par_tok->redir_type[is_out_append]
			&& ft_strcmp(par_tok->out[i++], ">>") == 0)
			fd = open(par_tok->out[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
		{
			perror("ERROR_out");// change this after finished debugging to ERROR
			return (EXIT_FAILURE); // here we need to set the exit_status to 1 and somehow quit the executor
		}
		if (par_tok->out[i + 1] == NULL)
			break ;
		i++;
	}
	exp_tok->out = fd;
	printf("the new fd for output is now %d\n", exp_tok->out);
	return (EXIT_SUCCESS);
}

int	handle_redir(t_par_tok **par_toks, t_exp_tok **exp_toks)
{
	int	i;

	i = 0;
	while (par_toks && par_toks[i] && exp_toks && exp_toks[i])
	{
		if (par_toks[i]->in && par_toks[i]->in[0])
		{
			if (open_in(par_toks[i], exp_toks[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		if (par_toks[i]->out && par_toks[i]->out[0])
		{
			if (open_out(par_toks[i], exp_toks[i]) == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
