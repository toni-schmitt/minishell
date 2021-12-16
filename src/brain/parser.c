/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:35:35 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/16 19:16:41 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "parser_utils.h"

#define NO_OF_ITERATORS 5

/**
 * @brief  Trys to get correct current parser token
 * @note   Helper function of get_tokens
 * @param  *lex_toks[]:
 * @param  *par_toks[]:
 * @param  *iter:
 * @retval int to indicate exit status
 */
static int	get_par_tok(char *lex_toks[], t_par_tok *par_toks[], t_iter *iter)
{
	int	tmp;

	tmp = EXIT_SUCCESS;
	tmp = get_tok_type(lex_toks[iter[lex]], iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	tmp = get_tok_redir(lex_toks, iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	tmp = get_tok_cmd(lex_toks[iter[lex]], par_toks[iter[par]], iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	tmp = get_special_tok(lex_toks[iter[lex]], par_toks, iter);
	if (tmp != EXIT_SUCCESS)
		return (tmp);
	return (EXIT_SUCCESS);
}

/**
 * @brief  Trys to create correct tokens for expander
 * @note
 * @param  *lex_toks[]: Tokens from lexer to create parser tokens from
 * @retval int to indicate exit status
 */
static int	get_tokens(char *lex_toks[])
{
	t_par_tok	**par_toks;
	t_iter		*iter;
	int			get_par_tok_exit_status;

	iter = ft_calloc(NO_OF_ITERATORS + 1, sizeof(*iter));
	if (iter == NULL)
		return (EXIT_FAILURE);
	set_iter(iter);
	par_toks = ft_calloc(get_tokens_size(lex_toks) + 1, sizeof(*par_toks));
	if (par_toks == NULL)
		return (EXIT_FAILURE);
	set_par_toks(par_toks);
	while (lex_toks[iter[lex]])
	{
		get_par_tok_exit_status = get_par_tok(lex_toks, par_toks, iter);
		if (get_par_tok_exit_status == EXIT_FAILURE)
			return (free_parser(par_toks, iter, EXIT_FAILURE));
		else if (get_par_tok_exit_status == EXIT_SYNTAX_ERROR)
			return (free_parser(par_toks, iter, EXIT_SYNTAX_ERROR));
	}
	free(iter);
	return (EXIT_SUCCESS);
}

static char	**interprete_env_vars(char *lex_toks[])
{
	int		i;
	// char	*temp;

	i = 0;
	while (lex_toks[i])
	{
		lex_toks[i] = interprete_env_var(lex_toks[i]);
		if (lex_toks[i] == NULL)
			return (NULL);
		if (ft_strstr(lex_toks[i], "&&") || ft_strstr(lex_toks[i], "||"))
			break ;
		i++;
	}
	return (lex_toks);
}

int	parser(char *lexer_tokens[])
{
	t_par_tok	**tokens;
	int			exit_code;

	lexer_tokens = interprete_env_vars(lexer_tokens);
	if (lexer_tokens == NULL)
		return (EXIT_FAILURE);
	set_lex_toks(lexer_tokens);
	exit_code = get_tokens(lexer_tokens);
	if (exit_code == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (exit_code == EXIT_SYNTAX_ERROR)
		return (EXIT_SUCCESS);
	tokens = get_par_toks();
	return (free_par_toks(tokens, expander(tokens)));
}
