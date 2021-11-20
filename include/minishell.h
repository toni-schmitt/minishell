/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:29:02 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/20 12:39:36 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <dirent.h>
# include <stdbool.h>

/* TRANSPORT OF ENV_VARIABLES */
typedef struct s_env
{
	char	**envp;
	char	**env_var;
	char	*pwd;
	char	*oldpwd;
}			t_env;

/* TRANSPORT OF VARIABLES OF EXPORT */
typedef struct s_export
{
	int		i;
	int		j;
	char	*var;
}			t_export;

/* INBUILD */
int		echo(char **args);
int		export(char **argv, t_env *envv);
int		unset(char **argv, t_env *envv);
int		env(t_env *envv);
int		pwd(void);
int		cd(char **argv, t_env *envv);

/* INBUILD_UTILS */
int		export_only(t_env *envv);
t_env	*init_envv(char **envp);
char	*search_env_var(char **env_var, char *var);
void	free_envv(t_env **envv);

#endif
