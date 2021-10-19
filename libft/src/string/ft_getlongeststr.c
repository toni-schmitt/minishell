/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getlongeststr.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 21:25:03 by tschmitt          #+#    #+#             */
/*   Updated: 2021/08/25 21:29:42 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
	Returns a char pointer to the longest string in the double pointer array
	Assumes that array ends with NULL to determin it's size.
*/
char	*ft_getlongeststr(char **array)
{
	int		max_len;
	int		tmp_len;
	char	*longest_str;

	if (array == NULL)
		return (NULL);
	max_len = ft_strlen(*array);
	longest_str = *array;
	array++;
	while (array && *array)
	{
		tmp_len = ft_strlen(*array);
		if (tmp_len > max_len)
		{
			max_len = tmp_len;
			longest_str = *array;
		}
		array++;
	}
	return (longest_str);
}
