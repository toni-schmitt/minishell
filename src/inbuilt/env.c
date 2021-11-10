/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 13:48:30 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/10 14:51:31 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	env(t_environment *environment)
{
	int	i;

	if (environment == NULL || environment->env_var == NULL)
		return (EXIT_FAILURE);
	i = 0;
	while (environment->env_var && environment->env_var[i] != NULL)
	{
		if (ft_printf("%s\n", environment->env_var[i++]) == 0)
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
