/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:12:12 by tschmitt          #+#    #+#             */
/*   Updated: 2021/10/29 16:17:54 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**_get_envp(char *envp[])
{
	static char	**static_envp;

	if (envp != NULL)
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
