/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 21:35:35 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/29 19:51:18 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "brain.h"
#include "parser_utils.h"

#define NO_OF_ITERATORS 5

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
		get_tok_type(lex_toks[iter[lex]], iter);
		if (lex_toks[iter[lex]] && get_tok_redir(lex_toks, iter) == 1)
			return (free_parser(par_toks, iter, EXIT_FAILURE));
		if (lex_toks[iter[lex]] && \
		get_tok_cmd(lex_toks[iter[lex]], par_toks[iter[par]], iter) == 1)
			return (free_parser(par_toks, iter, EXIT_FAILURE));
		if (lex_toks[iter[lex]] && \
		get_special_tok(lex_toks, par_toks, iter) == EXIT_FAILURE)
			return (free_parser(par_toks, iter, EXIT_FAILURE));
	}
	return (EXIT_FAILURE);
}

static char	**interprete_env_vars(char *lex_toks[])
{
	int	i;

	i = 0;
	while (lex_toks[i])
	{
		lex_toks[i] = interprete_vars(lex_toks[i]);
		if (lex_toks[i] == NULL)
			return (NULL);
		i++;
	}
	return (lex_toks);
}

void prnt_token(t_par_tok *tok[])
{
	char *white = "\033[0;37m";
	char *red = "\033[0;31m";
	char *green = "\033[0;32m";
	char *purp = "\033[0;35m";
	char *boldred = "\033[1;31m";
	char *boldwhite = "\033[1;37m";
	for (int i = 0; tok[i]; i++)
	{
		printf("%sToken [%d]:\n%s", boldwhite, i, white);
		if (tok[i]->type != 0)
			printf("%sType: %s", purp, white);
		switch (tok[i]->type)
		{
			case 1:
				printf("subshell\n");
				break;
			case 2:
				printf("%s&&%s\n", boldwhite, white);
				break;
			case 3:
				printf("%s||%s\n", boldwhite, white);
				break;
			default:
				if (tok[i]->type != 0)
					printf("%s%s%d is unsepcified\n%s", boldred, red, tok[i]->type, white);
				break;
		}
		for (int m = 0; m < 5; m++)
			if (tok[i]->redir_type[m])
			{
				printf("%sRedirections:\n%s", purp, white);
				break;
			}
		for (int m = 0; m < 5; m++)
		{
			if (tok[i]->redir_type[m])
			{
				switch (m)
				{
					case 0:
						printf("Is Pipe:\t");
						break;
					case 1:
						printf("Is In:\t\t");
						break;
					case 2:
						printf("Is Heredoc:\t");
						break;
					case 3:
						printf("Is Out:\t\t");
						break;
					case 4:
						printf("Is Out-Append:\t");
						break;
					default:
						break;
				}
				printf("%strue\n%s", green, white);
			}
		}
		if (tok[i]->cmd)
		{
			printf("%sCommand:\n%s", purp, white);
			for (int j = 0; tok[i]->cmd && tok[i]->cmd[j]; j++)
				printf("%s\t", tok[i]->cmd[j]);
			printf("\n");
		}
		if (tok[i]->in)
		{
			printf("%sIn Redirections:\n%s", purp, white);
			for (int k = 0; tok[i]->in && tok[i]->in[k]; k++)
				printf("%s\t", tok[i]->in[k]);
			printf("\n");
		}
		if (tok[i]->out)
		{
			printf("%sOut Redirections:\n%s", purp, white);
			for (int l = 0; tok[i]->out && tok[i]->out[l]; l++)
				printf("%s\t", tok[i]->out[l]);
			printf("\n");
		}
		printf("\n");
	}
}

int	parser(char *lexer_tokens[])
{
	t_par_tok	**tokens;
	int			exit_code;

	lexer_tokens = interprete_env_vars(lexer_tokens);
	if (lexer_tokens == NULL)
		return (EXIT_FAILURE);
	set_lex_toks(lexer_tokens);
	for (size_t i = 0; lexer_tokens[i]; i++)
	{
		printf("%s\n", lexer_tokens[i]);
	}
	printf("\n");
	exit_code = get_tokens(lexer_tokens);
	if (exit_code == EXIT_FAILURE)
		return (EXIT_FAILURE);
	if (exit_code == EXIT_SYNTAX_ERROR)
	{
		printf("minishell: Syntax Error at unspecified Token\n");
		ft_free_str_array(&lexer_tokens);
		return (EXIT_SUCCESS);
	}
	tokens = get_par_toks();
	prnt_token(tokens);
	return (0);
	if (expander(tokens) == EXIT_FAILURE)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
