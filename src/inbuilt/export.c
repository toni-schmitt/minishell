/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:49:07 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/09 22:34:29 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	export_only(t_environment *environment)
{
	char	*temp;
	char	*position;
	int		arr_len;
	int		i;
	int		j;

	// printf("\nNOW SORTED\n\n");
	i = 0;
	temp = NULL;
	arr_len = ft_str_arr_len(environment->env_var);
	i = 0;
	while (i < arr_len) ///////////// rewirte this sorting part so it worts it into a new 2D array
	{
		j = i + 1;
		while (j < arr_len)
		{
			if (ft_strcmp(environment->env_var[i], environment->env_var[j]) > 0)
			{
				temp = ft_strdup(environment->env_var[i]);
				if (temp == NULL)
					return (EXIT_FAILURE);
				ft_free_str(&environment->env_var[i]);
				environment->env_var[i] = environment->env_var[j];
				// if (environment->env_var[i] == NULL)
				// 	return (EXIT_FAILURE);
				// ft_free_str(&environment->env_var[j]);
				environment->env_var[j] = temp;
				// if (environment->env_var[j] == NULL)
				// 	return (EXIT_FAILURE);
				// ft_free_str(&temp);
			}
			j++;
		}
		i++;
	}
	i = 0;
	while (i < arr_len)
	{
		position = ft_strchr(environment->env_var[i], '=');
		if (position != NULL)
		{
			if (ft_printf("declare -x ") != ft_strlen("decalre -x ")) // is this protection needed??????
				return (EXIT_FAILURE);
			while (*environment->env_var[i])
			{
				if (*environment->env_var[i] == *position)
				{
					ft_printf("%c\"", *environment->env_var[i]++);
				}
				else
					ft_printf("%c", *environment->env_var[i]++);
			}
			ft_printf("\"\n");
		}
		else
			ft_printf("declare -x %s\n", environment->env_var[i]);
		i++;
	}
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
			ft_free_str_array(var_split);
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
