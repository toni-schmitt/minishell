/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_get_set.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 23:17:01 by toni              #+#    #+#             */
/*   Updated: 2021/12/04 23:20:39 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "expander_utils.h"

static t_exp_tok	**_get_exec_toks(t_exp_tok *exec_toks[])
{
	static t_exp_tok	**static_exec_toks = NULL;

	if (exec_toks == NULL)
		return (static_exec_toks);
	static_exec_toks = exec_toks;
	return (static_exec_toks);
}

t_exp_tok	**get_exec_toks(void)
{
	return (_get_exec_toks(NULL));
}

void	set_exec_toks(t_exp_tok *exec_toks[])
{
	_get_exec_toks(exec_toks);
}
