/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:49:07 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/16 21:56:41 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_export_found(t_environment *env, t_export *exp, char **argv)
{
	if (ft_strcmp(env->env_var[exp->i], exp->var) == 0)
	{
		ft_free_str(&env->env_var[exp->i]);
		env->env_var[exp->i] = ft_strdup(argv[exp->j++]);
		ft_free_str(&exp->var);
		if (env->env_var[exp->i] == NULL)
			return (EXIT_FAILURE);
		return (2);
	}
	return (EXIT_SUCCESS);
}

static int	ft_export_new(t_environment *env, t_export *exp, char **argv)
{
	if (env->env_var[exp->i] == NULL)
	{
		env->env_var = ft_realloc_str_arr
			(env->env_var, ft_str_arr_len(env->env_var) + 1);
		env->env_var[exp->i] = ft_strdup(argv[exp->j++]);
		ft_free_str(&exp->var);
		if (env->env_var == NULL || env->env_var[exp->i] == NULL)
			return (EXIT_FAILURE);
		return (2);
	}
	return (EXIT_SUCCESS);
}

static void	ft_split_var(t_export *exp, char **argv)
{
	char	**var_split;

	var_split = ft_split(argv[exp->j], '=');
	if (var_split == NULL)
		exp->var = NULL;
	else
	{
		exp->var = ft_strdup(var_split[0]);
		ft_free_str_array(&var_split);
	}
}

static int	ft_export_loop(t_environment *env, t_export *exp, char **argv)
{
	int		check;

	while (argv[exp->j])
	{
		ft_split_var(exp, argv);
		if (exp->var == NULL)
			return (EXIT_FAILURE);
		exp->i = 0;
		while (env->env_var[exp->i])
		{
			check = ft_export_found(env, exp, argv);
			if (check == 2)
				break ;
			else if (check == EXIT_FAILURE)
				return (EXIT_FAILURE);
			exp->i++;
			check = ft_export_new(env, exp, argv);
			if (check == 2)
				break ;
			else if (check == EXIT_FAILURE)
				return (EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}

int	export(char **argv, t_environment *env)
{
	t_export	*exp;

	if (env == NULL || env->env_var == NULL)
		return (EXIT_FAILURE);
	if (argv[1] == NULL)
		export_only(env);
	else
	{
		exp = ft_calloc(1, sizeof(t_export));
		if (exp == NULL)
			return (EXIT_FAILURE);
		exp->j = 1;
		if (ft_export_loop(env, exp, argv) == EXIT_FAILURE)
		{
			free(exp);
			exp = NULL;
			return (EXIT_FAILURE);
		}
		free(exp);
		exp = NULL;
	}
	return (EXIT_SUCCESS);
}
