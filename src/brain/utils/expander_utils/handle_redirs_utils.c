/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_redirs_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 12:51:20 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/20 15:23:52 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"

static int	open_in(t_par_tok *par_tok, t_exp_tok *exp_tok)
{
	int		i;
	int		fd;
	int		heredeoc_fd;

	i = 0;
	fd = 0;
	if (exp_tok->in != STDIN_FILENO)
		heredeoc_fd = exp_tok->in;
	while (par_tok->redir_type[is_in] || par_tok->redir_type[is_in_heredoc])
	{
		if (ft_strncmp(par_tok->in[i++], "<<", 2) != 0)
			fd = open(par_tok->in[i], O_RDONLY);
		else if (par_tok->redir_type[is_in_heredoc])
			fd = heredeoc_fd;
		if (fd == -1)
			return (ft_perror(EXIT_FAILURE, "open error"));
		if (par_tok->in[i + 1] == NULL)
			break ;
		if (fd != heredeoc_fd && fd != 0 && fd != 1)
			close(fd);
		i++;
	}
	exp_tok->in = fd;
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
			return (ft_perror(EXIT_FAILURE, "open error"));
		if (par_tok->out[i + 1] == NULL)
			break ;
		if (fd != 0 && fd != 1)
			close(fd);
		i++;
	}
	exp_tok->out = fd;
	return (EXIT_SUCCESS);
}

int	handle_redir(t_par_tok *par_tok, t_exp_tok *exp_tok, int pipe_type)
{
	int	exit_status;

	if (open_in(par_tok, exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (open_out(par_tok, exp_tok) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (handle_pipes(exp_tok, pipe_type) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (par_tok->redir_type[is_pipe] == true)
		exp_tok->is_pipe = true;
	else
		exp_tok->is_pipe = false;
	if (par_tok->type == subshell)
		return (handle_subshell(exp_tok));
	exit_status = executor(exp_tok);
	if (exp_tok->in != STDIN_FILENO)
		close(exp_tok->in);
	if (exp_tok->out != STDOUT_FILENO)
		close(exp_tok->out);
	return (exit_status);
}
