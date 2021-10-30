/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 22:21:31 by tschmitt          #+#    #+#             */
/*   Updated: 2021/10/30 22:35:42 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_H
# define BRAIN_H

# include <readline/history.h>
# include <readline/readline.h>

// BRAIN
int		lexer(char *line);
int		parser(char *tokens[]);
int		expander(void);
int		executor(void);

// BRAIN UTILS

// LEXER UTILS
char	get_next_special(char *token);
size_t	get_new_tokens_size(char **tokens);
size_t	get_next_token_size(char *token, char next_special);
bool	token_is_unadjusted(char *token);

// ENVP UTILS
void	set_envp(char *envp[]);
char	**get_envp(void);

#endif