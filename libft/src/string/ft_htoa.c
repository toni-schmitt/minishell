/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_htoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 18:02:40 by tschmitt          #+#    #+#             */
/*   Updated: 2021/09/03 19:19:57 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_convert(unsigned long long dec, int uppcase, char *ptr)
{
	int	r;

	*(--ptr) = '\0';
	if (dec == 0)
		*(--ptr) = '0';
	while (dec != 0)
	{
		ptr--;
		r = dec % 16;
		if (r < 10)
			r += '0';
		else
		{
			if (uppcase == 0)
				r += 'W';
			else
				r += '7';
		}
		*ptr = r;
		dec /= 16;
	}
	return (ptr);
}

char	*ft_htoa(unsigned long long dec, int uppcase)
{
	char	*hexnum;
	char	*ptr;
	int		nbrlen;

	nbrlen = ft_hexnbrlen(dec);
	hexnum = malloc((nbrlen + 1) * sizeof(*hexnum));
	if (hexnum == NULL)
		return (NULL);
	ptr = hexnum + nbrlen + 1;
	return (ft_convert(dec, uppcase, ptr));
}
