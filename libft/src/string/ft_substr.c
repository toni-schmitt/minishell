/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 16:51:51 by tschmitt          #+#    #+#             */
/*   Updated: 2021/09/09 10:42:30 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	int		i;
	char	*substr;
	int		str_len;

	i = 0;
	str_len = ft_strlen(s);
	if (s == NULL || str_len == 0)
		return (NULL);
	if (start > (size_t)ft_strlen(s))
		return (ft_calloc(1, 1));
	substr = malloc(sizeof(*substr) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while (len-- && start < (unsigned int)str_len)
		substr[i++] = s[start++];
	substr[i] = '\0';
	return (substr);
}
