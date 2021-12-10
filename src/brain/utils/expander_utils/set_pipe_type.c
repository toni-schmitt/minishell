/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_pipe_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 11:35:34 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/10 12:43:34 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"

int	set_pipe_type(t_par_tok **par_toks, int i)
{
	int	pipe_type;

	pipe_type = -1;
	if (par_toks[i]->redir_type[is_pipe] == false)
		return (pipe_type);
	else if (i > 0)
	{
		if (par_toks[i - 1]->redir_type[is_pipe]
			&& par_toks[i]->redir_type[is_pipe] && (par_toks[i + 1] == NULL
				|| par_toks[i + 1]->redir_type[is_pipe] == false))
			pipe_type = 0;
		else if (par_toks[i - 1]->redir_type[is_pipe] == false
			&& par_toks[i]->redir_type[is_pipe] && par_toks[i + 1] != NULL
			&& par_toks[i + 1]->redir_type[is_pipe])
			pipe_type = 1;
		else if (par_toks[i - 1]->redir_type[is_pipe]
			&& par_toks[i]->redir_type[is_pipe] && par_toks[i + 1] != NULL
			&& par_toks[i + 1]->redir_type[is_pipe])
			pipe_type = 2;
	}
	else if (par_toks[i]->redir_type[is_pipe] && par_toks[i + 1] != NULL
		&& par_toks[i + 1]->redir_type[is_pipe])
		pipe_type = 1;
	// fprintf(stderr, "the pipe_type of %s is %d\n", par_toks[i]->cmd[0], pipe_type);
	return (pipe_type);
}
