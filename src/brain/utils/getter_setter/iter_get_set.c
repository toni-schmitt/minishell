/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_get_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:12:29 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/24 20:36:57 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "parser_utils.h"

static t_iter	*_get_iter(t_iter *iter)
{
	static t_iter	*static_iter = NULL;

	if (iter == NULL)
		return (static_iter);
	static_iter = iter;
	return (static_iter);
}

t_iter	*get_iter(void)
{
	return (_get_iter(NULL));
}

void	set_iter(t_iter *iter)
{
	_get_iter(iter);
}
