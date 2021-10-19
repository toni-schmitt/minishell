/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/07 18:41:59 by tschmitt          #+#    #+#             */
/*   Updated: 2021/09/16 16:30:23 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

static int	get_next_char(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != c)
		i++;
	return (i);
}

static int	ft_get_array_size(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s)
	{
		if (*s != c)
		{
			i++;
			s = s + get_next_char((char *)s, c);
		}
		else
			s++;
	}
	return (i);
}

static void	*ft_free_array(char ***a, int i)
{
	int	j;

	j = 0;
	if (!(*a))
		return (NULL);
	while (j < i)
	{
		j++;
		if ((*a)[j])
			free((*a)[j]);
	}
	free(*a);
	return (NULL);
}

static void	ft_gettochar(const char **s, char c)
{
	while (**s == c)
		(*s)++;
}

char	**ft_split(const char *s, char c)
{
	int		size;
	int		i[2];
	char	**array;

	if (s == NULL)
		return (NULL);
	size = ft_get_array_size(s, c);
	if (size == 0)
		return (NULL);
	array = ft_calloc(size + 1, sizeof(char *));
	if (array == NULL)
		return (NULL);
	i[0] = 0;
	while (i[0] < size)
	{
		ft_gettochar(&s, c);
		array[i[0]] = ft_calloc(get_next_char((char *)s, c) + 1, sizeof(char));
		if (array[i[0]] == NULL)
			return (ft_free_array(&array, size + 1));
		i[1] = 0;
		while (*s && *s != c)
			array[i[0]][i[1]++] = *s++;
		i[0]++;
	}
	return (array);
}
