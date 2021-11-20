/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:17 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/20 12:16:45 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_home(char **env_var)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (env_var && env_var[i] && ft_strcmp(env_var[i], "HOME=") != 0)
		i++;
	if (env_var[i] == NULL || ft_strlen(env_var[i]) <= 5)
		ft_printf("cd: HOME not set\n");
	else
		path = ft_strdup(ft_strchr(env_var[i], '=') + 1);
	return (path);
}

static void	ft_update_env_var(t_env *envv, char *var,
char *value)
{
	int	i;

	i = 0;
	while (envv->env_var && envv->env_var[i])
	{
		if (ft_strcmp(envv->env_var[i], var) == 0
			&& (envv->env_var[i][ft_strlen(var)] == '='
			|| envv->env_var[i][ft_strlen(var)] == '\0'))
		{
			ft_free_str(&envv->env_var[i]);
			envv->env_var[i] = ft_strstrjoin(var, value, "=");
			return ;
		}
		i++;
	}
	if (envv->env_var && envv->env_var[i] == NULL)
	{
		envv->env_var = ft_realloc_str_arr(envv->env_var,
				ft_str_arr_len(envv->env_var) + 1);
		envv->env_var[i] = ft_strstrjoin(var, value, "=");
	}
}

static int	ft_exit_cd(char **home, char **cwd, int exit_status)
{
	ft_free_str(cwd);
	ft_free_str(home);
	if (exit_status == EXIT_SUCCESS)
		return (EXIT_SUCCESS);
	else
	{
		perror("Error");
		return (EXIT_FAILURE);
	}
}

static int	ft_cd_home(t_env *envv, char **home_path, char **cwd)
{
	if (chdir(*home_path) != 0)
		return (ft_exit_cd(home_path, cwd, 1));
	ft_update_env_var(envv, ft_strdup("OLDPWD"), *cwd);
	ft_free_str(cwd);
	*cwd = getcwd(*cwd, 0);
	ft_update_env_var(envv, ft_strdup("PWD"), *cwd);
	return (ft_exit_cd(home_path, cwd, EXIT_SUCCESS));
}

// check why it prints error when running ./minishell

int	cd(char **argv, t_env *envv)
{
	char	*cwd;
	char	*home_path;
	DIR		*directory;

	cwd = NULL;
	home_path = NULL;
	if (argv == NULL)
		return (EXIT_FAILURE);
	if (argv[1] == NULL)
	{
		home_path = find_home(envv->env_var);
		if (home_path == NULL)
			return (EXIT_FAILURE);
	}
	cwd = getcwd(cwd, 0);
	if (argv[1] == NULL)
		return (ft_cd_home(envv, &home_path, &cwd));
	directory = opendir(argv[1]);
	if (directory == NULL)
		return (ft_exit_cd(&home_path, &cwd, EXIT_FAILURE));
	else if (closedir(directory) != 0)
		return (ft_exit_cd(&home_path, &cwd, EXIT_FAILURE));
	else if (chdir(argv[1]) != 0)
		return (ft_exit_cd(&home_path, &cwd, EXIT_FAILURE));
	ft_update_env_var(envv, ft_strdup("OLDPWD"), cwd);
	ft_free_str(&cwd);
	cwd = getcwd(cwd, 0);
	ft_update_env_var(envv, ft_strdup("PWD"), cwd);
	return (ft_exit_cd(&home_path, &cwd, 0));
}
