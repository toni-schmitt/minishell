/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/24 20:05:39 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/02 17:33:38 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "minishell.h"
#include "parser_utils.h"

/**
 * @brief  Allocates current parser token and resets cmd- in- and out-iterator
 * @note   
 * @retval int to indicate success or failure
 */
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

void	free_par_toks(t_par_tok *par_toks[])
{
	int	i;

	i = 0;
	while (par_toks[i])
	{
		ft_free_str_array(&par_toks[i]->cmd);
		ft_free_str_array(&par_toks[i]->in);
		ft_free_str_array(&par_toks[i]->out);
		free(par_toks[i]);
		i++;
	}
	free(par_toks);
}

/**
 * @brief  Correctly frees allocated memory for parser tokens and iterator
 * @note   
 * @param  *par_tok[]: Parser Tokens
 * @param  *iter: Iterator of Parser Tokens, Lexer Tokens, Command-, In- and 
 * * Out-Array
 * @param  exit_status: Exit status to return
 * @retval Returns exit_status
 */
int	free_parser(t_par_tok *par_tok[], t_iter *iter, int exit_status)
{
	free_par_toks(par_tok);
	free(iter);
	return (exit_status);
}

/**
 * @brief  Returns correct size for allocation of Parser-Tokens-Array
 * @note   
 * @param  *lex_toks[]: 
 * @retval Correct Size for allocation
 */
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
