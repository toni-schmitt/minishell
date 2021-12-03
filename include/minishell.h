/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/19 18:29:02 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/03 16:20:36 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft.h"
# include <errno.h>
# include <dirent.h>
# include <stdbool.h>
# include "brain.h"
# include "parser_utils.h"
# include "lexer_utils.h"

# define EXIT_SYNTAX_ERROR 258

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
int		env(t_env *envv, char **argv);
int		pwd(void);
int		cd(char **argv, t_env *envv);

/* INBUILD_UTILS */
int		export_only(t_env *envv);
int		export_input_error(char **argv);
int		export_special(t_env *envv, t_export *exp);
int		export_wd(t_env *envv, t_export *exp, char **argv);
t_env	*init_envv(char **envp);
int		reinit_env_var(t_env *envv, char **argv);
char	*get_env_var_value(char **env_var, char *var);
void	free_envv(t_env **envv);

#endif
