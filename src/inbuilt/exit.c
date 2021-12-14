/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/11 13:22:09 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/14 17:01:20 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	is_valid_exit_arg(char *args[])
{
	int	i;
	int	j;

	i = 0;
	while (args && args[i])
	{
		j = 0;
		while (args[i][j])
		{
			if (!ft_isdigit(args[i][j]))
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

int	exit_inbuilt(char *args[])
{
	int	exit_code;

	if (ft_strncmp(*args, "exit", ft_strlen(*args)) != 0)
		return (EXIT_FAILURE);
	args++;
	if (*args)
		exit_code = ft_atoi(*args);
	if (!is_valid_exit_arg(args))
	{
		ft_fprintf(STDERR_FILENO, "exit: not a valid argument\n");
		exit_code = 255;
	}
	if (*(++args))
	{
		ft_fprintf(STDERR_FILENO, "exit: too many arguments\n");
		printf("exit\n");
		return (EXIT_FAILURE);
	}
	printf("exit\n");
	exit(exit_code);
	return (exit_code);
}
