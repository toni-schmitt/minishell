/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc_str_arr.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:35:01 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/10 13:43:09 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

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
char	**ft_realloc_str_arr(char **arr, size_t size)
{
	char	**new;
	int		i;

	if (arr == NULL || *arr == NULL)
		return (NULL);
	if (size <= (size_t)ft_str_arr_len(arr))
		return (arr);
	new = ft_calloc(size + 1, sizeof(*new));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (arr && arr[i])
	{
		new[i] = ft_strdup(arr[i]);
		i++;
	}
	ft_free_str_array(&arr);
	return (new);
}
