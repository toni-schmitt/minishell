/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:17 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/26 14:35:24 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_del_last(char *s)
{
	char	*del;

	del = ft_strrchr(s, '/');
}

int	cd(char **argv)
{
	char	*cwd;

	cwd = NULL;
	cwd = getcwd(cwd, 0);
	if (ft_strstr(argv[1], ".."))
	{
		ft_del_last(cwd);
	}
	return (0);
}
