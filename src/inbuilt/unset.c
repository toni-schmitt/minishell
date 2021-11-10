/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 15:50:27 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/10 15:38:02 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_get_var(t_environment *environment, int i)
{
	char	**split;
	char	*var;

	split = ft_split(environment->env_var[i], '=');
	if (split == NULL)
		return (NULL);
	var = ft_strdup(split[0]);
	ft_free_str_array(&split);
	return (var);
}

static void	ft_del_var(t_environment *environment, int i)
{
	int	j;

	ft_free_str(&environment->env_var[i]);
	j = i;
	while (environment->env_var[j + 1])
	{
		environment->env_var[j] = environment->env_var[j + 1];
		j++;
		if (environment->env_var[j + 1] == NULL)
			environment->env_var[j] = NULL;
		i = ft_str_arr_len(environment->env_var);
	}
}

static int	ft_inner_loop(char **argv, t_environment *environment, int i, int k)
{
	char	*var;

	var = NULL;
	if (ft_strcmp(environment->env_var[i], argv[k]) == 0)
	{
		var = ft_get_var(environment, i);
		if (var == NULL)
			return (EXIT_FAILURE);
		if (ft_strncmp(var, argv[k], ft_strlen(var) != 0)
			|| ft_strncmp(var, argv[k], ft_strlen(argv[k]) != 0))
		{
			ft_free_str(&var);
			return (-1);
		}
		ft_del_var(environment, i);
	}
	ft_free_str(&var);
	return (EXIT_SUCCESS);
}

int	unset(char **argv, t_environment *environment)
{
	int		i;
	int		k;
	int		inner_out;

	k = 1;
	if (argv[k] == NULL)
		return (EXIT_SUCCESS);
	while (argv[k])
	{
		i = 0;
		while (environment->env_var[i])
		{
			inner_out = ft_inner_loop(argv, environment, i, k);
			if (inner_out == -1)
				break ;
			else if (inner_out == EXIT_FAILURE)
				return (EXIT_FAILURE);
			i++;
		}
		k++;
	}
	return (EXIT_SUCCESS);
}
