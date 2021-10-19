/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/25 18:37:16 by tschmitt          #+#    #+#             */
/*   Updated: 2021/09/02 19:40:27 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(char *str, size_t n)
{
	char	*duped;
	int		i;
	size_t	duped_len;

	duped_len = n;
	i = 0;
	duped = malloc((duped_len + 1) * sizeof(*duped));
	if (duped == NULL)
		return (NULL);
	while (n--)
	{
		duped[i] = str[i];
		i++;
	}
	duped[i] = '\0';
	return (duped);
}
