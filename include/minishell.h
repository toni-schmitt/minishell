/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:29:02 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/09 21:20:23 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <dirent.h>
# include <stdbool.h>

typedef struct s_environment
{
	char	**envp;
	char	**env_var;
}			t_environment;

/* INBUILD */
int		echo(char **args);
int		export(char **argv, t_environment *environment);
char	**unset(char **argv, char **env_var);
int		env(t_environment *environment);
int		pwd(void);
int		cd(char **argv, t_environment *environment);

#endif
