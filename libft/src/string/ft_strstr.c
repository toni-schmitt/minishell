/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 13:00:58 by tschmitt          #+#    #+#             */
/*   Updated: 2021/07/07 14:10:39 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *s, const char *to_find)
{
	int	i;

	if (ft_strlen(to_find) == 0)
		return ((char *)s);
	i = 0;
	while (*s)
	{
		if (*s == *to_find)
		{
			i = 0;
			while (s[i] == to_find[i] && s[i])
				i++;
			if (i == ft_strlen(to_find))
				return ((char *)s);
		}
		s++;
	}
	return (0);
}
