/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_single_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/30 22:17:58 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/30 22:52:30 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_add_single_str(char ***arr, int pos, char *new)
{
	int		i;

	i = 0;
	if (new == NULL)
	{
		ft_free_str_array(arr);
		return (NULL);
	}
	ft_realloc_str_arr(*arr, ft_str_arr_len(*arr) + 1);
	if (*arr == NULL)
		return (NULL);
	while (*arr && (*arr)[i] && i < pos)
		i++;
	if (*arr == NULL || (*arr)[i] == NULL)
	{
		ft_free_str_array(arr);
		return (NULL);
	}
	i = ft_str_arr_len(*arr) + 1;
	while (i > pos)
	{
		(*arr)[i] = (*arr)[i - 1];
		i--;
	}
	(*arr)[i] = ft_strdup(new);
	if ((*arr)[i] == NULL)
	{
		ft_free_str_array(arr); // might cause leaks....
		return (NULL);
	}
	return (*arr);
}