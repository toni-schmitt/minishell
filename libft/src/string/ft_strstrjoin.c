/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstrjoin.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 20:51:07 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/03 20:52:17 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
will append s2 to s1
will do nothing if s1, s2 or divider is NULL
it will ad the divider string between the strings
will free s1
*/
char	*ft_strstrjoin(const char *s1, const char *s2, char *divider)
{
	char	*c;
	int		i;
	int		i2;

	if (!s1 || !s2 || !divider)
		return (NULL);
	i = 0;
	i2 = 0;
	s1 = ft_strjoin(s1, divider);
	c = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (c == '\0')
		return (0);
	while (s1[i] != '\0')
	{
		c[i] = s1[i];
		i++;
	}
	while (s2[i2] != '\0')
		c[i++] = s2[i2++];
	c[i] = '\0';
	ft_free(&s1);
	return (c);
}
