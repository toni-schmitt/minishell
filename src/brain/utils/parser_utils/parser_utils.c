/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:05:39 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/26 19:50:01 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "minishell.h"
#include "parser_utils.h"

void	init_token(t_par_tok **par_tok)
{
	t_iter	*iter;

	if (*par_tok != NULL)
		return ;
	iter = get_iter();
	iter[cmd] = 0;
	iter[in] = 0;
	iter[out] = 0;
	*par_tok = ft_calloc(1 + 1, 100);
	if (*par_tok == NULL)
		return ;
}

int	free_parser(t_par_tok *par_tok[], t_iter *iter, int exit_status)
{
	int	i;

	i = 0;
	while (par_tok[i])
	{
		ft_free_split(par_tok[i]->cmd);
		ft_free_split(par_tok[i]->in);
		ft_free_split(par_tok[i]->out);
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

	init_token(&get_par_toks()[get_iter()[par]]);
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
