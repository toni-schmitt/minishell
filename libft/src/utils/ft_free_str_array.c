/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str_array.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/24 17:05:35 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/26 18:18:52 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
 * Frees allocated null-terminated string array
*/
void	ft_free_str_array(char ***arr)
{
	//Tim's version!!!!!!
	int	i;

	i = 0;
	while (*arr && (*arr)[i])
	{
		ft_free_str(&(*arr)[i]);
		(*arr)[i] = NULL;
		i++;
	}
	free(*arr);
	*arr = NULL;
}
