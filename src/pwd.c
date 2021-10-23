/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 16:22:09 by tblaase           #+#    #+#             */
/*   Updated: 2021/10/23 16:52:08 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"
// #include <stdio.h>
// #include <unistd.h>
// #include <stdlib.h>

void	ft_pwd(char *cwd)
{
	// char	*cwd;

	// cwd = NULL;
	getcwd(cwd, 10);
	if (cwd == NULL)
		perror("Error with getcwd");
	printf("%s", cwd);
}
