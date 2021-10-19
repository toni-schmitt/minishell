/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_append.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 17:39:22 by tschmitt          #+#    #+#             */
/*   Updated: 2021/09/03 19:19:51 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* Appends src to dst, frees dst and returns newly created string */
char	*ft_append(char **dst, char *src)
{
	char	*dst_buf;
	char	*appendet;
	int		appendet_len;

	dst_buf = *dst;
	appendet_len = ft_strlen(dst_buf) + ft_strlen(src);
	if (appendet_len == 0)
		return (NULL);
	appendet = malloc((appendet_len + 1) * sizeof(*appendet));
	if (appendet == NULL)
		return (NULL);
	while (dst_buf && *dst_buf)
		*appendet++ = *dst_buf++;
	while (src && *src)
		*appendet++ = *src++;
	*appendet = '\0';
	ft_free((void *)dst);
	return (appendet - appendet_len);
}
