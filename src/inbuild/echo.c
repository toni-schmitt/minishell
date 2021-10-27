/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 21:33:39 by tschmitt          #+#    #+#             */
/*   Updated: 2021/10/27 21:54:44 by tschmitt         ###   ########.fr       */
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
	int		printed_chars;

	prnt_nl = prnt_newline(arg);
	if (!prnt_nl)
		arg += 2;
	printed_chars = ft_printf("%s", arg);
	if (prnt_nl)
		ft_printf("\n");
	if (printed_chars != ft_strlen(arg))
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
