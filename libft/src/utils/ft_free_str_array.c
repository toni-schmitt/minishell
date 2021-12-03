/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 17:05:35 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/03 11:05:24 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Frees allocated array returned by ft_split function.
 * Assumes that ft_split successfully split the string.
 * Returns NULL
*/
void	*ft_free_split(char **split)
{
	//Toni's version!!!!!
	int	i;

	i = 0;
	while (*arr && (*arr)[i])
	{
		ft_free_str(&(*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(split);
	return (NULL);
}
