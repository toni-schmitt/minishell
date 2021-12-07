/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iter_get_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:12:29 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/07 19:27:53 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "parser_utils.h"

static t_iter	*_get_iter(t_iter *iter, bool reset)
{
	static t_iter	*static_iter = NULL;

	if (iter == NULL && !reset)
		return (static_iter);
	if (reset)
	{
		static_iter = NULL;
		return (NULL);
	}
	static_iter = iter;
	return (static_iter);
}

t_iter	*get_iter(void)
{
	return (_get_iter(NULL, false));
}

void	set_iter(t_iter *iter)
{
	_get_iter(iter, false);
}

void	reset_iter(void)
{
	_get_iter(NULL, true);
}
