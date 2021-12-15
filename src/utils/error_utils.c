/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tschmitt <tschmitt@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 20:21:38 by toni              #+#    #+#             */
/*   Updated: 2021/12/15 18:45:06 by tschmitt         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "error_utils.h"

static int	_get_err_code(int err_code, bool set_err_code)
{
	static int	static_err_code = 0;

	if (set_err_code)
		static_err_code = err_code;
	return (static_err_code);
}

void	set_err_code(int err_code)
{
	static bool	last_cmd_ctrlc = false;

	if (last_cmd_ctrlc)
	{
		last_cmd_ctrlc = false;
		return ;
	}
	if (err_code == 130)
		last_cmd_ctrlc = true;
	_get_err_code(err_code, true);
}

int	get_err_code(void)
{
	return (_get_err_code(0, false));
}
