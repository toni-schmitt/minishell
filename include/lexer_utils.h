/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/31 01:18:48 by toni              #+#    #+#             */
/*   Updated: 2021/10/31 01:21:43 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_UTILS_H
# define LEXER_UTILS_H

// LEXER UTILS
char	get_next_special(char *token);
size_t	get_new_tokens_size(char **tokens);
size_t	get_next_token_size(char *token, char next_special);
bool	token_is_unadjusted(char *token);

#endif