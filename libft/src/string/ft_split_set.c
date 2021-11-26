/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 15:20:06 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/26 14:22:03 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	get_arr_len(char *str, char *set)
{
	char	*trimmed_str;
	int		arr_len;
	int		i;

	trimmed_str = ft_strtrim(str, set);
	if (trimmed_str == NULL)
		return (-1);
	arr_len = 0;
	i = 0;
	if (ft_strchr(set, trimmed_str[i]) == NULL)
		arr_len++;
	while (trimmed_str[i])
	{
		if (ft_strchr(set, trimmed_str[i]) != NULL)
			arr_len++;
		i++;
	}
	free(trimmed_str);
	return (arr_len);
}

static size_t	get_element_size(char *str, char *set)
{
	size_t	size;

	size = 0;
	while (*str && ft_strchr(set, *str) == NULL)
	{
		size++;
		str++;
	}
	return (size);
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
	while (i < arr_len && *str)
	{
		while (*str && ft_strchr(set, *str) != NULL)
			str++;
		arr[i] = ft_calloc(get_element_size(str, set) + 1, sizeof(*arr[i]));
		if (arr[i] == NULL)
			return (ft_free_str_array(arr));
		j = 0;
		while (*str && ft_strchr(set, *str) == NULL)
			arr[i][j++] = *str++;
		i++;
	}
	return (arr);
}
