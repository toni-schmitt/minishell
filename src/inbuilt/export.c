/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 17:49:07 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/27 21:18:23 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export(char **argv, char **envp)
{
	int		i;
	char	**var_split;
	char	*var;
	char	**env_var;

	env_var = NULL;
	// env_var = ft_str_arr_dup(envp);
	if (env_var == NULL)
		return (1);
	(void)envp;
	i = 0;
	while (argv[1] != NULL)
	{
		var_split = ft_split(argv[1], '=');
		var = ft_strdup(var_split[0]);
		ft_free_split(var_split);
		if (argv[1] != NULL && ft_strncmp(env_var[i], var, ft_strlen(var)))
			env_var[i] = ft_strdup(argv[1]);
	}
	return (0);
}
