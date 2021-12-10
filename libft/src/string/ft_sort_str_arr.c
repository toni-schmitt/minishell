/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sort_str_arr.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 18:59:15 by toni              #+#    #+#             */
/*   Updated: 2021/12/10 19:35:41 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	swap(char **old, char **new)
{
	char	*tmp;

	tmp = *old;
	*old = *new;
	*new = tmp;
}

char	**ft_sort_str_arr(char *unsorted[])
{
	char	*tmp;
	int		unsorted_len;
	int		i;
	int		j;

	if (unsorted == NULL)
		return (NULL);
	unsorted_len = ft_str_arr_len(unsorted);
	tmp = NULL;
	i = 0;
	while (i < unsorted_len)
	{
		j = 0;
		while (j < (unsorted_len - 1 - i))
		{
			if (strcmp(unsorted[j], unsorted[j + 1]) > 0)
				swap(&unsorted[j], &unsorted[j + 1]);
			j++;
		}
		i++;
	}
	return (unsorted);
}
