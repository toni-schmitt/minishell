/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:45:36 by tschmitt          #+#    #+#             */
/*   Updated: 2021/07/06 18:17:40 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

void	*ft_memcpy(void *dst, void *src, size_t n)
{
	char	*src_buf;
	char	*dst_buf;

	if (dst == NULL && src == NULL)
		return (NULL);
	src_buf = src;
	dst_buf = dst;
	while (n > 0)
	{
		*dst_buf = *src_buf;
		dst_buf++;
		src_buf++;
		n--;
	}
	return (dst);
}
