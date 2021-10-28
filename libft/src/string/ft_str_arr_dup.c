/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_dup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 18:12:28 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/28 19:52:01 by tblaase          ###   ########.fr       */
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

	if (!arr)
		return (NULL);
	i = 0;
	while (arr[i])
		i++;
	cpy = ft_calloc(i + 1, sizeof(char *));
	printf("%d\n", i);
	i = 0;
	while (arr[i])
	{
		cpy[i] = ft_strdup(arr[i]);
		i++;
	}
	return (cpy);
}
