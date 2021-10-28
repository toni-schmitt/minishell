/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 14:12:17 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/28 18:04:21 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	cd(char **argv)
{
	if (argv[1] == NULL)
		return (0);
	else if (opendir(argv[1]) == NULL && errno != 0)
	{
		perror("Error");
		return (1);
	}
	if (chdir(argv[1]) != 0)
	{
		perror("Error");
		return (1);
	}
	return (0);
}
