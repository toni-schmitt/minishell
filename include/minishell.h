/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:29:02 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/15 18:23:30 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <dirent.h>
# include <stdbool.h>
# include <fcntl.h>
# include "error_utils.h"

# define EXIT_SYNTAX_ERROR 258
# define EXIT_CMD_NOT_FOUND 127
# define EXIT_CTRL_D 130

/* INBUILD */
int		echo(char **args);
int		export(char **argv);
int		unset(char **argv);
int		env(char **argv);
int		pwd(void);
int		cd(char **argv);
int		exit_inbuilt(char *args[]);

void	handle_cmd_signals(void);
void	handle_global_signals(void);

#endif
