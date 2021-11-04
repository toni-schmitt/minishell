/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 17:35:48 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/04 18:34:53 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
will append s2 to s1
will not free s1 afterwards
*/
char	*ft_strjoin(char *s1, const char *s2)
{
	char	*joined;
	int		joined_len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	joined_len = ft_strlen(s1) + ft_strlen(s2);
	joined = malloc((joined_len + 1) * sizeof(*joined));
	if (joined == NULL)
		return (NULL);
	while (s1 && *s1)
		*joined++ = *s1++;
	while (s2 && *s2)
		*joined++ = *s2++;
	*joined = '\0';
	// ft_free_str(&s1);
	return (joined - joined_len);
}
