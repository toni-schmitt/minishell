/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_split.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 17:05:35 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/26 18:02:40 by tblaase          ###   ########.fr       */
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
	while (split && split[i])
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (NULL);
}