/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:05:39 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/29 18:42:22 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "minishell.h"
#include "parser_utils.h"

int	init_curr_par_tok(void)
{
	t_par_tok	**par_toks;
	t_iter		*iter;

	par_toks = get_par_toks();
	iter = get_iter();
	if (par_toks[iter[par]] != NULL)
		return (EXIT_SUCCESS);
	iter[cmd] = 0;
	iter[in] = 0;
	iter[out] = 0;
	par_toks[iter[par]] = ft_calloc(1 + 1, sizeof(*par_toks[iter[par]]));
	if (par_toks[iter[par]] == NULL)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}

int	free_parser(t_par_tok *par_tok[], t_iter *iter, int exit_status)
{
	int	i;

	i = 0;
	while (par_tok[i])
	{
		ft_free_str_array(&par_tok[i]->cmd);
		ft_free_str_array(&par_tok[i]->in);
		ft_free_str_array(&par_tok[i]->out);
		free(par_tok[i]);
		i++;
	}
	free(par_tok);
	free(iter);
	return (exit_status);
}

size_t	get_tokens_size(char *lex_toks[])
{
	size_t	size;
	int		i;

	size = 0;
	i = 0;
	while (lex_toks[i])
	{
		if (ft_strlen(lex_toks[i]) == 2)
		{
			if (ft_strstr(lex_toks[i], "&&") \
			|| ft_strstr(lex_toks[i], "||") \
			|| ft_strstr(lex_toks[i], "<<"))
				size += 2;
		}
		if (ft_strlen(lex_toks[i]) == 1)
		{
			if (ft_strchr(lex_toks[i], '|') \
			|| ft_strchr(lex_toks[i], '(') \
			|| ft_strchr(lex_toks[i], ')'))
				size++;
		}
		i++;
	}
	size++;
	return (size);
}

int	get_subshell_tok(t_iter *iter)
{
	char		*lex_tok;
	t_par_tok	*par_tok;

	if (init_curr_par_tok() == EXIT_FAILURE)
		return (EXIT_FAILURE);
	lex_tok = get_curr_lex_tok();
	par_tok = get_curr_par_tok();
	par_tok->cmd_size++;
	par_tok->cmd = ft_str_arr_realloc(par_tok->cmd, par_tok->cmd_size);
	if (par_tok->cmd == NULL)
		return (EXIT_FAILURE);
	par_tok->cmd[iter[cmd]] = ft_strdup(lex_tok);
	if (par_tok->cmd[iter[cmd]] == NULL)
		return (EXIT_FAILURE);
	iter[cmd]++;
	par_tok->type = subshell;
	iter[lex]++;
	// iter[par]++;
	return (EXIT_BREAK);
}
