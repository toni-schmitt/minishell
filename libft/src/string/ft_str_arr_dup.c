/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:12:28 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/29 14:33:04 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str_arr_dup(char **arr)
/*
strdup for string arrays
arr: the array to copy
cpy: the copied array that gets returned
*/
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
