/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interprete_env_var.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/26 23:13:27 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/16 19:15:41 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "brain.h"
#include "minishell.h"
#include "parser_utils.h"
#include "env_var_utils.h"

static char	*get_env_variable(char *lex_tok, char *var)
{
	char	*env_var;
	char	*var_value;
	int		i;
	int		j;

	var_value = get_env_var_value(get_envv(), var);
	if (var_value == NULL)
		return (NULL);
	env_var = ft_calloc(ft_strlen(lex_tok) + ft_strlen(var_value) + 1, 1);
	if (env_var == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (lex_tok[i] && lex_tok[i] != '$')
		env_var[j++] = lex_tok[i++];
	env_var = ft_append(&env_var, var_value);
	if (env_var == NULL)
		return (var_value);
	while ((lex_tok[i] == '$') || (lex_tok[i] && ft_isalpha(lex_tok[i])))
		i++;
	env_var = ft_append(&env_var, lex_tok + i);
	if (env_var == NULL)
		return (NULL);
	free(var_value);
	return (env_var);
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
	if (lex_tok[0] != '\'' && ft_strlen(lex_tok) > 1 \
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
		fprintf(stderr, "l:%s\nv:%s\n", lex_tok, var);
		interpreted_token = get_env_variable(lex_tok, var);
		free(var);
		free(lex_tok);
		return (interpreted_token);
	}
	if (!ft_strchr(lex_tok, '\'') && !ft_strchr(lex_tok, '\"') \
	&& ft_strcmp(lex_tok, "*\0") == 0)
	{
		free(lex_tok);
		return (get_dir_items());
	}
	return (interpreted_token);
}
