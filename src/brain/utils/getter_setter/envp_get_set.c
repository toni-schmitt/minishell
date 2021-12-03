/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_get_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:12:12 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/02 21:20:35 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**_get_envp(char *envp[])
{
	static char	**static_envp = NULL;

	if (envp == NULL)
		return (static_envp);
	static_envp = envp;
	return (static_envp);
}

void	set_envp(char *envp[])
{
	_get_envp(envp);
}

char	**get_envp(void)
{
	return (_get_envp(NULL));
}
