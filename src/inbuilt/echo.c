/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:33:39 by tschmitt          #+#    #+#             */
/*   Updated: 2021/10/28 16:08:40 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	prnt_newline(char *arg)
{
	if (arg[0] == '-' && arg[1] == 'n')
		return (false);
	return (true);
}

int	echo(char *arg)
{
	bool	prnt_nl;

	prnt_nl = prnt_newline(arg);
	if (!prnt_nl)
		arg += 2;
	if (ft_printf("%s", arg) != ft_strlen(arg))
		return (EXIT_FAILURE);
	if (prnt_nl)
		if (ft_printf("\n") != ft_strlen("\n"))
			return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
