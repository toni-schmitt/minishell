/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/13 17:13:19 by tschmitt          #+#    #+#             */
/*   Updated: 2021/08/15 18:04:05 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	*ft_assigndigits(char *snbr, long lnbr, int i)
{
	int	nbr;
	int	r;

	r = 0;
	nbr = lnbr;
	snbr += i;
	*snbr = '\0';
	if (nbr == 0)
		*(--snbr) = '0';
	while (lnbr != 0)
	{
		snbr--;
		r = lnbr % 10;
		if (r < 0)
			r *= -1;
		*snbr = r + '0';
		lnbr /= 10;
	}
	if (nbr < 0)
		*(--snbr) = '-';
	return (snbr);
}

char	*ft_itoa(int nbr)
{
	char	*snbr;
	long	lnbr;
	int		i;

	lnbr = nbr;
	i = ft_nbrlen(lnbr);
	if (nbr < 0)
		i++;
	snbr = malloc(sizeof(*snbr) * (i + 1));
	if (snbr == NULL)
		return (NULL);
	snbr = ft_assigndigits(snbr, lnbr, i);
	return (snbr);
}
