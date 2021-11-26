/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:12:28 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/02 16:17:01 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
strdup for string arrays
arr: the array to copy
cpy: the copied array that gets returned
*/
char	**ft_str_arr_dup(char **arr)
{
	char	**cpy;
	int		i;

	if (arr == NULL)
		return (NULL);
	cpy = ft_calloc(ft_str_arr_len(arr) + 1, sizeof(*cpy));
	if (cpy == NULL)
		return (NULL);
	i = 0;
	while (arr[i])
	{
		cpy[i] = ft_strdup(arr[i]);
		i++;
	}
	return (cpy);
}
