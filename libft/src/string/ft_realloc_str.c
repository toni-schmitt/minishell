/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 19:55:37 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/29 14:24:53 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc_str(char *str, size_t size)
/*
this function is similar to realloc, but only for strings
++ instead of malloc this uses calloc
-- it will create a new adress and free the old one of str
if allocation of the new size fails str wont be freed
if size is <= to the size of str, str will get returned
str: adress of the string you want to realloc
size: number of elements you want to realloc
new: adress of the reallocated string
*/
{
	char	*new;
	int		i;

	if (str == NULL)
		return (NULL);
	if (size <= (size_t)ft_strlen(str))
		return (str);
	new = ft_calloc(size, sizeof(*new));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	return (new);
}
