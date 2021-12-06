/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 11:29:18 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/06 18:32:39 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	get_env_var_value_utils(t_env *envv, char *var, char **value)
{
	if (ft_strlen(*value) == 0 && ft_strcmp(var, "PWD") == 0)
		*value = ft_strdup(envv->pwd);
	else if (ft_strlen(*value) == 0 && ft_strcmp(var, "OLDPWD") == 0)
	{
		if (ft_strlen(envv->oldpwd) == 0)
			*value = ft_calloc(1, sizeof (char));
		else
			*value = ft_strdup(envv->oldpwd);
	}
}

/*
 * @brief  get value of a specific variable from env_var
 * @note  similar to getenv but uses our env_var instead of envp
 * @param  *envv: the t_env struct
 * @param  *var: the variable you are searching for without the '='
 * @retval the maloced value that was found, empty string if not found
 * * , NULL if error occured
*/
char	*get_env_var_value(t_env *envv, char *var)
{
	int		i;
	char	*value;

	value = NULL;
	i = 0;
	while (envv && envv->env_var && envv->env_var[i] != NULL)
	{
		if (ft_strcmp(var, envv->env_var[i]) == -61)
		{
			value = ft_strchr(envv->env_var[i++], '=') + 1;
			if (ft_strlen(value) == 0)
				value = ft_calloc(1, sizeof (char));
			else
				value = ft_strdup(value);
			break ;
		}
		else if (ft_strcmp(var, envv->env_var[i++]) == 0)
		{
			value = ft_calloc(1, sizeof (char));
			break ;
		}
	}
	get_env_var_value_utils(envv, var, &value);
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
		envv->pwd = get_env_var_value(envv, "PWD");
		envv->oldpwd = get_env_var_value(envv, "OLDPWD");
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

/**
 * @brief  will reinitiate env_var if all values got unset
 * @note
 * @param  *envv: the t_env struct
 * @param  **argv: the first variable that gets exported into the empty env_var
 * @retval either EXIT_SUCCESS or EXIT_FAILURE
 */
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
