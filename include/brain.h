/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   brain.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 22:21:31 by tschmitt          #+#    #+#             */
/*   Updated: 2021/10/29 16:17:08 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BRAIN_H
# define BRAIN_H

# include <readline/history.h>
# include <readline/readline.h>

// BRAIN
int		lexer(char *line);
int		parser(char **tokens);
int		expander(void);
int		executor(void);

// BRAINS UTILS
void	set_envp(char *envp[]);
char	**get_envp(void);

#endif