/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_get_set.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 16:12:12 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/07 19:25:42 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**_get_envp(char *envp[], bool reset)
{
	static char	**static_envp = NULL;

	if (envp == NULL && !reset)
		return (static_envp);
	if (reset)
	{
		static_envp = NULL;
		return (NULL);
	}
	static_envp = envp;
	return (static_envp);
}

void	set_envp(char *envp[])
{
	_get_envp(envp, false);
}

char	**get_envp(void)
{
	return (_get_envp(NULL, false));
}

void	reset_envp(void)
{
	_get_envp(NULL, true);
}
