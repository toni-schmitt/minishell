/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:17 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/26 21:58:24 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(int argc, char **argv)
{
	char	*cwd;

	if (argv[1] == NULL)
		return (0);
	else if (opendir(argv[1]) == NULL && errno != 0)
	{
		perror("Error");
		return (1);
	}
	chdir(argv[1]);
	return (0);
}
