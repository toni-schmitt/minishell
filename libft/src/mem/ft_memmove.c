/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/05 19:45:17 by tschmitt          #+#    #+#             */
/*   Updated: 2021/07/07 15:31:33 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	const char	*src_buf;
	char		*dst_buf;

	if (dst > src)
	{
		src_buf = src + n - 1;
		dst_buf = dst + n - 1;
	}
	else
		return (ft_memcpy(dst, (void *)src, n));
	while (n > 0)
	{
		*dst_buf = *src_buf;
		dst_buf--;
		src_buf--;
		n--;
	}
	return (dst);
}
