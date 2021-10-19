/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:50:39 by tschmitt          #+#    #+#             */
/*   Updated: 2021/09/12 16:57:45 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const char	*buf;

	buf = s;
	while (n > 0)
	{
		if (*buf == (unsigned char)c)
			return ((void *)buf);
		buf++;
		n--;
	}
	return (NULL);
}
