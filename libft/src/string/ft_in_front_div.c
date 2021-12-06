/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_in_front.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:42:05 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/26 23:53:45 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
this will add src infront of dst divided by div
dst will be free'd
returns NULL if dst == NULL or src == NULL or if error
*/
char	*ft_in_front_div(char **dst, char *src, char *div)
{
	char	*out;

	out = ft_strdup(src);
	if (out == NULL)
		return (NULL);
	out = ft_append(&out, div);
	if (out == NULL)
		return (NULL);
	out = ft_append(&out, *dst);
	if (out == NULL)
		return (NULL);
	ft_free_str(dst);
	return (out);
}
