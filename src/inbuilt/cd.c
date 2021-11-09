/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:17 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/09 18:11:04 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_home(char **envp, char **env_var)
{
	int		i;
	char	*path;

	i = 0;
	path = NULL;
	while (env_var && env_var[i] && ft_strcmp(env_var[i], "HOME=") != 0)
		i++;
	if (!env_var || ft_strlen(env_var[i]) <= 5) // env_var[i] == NULL not needed because strlen <= 6 will protect for that case as well
	{
		i = 0;
		while (envp[i])
		{
			if (ft_strcmp(envp[i], "HOME=") == 0)
			{
				path = ft_strdup(ft_strchr(envp[i], '=') + 1);
				return (path);
			}
			i++;
		}
	}
	else
		path = ft_strdup(ft_strchr(env_var[i], '=') + 1);
	return (path);
}

static void	ft_update_env_var(t_environment *environment, char *var, char *value)
{
	int	i;

	i = 0;
	while (environment->env_var && environment->env_var[i])
	{
		if (ft_strcmp(environment->env_var[i], var) == 0 && (environment->env_var[i][ft_strlen(var)] == '=' || environment->env_var[i][ft_strlen(var)] == '\0'))
		{
			ft_free_str(&environment->env_var[i]);
			environment->env_var[i] = ft_strstrjoin(var, value, "=");
			return ;
		}
		i++;
	}
	if (environment->env_var && environment->env_var[i] == NULL)
	{
		environment->env_var = ft_realloc_str_arr(environment->env_var, ft_str_arr_len(environment->env_var) + 1);
		environment->env_var[i] = ft_strstrjoin(var, value, "=");
	}
}

static void	ft_free_cd_work(char **home, char **cwd)
{
	ft_free_str(cwd);
	ft_free_str(home);
}

int	cd(char **argv, t_environment *environment)
{
	char	*home;
	char	*cwd;
	DIR		*directory;

	cwd = NULL;
	home = NULL;
	cwd = getcwd(cwd, 0);
	ft_update_env_var(environment, ft_strdup("OLDPWD"), cwd);
	ft_free_cd_work(&home, &cwd);
	home = find_home(environment->envp, environment->env_var);
// printf("homefolder found:%s\n", home);
// (void)argv;
	if (argv[1] == NULL)
	{
		if (chdir(home) != 0)
		{
			perror("Error");
			ft_free_cd_work(&home, &cwd);
			return (EXIT_FAILURE);
		}
		cwd = getcwd(cwd, 0);
		ft_update_env_var(environment, ft_strdup("PWD"), cwd);
		ft_free_cd_work(&home, &cwd);
		return (EXIT_SUCCESS);
	}
	directory = opendir(argv[1]);
	if (directory == NULL || access(argv[1], F_OK) !=0)
	{
		perror("Error");
		ft_free_cd_work(&home, &cwd);
		return (EXIT_FAILURE);
	}
	else if (closedir(directory) != 0)
	{
		perror("Error");
		ft_free_cd_work(&home, &cwd);
		return (EXIT_FAILURE);
	}
	else if (chdir(argv[1]) != 0)
	{
		perror("Error");
		ft_free_cd_work(&home, &cwd);
		return (EXIT_FAILURE);
	}
	cwd = getcwd(cwd, 0);
	ft_update_env_var(environment, ft_strdup("PWD"), cwd);
	ft_free_cd_work(&home, &cwd);
	return (EXIT_SUCCESS);
}
