/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:50:27 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/02 17:42:54 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**unset(char **argv, char **env_var)
{
	int		i;
	int		j;
	int		k;
	char	**split;
	char	*var;

	k = 1;
	if (argv[k] == NULL)
		return (NULL);
	while (argv[k])
	{
		i = 0;
		while (env_var[i])
		{
			if (ft_strcmp(env_var[i], argv[k]) == 0)
			{
				split = ft_split(env_var[i], '=');
				var = ft_strdup(split[0]);
				ft_free_str_array(split);
				if (ft_strncmp(var, argv[k], ft_strlen(var) != 0)
					|| ft_strncmp(var, argv[k], ft_strlen(argv[k]) != 0))
					break ;
				ft_free_str(&env_var[i]);
				j = i;
				while (env_var[j + 1])
				{
					// ft_memmove(env_var[j], env_var[j + 1], ft_strlen(env_var[j]));
					env_var[j] = env_var[j + 1];
					j++;
					if (env_var[j + 1] == NULL)
						env_var[j] = NULL;
					i = ft_str_arr_len(env_var);
				}
			}
			i++;
			// if (argv[k + 1] == NULL)
			// 	break;
		}
		k++;
	}
	return (env_var);
}
