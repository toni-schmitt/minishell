/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_dir_items.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 23:11:46 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/15 23:12:23 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parser_utils.h"
#include "brain.h"

static char	**get_next_item(char *n, char *items[], size_t *it_siz, size_t *i)
{
	if (*it_siz == (*i + 2))
	{
		*it_siz += 10;
		items = ft_realloc_str_arr(items, *it_siz);
		if (items == NULL)
			return (NULL);
	}
	items[*i] = ft_strdup(n);
	if (items[*i] == NULL)
		return (ft_free_split(items));
	(*i)++;
	return (items);
}

static char	*get_items_sorted(char **unsorted)
{
	char	*items;
	int		i;

	unsorted = ft_sort_str_arr(unsorted);
	i = 0;
	while (unsorted[i])
	{
		items = ft_append(&items, unsorted[i]);
		if (items == NULL)
			return (ft_free_split(unsorted));
		items = ft_append(&items, " ");
		if (items == NULL)
			return (ft_free_split(unsorted));
		i++;
	}
	ft_free_split(unsorted);
	return (items);
}

char	*get_dir_items(void)
{
	DIR				*d;
	struct dirent	*dir;
	char			**items;
	size_t			items_size;
	size_t			i;

	d = opendir(".");
	if (d == NULL)
		return (NULL);
	i = 0;
	items_size = 10;
	dir = readdir(d);
	items = ft_calloc(items_size + 1, sizeof(*items));
	if (items == NULL)
		return (NULL);
	while (dir != NULL)
	{
		if (dir->d_name[0] != '.')
			items = get_next_item(dir->d_name, items, &items_size, &i);
		if (items == NULL)
			return (NULL);
		dir = readdir(d);
	}
	closedir(d);
	return (get_items_sorted(items));
}
