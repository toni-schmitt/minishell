/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:49:07 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/28 21:36:25 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char **argv, char **envp)
{
	int		i;
	int		j;
	char	**var_split;
	char	*var;
	char	**env_var;

	env_var = NULL;
	env_var = ft_str_arr_dup(envp);
	if (env_var == NULL)
		return (1);
	if (argv[1] == NULL)
	{
		i = 0;
		while (env_var[i])
			ft_printf("declare -x %s\n", env_var[i++]); // needs to be printed in alphabetical order.... and add "" around the values like USER="tblaase"
	}
	else
	{
		j = 1;
		while (argv[j])
		{
			var_split = ft_split(argv[j], '=');
			var = ft_strdup(var_split[0]);
			ft_free_split(var_split);
			i = 0;
			while (env_var[i])
			{
				if (ft_strncmp(env_var[i], var, ft_strlen(var) == 0))
					env_var[i] = ft_strdup(argv[j++]);
				i++;
				if (env_var[i] == NULL)
				{
					env_var = ft_realloc_str_arr(env_var,
							ft_str_arr_len(env_var) + 1);
					env_var[i] = ft_strdup(argv[j++]); // testing needed!!!!!!!!
				}
			}
			j++;
		}
	}
	return (0);
}
