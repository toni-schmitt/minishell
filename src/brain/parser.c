/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:35:35 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/16 21:27:53 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define TOKEN_FOUND 1
#define TOKEN_NOT_FOUND 0

static t_par_tok_type	try_get_token_type(char *token)
{
	if (ft_strlen(token) == 1)
	{
		if (ft_strchr(token, '|'))
			return (pipe_redir);
		if (ft_strchr(token, '<'))
			return (in_out_redir);
		if (ft_strchr(token, '>'))
			return (in_out_redir);
	}
	if (ft_strlen(token) == 2)
	{
		if (ft_strstr(token, "<<"))
			return (heredoc);
		if (ft_strstr(token, "&&"))
			return (and);
		if (ft_strstr(token, "||"))
			return (or);
	}
	// if (ft_strchr(token, '\''))
	// 	return (single_quote);
	// if (ft_strchr(token, '\"'))
	// 	return (double_quote);
	return (std);
}

typedef enum e_iterator
{
	lex = 0,
	par = 1,
	cmd = 2,
	in = 3,
	out = 4,
}	t_iterator;

static int	try_get_redir_token(
	char *lex_toks[], t_parser_tok *tokens, t_iterator *iter)
{
	if (ft_strchr(lex_toks[iter[lex]], '<') && ft_strlen(lex_toks[iter[lex]]) == 1)
	{
		tokens[iter[par]].in[iter[in]] = ft_strdup(lex_toks[iter[lex]]);
		if (tokens[iter[par]].in[iter[in]] == NULL)
			return (EXIT_FAILURE);
		iter[in]++;
		iter[lex]++;
		tokens[iter[par]].in[iter[in]] = ft_strdup(lex_toks[iter[lex]]);
		if (tokens[iter[par]].in[iter[in]] == NULL)
			return (EXIT_FAILURE);
		iter[in]++;
		iter[lex]++;
	}
	if ((ft_strchr(lex_toks[iter[lex]], '>') && ft_strlen(lex_toks[iter[lex]]) == 1) \
	|| (ft_strstr(lex_toks[iter[lex]], ">>") && ft_strlen(lex_toks[iter[lex]]) == 2))
	{
		tokens[iter[par]].out[iter[out]] = ft_strdup(lex_toks[iter[lex]]);
		if (tokens[iter[par]].out[iter[out]] == NULL)
			return (EXIT_FAILURE);
		iter[out]++;
		iter[lex]++;
		tokens[iter[par]].out[iter[out]] = ft_strdup(lex_toks[iter[lex]]);
		if (tokens[iter[par]].out[iter[out]] == NULL)
			return (EXIT_FAILURE);
		iter[out]++;
		iter[lex]++;
	}
	return (EXIT_SUCCESS);
}

static void	*exit_get_tokens(t_parser_tok *tokens, t_iterator *iter)
{
	int i;

	i = 0;
	while (&tokens[i])
	{
		ft_free_split(tokens[i].cmd);
		ft_free_split(tokens[i].in);
		ft_free_split(tokens[i].out);
		i++;
	}
	free(tokens);
	free(iter);
	return (NULL);
}

static int	init_token(t_parser_tok *token, t_iterator *iter)
{
	iter[cmd] = 0;
	iter[in] = 0;
	iter[out] = 0;
	token->cmd = ft_calloc(100, sizeof(*token->cmd));
	if (token->cmd == NULL)
		return (EXIT_FAILURE);
	token->in = ft_calloc(100, sizeof(*token->in));
	if (token->in == NULL)
		return (EXIT_FAILURE);
	token->out = ft_calloc(100, sizeof(*token->out));
	if (token->out == NULL)
		return (EXIT_FAILURE);
	token->type = std;
	return (EXIT_SUCCESS);
}

static bool	is_end_of_token(char *token)
{
	if (ft_strlen(token) == 1)
	{
		if (ft_strchr(token, '|'))
			return (true);
		if (ft_strchr(token, '('))
			return (true);
		if (ft_strchr(token, ')'))
			return (true);
	}
	if (ft_strlen(token) == 2)
	{
		if (ft_strstr(token, "&&"))
			return (true);
		if (ft_strstr(token, "||"))
			return (true);
	}
	return (false);
}

static bool	is_valid_syntax(t_parser_tok token)
{
	(void)token;
	return (true);
}

static char	*try_get_token_cmd(char *token)
{
	if (ft_strlen(token) == 1)
	{
		if (ft_strchr(token, '|'))
			return (NULL);
		if (ft_strchr(token, '('))
			return (NULL);
		if (ft_strchr(token, ')'))
			return (NULL);
		if (ft_strchr(token, '>'))
			return (NULL);
		if (ft_strchr(token, '<'))
			return (NULL);
	}
	if (ft_strlen(token) == 2)
	{
		if (ft_strstr(token, ">>"))
			return (NULL);
		if (ft_strstr(token, "&&"))
			return (NULL);
		if (ft_strstr(token, "||"))
			return (NULL);
	}
	return (ft_strdup(token));
}

int	try_get_special_token(char *lex_toks[], t_parser_tok *tokens, t_iterator *iter)
{
	int	i;

	if (iter[lex] == 0)
		i = 0;
	else
		i = iter[lex] - 1;
	if (ft_strlen(lex_toks[i]) == 2)
	{
		if (ft_strstr(lex_toks[i], "&&"))
		{
			iter[par]++;
			tokens[par].cmd = NULL;
			tokens[par].in = NULL;
			tokens[par].out = NULL;
			tokens[par].type = and;
			return (TOKEN_FOUND);
		}
		if (ft_strstr(lex_toks[i], "||"))
		{
			iter[par]++;
			tokens[par].cmd = NULL;
			tokens[par].in = NULL;
			tokens[par].out = NULL;
			tokens[par].type = or;
			return (TOKEN_FOUND);
		}
	}
	return (TOKEN_NOT_FOUND);
}

static t_parser_tok	*get_tokens(char *lex_toks[])
{
	t_parser_tok	*tokens;
	t_iterator		*iter;

	iter = ft_calloc(6, sizeof(*iter));
	if (iter == NULL)
		return (NULL);
	tokens = ft_calloc(100 + 1, sizeof(*tokens));
	if (tokens == NULL)
		return (NULL);
	while (lex_toks[iter[lex]])
	{
		if (init_token(&tokens[iter[par]], iter) == EXIT_FAILURE)
			return (NULL);
		while (lex_toks[iter[lex]])
		{
			tokens[iter[par]].type = try_get_token_type(lex_toks[iter[lex]]);
			if (try_get_redir_token(lex_toks, tokens, iter) == EXIT_FAILURE)
				return (exit_get_tokens(tokens, iter));	
			tokens[iter[par]].cmd[iter[cmd]++] = try_get_token_cmd(lex_toks[iter[lex]]);
			iter[lex]++;
			if (try_get_special_token(lex_toks, tokens, iter) == TOKEN_FOUND)
				break ;
			if (is_end_of_token(lex_toks[iter[lex] - 1]))
				break ;
		}
		if (!is_valid_syntax(tokens[iter[par]]))
			return ((void *)2);
		iter[par]++;
	}
	return (tokens);
}

void prnt_token(t_parser_tok *tok)
{
	for (int i = 0; &tok[i]; i++)
	{
		printf("Token[%i]\n", i);
		printf("%p\n", &tok[i]);
		printf("Token-Type: %i\n", tok[i].type);
		printf("Token-Cmd:\n");
		for (int j = 0; tok[i].cmd[j]; j++)
			printf("%s\t", tok[i].cmd[j]);
		printf("\n");
		printf("Token-In:\n");
		for (int k = 0; tok[i].in[k]; k++)
			printf("%s\t", tok[i].in[k]);
		printf("\n");
		printf("Token-Out:\n");
		for (int l = 0; tok[i].out[l]; l++)
			printf("%s\t", tok[i].out[l]);
		printf("\n");
	}
	printf("\n");
}

int	parser(char *lexer_tokens[])
{
	t_parser_tok	*tokens;

	for (int i = 0; lexer_tokens[i]; i++)
		printf("%s\n", lexer_tokens[i]);
	// return printf("\n");
	tokens = get_tokens(lexer_tokens);
	if (tokens == NULL)
		return (EXIT_FAILURE);
	prnt_token(tokens);
	if (expander(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
