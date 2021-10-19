/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/09 18:53:00 by tschmitt          #+#    #+#             */
/*   Updated: 2021/07/10 14:48:13 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*newlst;
	t_list	*newele;

	newlst = NULL;
	while (lst != NULL)
	{
		newele = ft_lstnew((*f)(lst->content));
		if (newele == NULL)
		{
			ft_lstclear(&newlst, (*del));
			free(newlst);
			return (NULL);
		}
		ft_lstadd_back(&newlst, newele);
		lst = lst->next;
	}
	return (newlst);
}
