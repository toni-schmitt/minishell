/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete_env_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:13:27 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/13 15:48:47 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "minishell.h"
#include "parser_utils.h"
#include "env_var_utils.h"

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

static char	*get_dir_items(void)
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

static char	*get_var(char *lex_tok)
{
	char	*var;
	char	*lex_buf;
	int		i;

	lex_buf = lex_tok;
	var = ft_calloc(ft_strlen(lex_buf) + 1, sizeof(*var));
	if (var == NULL)
		return (NULL);
	lex_buf = ft_strchr(lex_buf, '$') + 1;
	i = 0;
	while (lex_buf && *lex_buf && ft_isalpha(*lex_buf))
		var[i++] = *lex_buf++;
	free(lex_tok);
	return (var);
}

/**
 * @brief  Interprets enviroment variables of current lexer token
 * @note   Frees current lex_tok if necessary
 * @param  *lex_tok: Current lexer token
 * @retval Returns interpreted lexer token
 */
char	*interprete_env_var(char *lex_tok)
{
	char	*interpreted_token;
	char	*var;

	interpreted_token = lex_tok;
	if (!ft_strchr(lex_tok, '\'') && ft_strlen(lex_tok) > 1 \
	&& ft_strchr(lex_tok, '$'))
	{
		if (ft_strstr(lex_tok, "$?"))
		{
			free(lex_tok);
			return (ft_itoa(get_err_code()));
		}
		var = get_var(lex_tok);
		if (var == NULL)
			return (NULL);
		interpreted_token = get_env_var_value(get_envv(), var);
		free(var);
	}
	if (!ft_strchr(lex_tok, '\'') && !ft_strchr(lex_tok, '\"') \
	&& ft_strchr(lex_tok, '*'))
	{
		free(lex_tok);
		return (get_dir_items());
	}
	return (interpreted_token);
}
