/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 19:55:37 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/28 21:10:44 by tblaase          ###   ########.fr       */
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

	if (size <= (size_t)ft_strlen(str))
		return (str);
	i = 0;
	new = ft_calloc(size, sizeof(char));
	if (!new)
		return (NULL);
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	free(str);
	return (new);
}
