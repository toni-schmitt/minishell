/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:49:07 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/10 16:54:15 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_only(t_environment *environment)
{
	char	*temp;
	char	**env_var_cpy;
	int		i;
	int		j;

	temp = NULL;
	env_var_cpy = ft_str_arr_dup(environment->env_var);
	i = 0;
	// printf("ORIGINAL ENV_VAR:\n");
	// while (environment->env_var[i] != NULL)
	// 	printf("%s\n", environment->env_var[i++]);
	// printf("------------------------------------\n");
	if (env_var_cpy == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (env_var_cpy[i] != NULL && env_var_cpy[i + 1] != NULL) ///////////// rewirte this sorting part so it worts it into a new 2D array
	{
		j = i + 1;
		while (env_var_cpy[j] != NULL)
		{
			if (ft_strcmp(env_var_cpy[i], env_var_cpy[j]) > 0)
			{
				temp = ft_strdup(env_var_cpy[i]);
				if (temp == NULL)
				{
					ft_free_str_array(&env_var_cpy);
					return (EXIT_FAILURE);
				}
				ft_free_str(&env_var_cpy[i]);
				env_var_cpy[i] = env_var_cpy[j];
				// if (environment->env_var[i] == NULL)
				// 	return (EXIT_FAILURE);
				// ft_free_str(&environment->env_var[j]);
				env_var_cpy[j] = temp;
				// if (environment->env_var[j] == NULL)
				// 	return (EXIT_FAILURE);
				// ft_free_str(&temp);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (env_var_cpy[i] != NULL)
	{
		if (ft_strchr(env_var_cpy[i], '=') != NULL)
		{
			if (ft_printf("declare -x ") != ft_strlen("decalre -x "))
				return (EXIT_FAILURE);
			j = 0;
			while (env_var_cpy[i][j])
			{
				if (&env_var_cpy[i][j] == ft_strchr(env_var_cpy[i], '='))
				{
					if (ft_printf("%c\"", env_var_cpy[i][j++]) != 2)
						return (EXIT_FAILURE);
				}
				else if (ft_printf("%c", env_var_cpy[i][j++]) != 1)
					return (EXIT_FAILURE);
			}
			if (ft_printf("\"\n") != 2)
				return (EXIT_FAILURE);
		}
		else if (ft_printf("declare -x %s\n", env_var_cpy[i]) != 12 + ft_strlen(env_var_cpy[i]))
		{
			printf("FAIL 74\n"); //for testing
			return (EXIT_FAILURE);
		}
		i++;
	}
	ft_free_str_array(&env_var_cpy);
	// printf("env_var has %d values\n", ft_str_arr_len(environment->env_var));
	// printf("\nORIGINAL OUTPUT OF export\n\n");

	return (EXIT_SUCCESS);
}

int	export(char **argv, t_environment *environment)
{
	int		i;
	int		j;
	char	**var_split;
	char	*var;
	bool	oldpwd_found;

	// if (environment->env_var == NULL)
	// {
	// 	perror("malloc failed");
	// 	return (EXIT_FAILURE);
	// }
	i = 0;
	oldpwd_found = false;
	while (environment->env_var[i] && argv[1] != NULL)
	{
		if (ft_strcmp(environment->env_var[i], "OLDPWD") == 0)
			oldpwd_found = true;
		i++;
	}
	if (oldpwd_found == false && argv[1] != NULL)
	{
		environment->env_var = ft_realloc_str_arr(environment->env_var, ft_str_arr_len(environment->env_var) + 1);
		environment->env_var[i] = ft_strdup("OLDPWD");
	}
	if (argv[1] == NULL)
	{
		export_only(environment); // testing needed!!!!!!!!
		// i = 0;
		// while (env_var[i])
		// 	ft_printf("declare -x %s\n", env_var[i++]); // needs to be printed in alphabetical order.... and add "" around the values like USER="tblaase"
	}
	else
	{
		j = 1;
		while (argv[j])
		{
			var_split = ft_split(argv[j], '=');
			var = ft_strdup(var_split[0]);
			ft_free_str_array(&var_split);
			i = 0;
			while (environment->env_var[i])
			{
				if (ft_strcmp(environment->env_var[i], var) == 0)
				{
					environment->env_var[i] = ft_strdup(argv[j++]);
					ft_free_str(&var);
					break ;
				}
				i++;
				if (environment->env_var[i] == NULL)
				{
					environment->env_var = ft_realloc_str_arr(environment->env_var, ft_str_arr_len(environment->env_var) + 1);
					environment->env_var[i] = ft_strdup(argv[j++]);
					ft_free_str(&var);
					break ;
				}
			}
		}
	}
	return (EXIT_SUCCESS);
}
