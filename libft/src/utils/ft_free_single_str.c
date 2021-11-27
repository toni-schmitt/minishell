/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_single_str.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 22:06:41 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/27 00:32:21 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
will free a single string out of a given array
will move the following strings to fill the gap
*/
void	ft_free_single_str(char ***arr, int i)
{
	if (*arr != NULL)
		ft_free_str(&(*arr)[i++]);
	while (*arr != NULL && (*arr)[i] != NULL)
	{
		(*arr)[i - 1] = (*arr)[i];
		i++;
	}
	(*arr)[--i] = NULL;
	if (*arr != NULL && (*arr)[i] == NULL)
		*arr = ft_realloc_str_arr(*arr, i + 1);
}
