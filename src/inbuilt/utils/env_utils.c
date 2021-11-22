/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:29:18 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/22 18:39:34 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* searches for var inside of env_var, allocates its value after the '='
value: allocated value or NULL */
char	*get_env_var_value(char **env_var, char *var)
{
	int		i;
	char	*value;

	value = NULL;
	i = 0;
	while (env_var && env_var[i] != NULL)
	{
		if (ft_strcmp(var, env_var[i]) == -61
			|| ft_strcmp(var, env_var[i]) == 0)
		{
			value = ft_strdup(ft_strchr(env_var[i], '=') + 1);
			break ;
		}
		i++;
	}
	return (value);
}

/* will create envv */
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

/* will free all allocated values of t_env and set them to NULL */
void	free_envv(t_env **envv)
{
	(*envv)->envp = NULL;
	ft_free_str_array(&(*envv)->env_var);
	ft_free_str(&(*envv)->pwd);
	ft_free_str(&(*envv)->oldpwd);
	free(*envv);
	*envv = NULL;
}
