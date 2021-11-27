/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:39:04 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/27 02:01:49 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str_arr_realloc(char *array[], size_t size)
{
	char	**reallocated;
	int		i;

	reallocated = ft_calloc(size + 1, sizeof(*reallocated));
	if (reallocated == NULL)
		return (NULL);
	i = 0;
	while (size-- && array && array[i])
	{
		reallocated[i] = ft_strdup(array[i]);
		i++;
	}
	ft_free_str_array(&array);
	return (reallocated);
}
