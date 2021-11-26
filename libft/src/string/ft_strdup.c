/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/06 14:09:09 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/24 22:26:53 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *str)
{
	char	*duped;
	int		duped_len;

	duped_len = ft_strlen(str);
	if (str == NULL)
		return (NULL);
	duped = malloc((duped_len + 1) * sizeof(*duped));
	if (duped == NULL)
		return (NULL);
	while (str && *str)
		*duped++ = *str++;
	*duped = '\0';
	return (duped - duped_len);
}
