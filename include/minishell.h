/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:29:02 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/16 19:25:10 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <dirent.h>
# include <stdbool.h>

/* TRANSPORT OF ENV_VARIABLES */
typedef struct s_environment
{
	char	**envp;
	char	**env_var;
}			t_environment;

/* TRANSPORT OF VARIABLES OF EXPORT */
typedef struct s_export
{
	int		i;
	int		j;
	char	*var;
}			t_export;

/* INBUILD */
int	echo(char **args);
int	export(char **argv, t_environment *environment);
int	unset(char **argv, t_environment *environment);
int	env(t_environment *environment);
int	pwd(void);
int	cd(char **argv, t_environment *environment);

/* INBUILD_UTILS */
int	export_only(t_environment *environment);

#endif
