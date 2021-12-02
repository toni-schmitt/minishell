/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   par_tok_get_set.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:11:15 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/02 21:21:09 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "parser_utils.h"
#include "minishell.h"

static t_par_tok	**_get_par_toks(t_par_tok **par_toks)
{
	static t_par_tok	**static_par_toks = NULL;

	if (par_toks == NULL)
		return (static_par_toks);
	static_par_toks = par_toks;
	return (static_par_toks);
}

t_par_tok	*get_curr_par_tok(void)
{
	t_iter	*iter;

	iter = get_iter();
	if (iter == NULL)
		return (NULL);
	return (get_par_toks()[iter[par]]);
}

t_par_tok	**get_par_toks(void)
{
	return (_get_par_toks(NULL));
}

void	set_par_toks(t_par_tok **par_toks)
{
	_get_par_toks(par_toks);
}
