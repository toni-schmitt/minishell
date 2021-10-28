/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:35:01 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/28 21:05:47 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_realloc_str_arr(char **arr, size_t size)
/*
this function is similar to realloc, but only for string-arrays
++ instead of malloc this uses calloc
-- it will create a new adress and free the old one of arr
if allocation of the new size fails arr wont be freed
if size is <= to the size of arr, arr will get returned
arr: adress of the array you want to realloc
size: number of elements you want to realloc
new: adress of the reallocated array of strings
*/
{
	char	**new;
	int		i;

	i = 0;
	if (size <= ft_str_arr_len(arr))
		return (arr);
	new = ft_calloc(size, sizeof(char *));
	if (!new)
		return (NULL);
	while (arr && arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	ft_free_split(arr);
	return (new);
}
