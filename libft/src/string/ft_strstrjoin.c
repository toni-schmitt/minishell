/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:51:07 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/09 17:39:11 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
will append s2 to s1
will do nothing if s1 or divider is NULL
it will ad the divider string between the strings
will free s1
*/
char	*ft_strstrjoin(char *s1, char *s2, char *divider)
{
	char	*out;
	int		i;
	int		j;

	if (!s1 || !divider)
		return (NULL);
	i = 0;
	j = 0;
	s1 = ft_append(&s1, divider);
	out = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (out == NULL)
		return (0);
	while (s1[i])
	{
		out[i] = s1[i];
		i++;
	}
	while (s2 && s2[j])
		out[i++] = s2[j++];
	out[i] = '\0';
	ft_free_str(&s1);
	return (out);
}
