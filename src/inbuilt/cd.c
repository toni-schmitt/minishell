/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:17 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/19 19:30:00 by tblaase          ###   ########.fr       */
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
	// printf("HOME FOUND:%s\n", path);
	return (path);
}

static void	ft_update_env_var(t_environment *environment, char *var,
char *value)
{
	int	i;

	i = 0;
	while (environment->env_var && environment->env_var[i])
	{
		if (ft_strcmp(environment->env_var[i], var) == 0
			&& (environment->env_var[i][ft_strlen(var)] == '='
			|| environment->env_var[i][ft_strlen(var)] == '\0'))
		{
			ft_free_str(&environment->env_var[i]);
			environment->env_var[i] = ft_strstrjoin(var, value, "=");
			return ;
		}
		i++;
	}
	if (environment->env_var && environment->env_var[i] == NULL)
	{
		environment->env_var = ft_realloc_str_arr(environment->env_var,
				ft_str_arr_len(environment->env_var) + 1);
		environment->env_var[i] = ft_strstrjoin(var, value, "=");
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

static int	ft_cd_home(t_environment *environment, char **home_path)
{
	char	*cwd;

	cwd = NULL;
	if (chdir(*home_path) != 0)
		return (ft_exit_cd(home_path, &cwd, 1));
	cwd = getcwd(cwd, 0);
	ft_update_env_var(environment, ft_strdup("PWD"), cwd);
	return (ft_exit_cd(home_path, &cwd, EXIT_SUCCESS));
}

// check why it prints error when running ./minishell

int	cd(char **argv, t_environment *environment)
{
	char	*cwd;
	char	*home_path;
	DIR		*directory;

	cwd = NULL;
	home_path = NULL;
	if (argv == NULL)
		return (EXIT_FAILURE);
	cwd = getcwd(cwd, 0);
	ft_update_env_var(environment, ft_strdup("OLDPWD"), cwd);
	ft_exit_cd(&home_path, &cwd, 0);
	// home_path = find_home(environment->env_var);
	// printf("path to home is:%s\n", home);
	if (argv[1] == NULL)
	{
		home_path = find_home(environment->env_var);
		if (home_path == NULL)
		{
			//fix exit of the programm right here
		}
		return (ft_cd_home(environment, &home_path));
	}
	directory = opendir(argv[1]);
	if (directory == NULL)
		return (ft_exit_cd(&home_path, &cwd, 1));
	else if (closedir(directory) != 0)
		return (ft_exit_cd(&home_path, &cwd, 1));
	else if (chdir(argv[1]) != 0)
		return (ft_exit_cd(&home_path, &cwd, 1));
	cwd = getcwd(cwd, 0);
	ft_update_env_var(environment, ft_strdup("PWD"), cwd);
	return (ft_exit_cd(&home_path, &cwd, 0));
}
