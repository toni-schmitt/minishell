/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_chrcount.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/05 19:01:54 by tschmitt          #+#    #+#             */
/*   Updated: 2021/09/05 19:02:38 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_chrcount(const char *str, char ch)
{
	int	count;

	count = 0;
	while (str && *str)
	{
		if (*str == ch)
			count++;
		str++;
	}
	return (count);
}
