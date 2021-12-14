/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:48:30 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/14 16:51:19 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "env_var_utils.h"

int	env(char **argv)
{
	int		i;
	t_env	*envv;

	envv = get_envv();
	if (envv == NULL || envv->env_var == NULL)
		return (EXIT_FAILURE);
	if (argv != NULL && argv[1] != NULL)
	{
		if (access(argv[1], F_OK) == 0)
		{
			ft_fprintf(STDERR_FILENO, "env: %s: Premission denied\n", argv[1]);
			return (126);
		}
		ft_fprintf(STDERR_FILENO, "env: %s: No such file or directory\n", argv[1]);
		return (127);
	}
	i = 0;
	while (envv->env_var && envv->env_var[i] != NULL)
	{
		if (ft_printf("%s\n", envv->env_var[i++]) == 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
