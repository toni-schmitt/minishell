/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:39:06 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/07 19:32:27 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"

static int	free_exp_toks(t_exp_tok *exp_toks[], int exit_status)
{
	int	i;

	i = 0;
	while (exp_toks[i])
	{
		ft_free_str_array(&exp_toks[i]->cmd);
		free(exp_toks[i]);
		i++;
	}
	free(exp_toks);
	reset_exp_toks();
	return (exit_status);
}

static size_t	get_tok_size(t_par_tok *par_toks[])
{
	size_t	size;

	size = 0;
	while (par_toks[size])
		size++;
	return (size);
}

static int	init(t_exp_tok **exp_tok)
{
	*exp_tok = malloc(sizeof(**exp_tok));
	if (*exp_tok == NULL)
		return (EXIT_FAILURE);
	(*exp_tok)->cmd = NULL;
	(*exp_tok)->in = 0;
	(*exp_tok)->out = 1;
	return (EXIT_SUCCESS);
}

static int	get_tokens(t_par_tok *par_toks[])
{
	t_exp_tok	**exp_toks;
	int			i;

	exp_toks = ft_calloc(get_tok_size(par_toks) + 1, sizeof(*exp_toks));
	if (exp_toks == NULL)
		return (EXIT_FAILURE);
	set_exp_toks(exp_toks);
	i = 0;
	while (par_toks[i])
	{
		if (init(&exp_toks[i]) == EXIT_FAILURE)
			return (free_exp_toks(exp_toks, EXIT_FAILURE));
		if (par_toks[i]->cmd)
		{
			exp_toks[i]->cmd = ft_str_arr_dup(par_toks[i]->cmd);
			if (exp_toks[i]->cmd == NULL)
				return (free_exp_toks(exp_toks, EXIT_FAILURE));
		}
		if (par_toks[i]->redir_type[is_in_heredoc])
			if (wait_for_heredoc(par_toks[i], exp_toks[i]) == EXIT_FAILURE)
				return (free_exp_toks(exp_toks, EXIT_FAILURE));
		i++;
	}
	return (EXIT_SUCCESS);
}

int	open_all_redirs(char **redir, t_redir_type *redir_type)
{
	int		i;
	int		fd;

	i = 0;
	if (redir == NULL)
		return (-1);
	if (redir[i] == NULL)
	{
		if (redir_type[is_pipe] == is_pipe)
			return (0);
	}
	while (true)
	{
		if (redir_type[is_in] || redir_type[is_pipe])
			fd = open(redir[i], O_RDONLY);
		else if (redir_type[is_out] || redir_type[is_pipe])
			fd = open(redir[i], O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (redir_type[is_out_append])
			fd = open(redir[i], O_RDWR | O_CREAT | O_APPEND, 0644);
		else if (redir_type[is_in_heredoc])
			fd = 3;
		if (fd == -1)
		{
			perror("ERROR");
			return (errno);
		}
		if (redir[i + 1] == NULL)
			break ;
		i++;
	}
	return (fd);
}

static int	handle_redir(t_par_tok **par_toks, t_exp_tok **exp_toks)
{
	int	i;

	i = 0;
	while (par_toks && par_toks[i] && exp_toks && exp_toks[i])
	{
		exp_toks[i]->in = open_all_redirs(par_toks[i]->in, par_toks[i]->redir_type); //ask toni if this typecasting i the correct way to get the redir_type
		exp_toks[i]->out = open_all_redirs(par_toks[i]->out, par_toks[i]->redir_type);
		if (exp_toks[i]->in == -1 || exp_toks[i]->out == -1)
			return (EXIT_FAILURE);
		i++;
	}
	return (EXIT_SUCCESS);
}

int	expander(t_par_tok *par_toks[])
{
	t_exp_tok	**exp_toks;

	if (get_tokens(par_toks) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	exp_toks = get_exp_toks();
	if (handle_redir(par_toks, exp_toks) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (executor(exp_toks) == EXIT_FAILURE)
	{
		free_exp_toks(exp_toks, EXIT_FAILURE);
		return (EXIT_FAILURE);
	}
	free_exp_toks(exp_toks, EXIT_SUCCESS);
	return (EXIT_SUCCESS);
}

/* for checking if a command is valid
	if (access(argv[1], F_OK) != 0)
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
*/