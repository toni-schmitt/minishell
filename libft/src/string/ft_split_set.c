/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:20:06 by tschmitt          #+#    #+#             */
/*   Updated: 2021/10/29 16:18:32 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_arr_len(char *str, char *set)
{
	int	arr_len;

	arr_len = 0;
	if (ft_strchr(set, *str) == NULL)
		arr_len++;
	while (*str)
	{
		if (ft_strchr(set, *str) != NULL)
			arr_len++;
		str++;
	}
	return (arr_len);
}

static void	*free_arr(char **arr)
{
	int	j;

	j = 0;
	while (arr && arr[j])
		free(arr[j++]);
	free(arr);
	return (NULL);
}

char	**ft_split_set(char *str, char *set)
{
	char	**arr;
	int		arr_len;
	int		i;
	int		j;

	if (str == NULL || set == NULL)
		return (NULL);
	arr_len = get_arr_len(str, set);
	arr = ft_calloc(arr_len + 1, sizeof(*arr));
	if (arr == NULL)
		return (NULL);
	i = 0;
	while (i < arr_len)
	{
		while (*str && ft_strchr(set, *str) != NULL)
			str++;
		arr[i] = ft_calloc(100, sizeof(*arr[i]));
		if (arr[i] == NULL)
			return (free_arr(arr));
		j = 0;
		while (*str && ft_strchr(set, *str) == NULL)
			arr[i][j++] = *str++;
		i++;
	}
	return (arr);
}
