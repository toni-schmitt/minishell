/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_realloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:39:04 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/18 17:44:06 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_str_arr_realloc(char *array[], size_t size)
{
	char	**reallocated;
	int		i;

	i = 0;
	if (array == NULL)
		return (NULL);
	reallocated = ft_calloc(size + 1, sizeof(*reallocated));
	if (reallocated == NULL)
		return (NULL);
	while (array[i])
	{
		reallocated[i] = ft_strdup(array[i]);
		i++;
	}
	ft_free_split(array);
	return (reallocated);
}
