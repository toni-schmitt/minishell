/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_arr_len.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 20:56:50 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/28 21:00:12 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_str_arr_len(char **arr)
/*
returns the size of an nullterminated array of strings
*/
{
	int	i;

	i = 0;
	while (arr && arr[i])
		i++;
	return (i);
}
