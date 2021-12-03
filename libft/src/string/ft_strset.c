/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/30 16:39:26 by toni              #+#    #+#             */
/*   Updated: 2021/10/30 16:42:29 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* 
 * Returns the first found character of set in str 
 * or NULL if no character of set is found in str 
 */
char	*ft_strset(char *str, char *set)
{
	int	i;

	i = 0;
	while (str && *str)
	{
		i = 0;
		while (set && set[i])
		{
			if (*str == set[i])
				return (str);
			i++;
		}
		str++;
	}
	return (NULL);
}
