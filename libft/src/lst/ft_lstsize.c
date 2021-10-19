/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 17:40:21 by tschmitt          #+#    #+#             */
/*   Updated: 2021/07/10 20:06:01 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *list)
{
	int		i;
	t_list	*c;

	if (list == NULL)
		return (0);
	i = 1;
	c = list;
	while (c->next != 0)
	{
		c = c->next;
		i++;
	}
	return (i);
}
