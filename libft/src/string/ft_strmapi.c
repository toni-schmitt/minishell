/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 18:22:02 by tschmitt          #+#    #+#             */
/*   Updated: 2021/09/03 19:20:25 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*iterated;
	int		i;

	if (s == NULL || (*f) == NULL)
		return (NULL);
	iterated = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (iterated == NULL)
		return (NULL);
	i = 0;
	while (s[i])
	{
		iterated[i] = f(i, s[i]);
		i++;
	}
	iterated[i] = 0;
	return (iterated);
}
