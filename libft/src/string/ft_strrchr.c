/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 12:54:32 by tschmitt          #+#    #+#             */
/*   Updated: 2021/09/12 17:05:23 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strrchr(const char *s, int c)
{
	int			i;
	const char	*p;

	i = ft_strlen(s);
	p = NULL;
	while (i >= 0)
	{
		if (s[i] == (char)c)
		{
			p = &s[i];
			return ((char *)p);
		}
		i--;
	}
	return ((char *)p);
}
