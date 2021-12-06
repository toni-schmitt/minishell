/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:29:18 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/26 13:40:44 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
searches for var inside of env_var, allocates its value after the '='
value: allocated value or NULL
*/
char	*get_env_var_value(char **env_var, char *var)
{
	int		i;
	char	*value;

	value = NULL;
	i = 0;
	while (env_var && env_var[i] != NULL)
	{
		if (ft_strcmp(var, env_var[i]) == -61)
		{
			value = ft_strdup(ft_strchr(env_var[i], '=') + 1);
			break ;
		}
		i++;
	}
	if (value == NULL && (ft_strcmp(var, "PWD") == 0
			|| ft_strcmp(var, "OLDPWD") == 0))
		value = ft_calloc(1, sizeof(char));
	return (value);
}

/*
will create envv by duplicating envp into t_env *envv
everything except envp inside t_env is allocated
*/
t_env	*init_envv(char **envp)
{
	t_env	*envv;

	envv = ft_calloc(1, sizeof(t_env));
	if (envv != NULL && envp != NULL && *envp != NULL)
	{
		envv->envp = envp;
		envv->env_var = ft_str_arr_dup(envp);
		envv->pwd = get_env_var_value(envv->env_var, "PWD");
		envv->oldpwd = get_env_var_value(envv->env_var, "OLDPWD");
		if (envv->env_var != NULL && envv->pwd != NULL && envv->oldpwd != NULL)
			return (envv);
	}
	return (NULL);
}

/*
will free all allocated values of t_env and set them to NULL
*/
void	free_envv(t_env **envv)
{
	(*envv)->envp = NULL;
	ft_free_str_array(&(*envv)->env_var);
	ft_free_str(&(*envv)->pwd);
	ft_free_str(&(*envv)->oldpwd);
	free(*envv);
	*envv = NULL;
}

int	reinit_env_var(t_env *envv, char **argv)
{
	if (*envv->env_var == NULL)
	{
		envv->env_var = ft_realloc_str_arr(envv->env_var, 2);
		if (envv->env_var == NULL)
			return (EXIT_FAILURE);
		envv->env_var[0] = ft_strdup(argv[1]);
		if (envv->env_var[0] == NULL)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
