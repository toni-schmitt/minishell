/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:33:39 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/13 15:56:57 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	echo(char **args)
{
	bool	print_newline;

	print_newline = true;
	if (ft_strncmp(*args, "echo", ft_strlen(*args)) != 0)
		return (EXIT_FAILURE);
	args++;
	if (*args && ft_strncmp(*args, "-n", ft_strlen("-n") + 1) == 0)
	{
		print_newline = false;
		args++;
	}
	while (*args)
	{
		if (printf("%s", *args) != ft_strlen(*args))
			return (EXIT_FAILURE);
		if (ft_strlen(*args) != 0 && *(args + 1) != NULL)
			if (printf(" ") != ft_strlen(" "))
				return (EXIT_FAILURE);
		args++;
	}
	if (print_newline)
		if (printf("\n") != ft_strlen("\n"))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
