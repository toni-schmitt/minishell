/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:51:20 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/09 19:53:58 by toni             ###   ########.fr       */
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
			// fprintf(stderr, "something with %s is wrong\n", par_tok->in[i]);//remove after testing
			perror("ERROR_in");//change this after finished debugging to ERROR
			return (EXIT_FAILURE);
		}
		if (par_tok->in[i + 1] == NULL)
			break ;
		close(fd);
		i++;
	}
	exp_tok->in = fd;
	// fprintf(stderr, "the new fd for input is now %d\n", exp_tok->in);//remove after testing
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
		close(fd);
		i++;
	}
	exp_tok->out = fd;
	// fprintf(stderr, "the new fd for output is now %d\n", exp_tok->out);//remove after testing
	return (EXIT_SUCCESS);
}

int	handle_redir(t_par_tok *par_tok, t_exp_tok *exp_tok)//remove comments after testing
{
	int	exit_status;

	// fprintf(stderr, "entering handle_redir\n");
	if (open_in(par_tok, exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// fprintf(stderr, "successfully set in redirection\n");
	if (open_out(par_tok, exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	// fprintf(stderr, "successfully set out redirection\n");
	exit_status = executor(exp_tok);
	if (exp_tok->in != STDIN_FILENO)
		close(exp_tok->in);
	if (exp_tok->out != STDOUT_FILENO)
		close(exp_tok->out);
	return (exit_status);
}
