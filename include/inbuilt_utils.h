/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inbuilt_utils.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/06 17:51:14 by toni              #+#    #+#             */
/*   Updated: 2021/12/06 19:34:52 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INBUILT_UTILS_H
# define INBUILT_UTILS_H

# include "env_var_utils.h"

/* TRANSPORT OF VARIABLES OF EXPORT */
typedef struct s_export
{
	int		i;
	int		j;
	char	*var;
}			t_export;

/* INBUILD_UTILS */
int		export_only(t_env *envv);
int		export_input_error(char **argv);
int		export_special(t_env *envv, t_export *exp);
int		export_wd(t_env *envv, t_export *exp, char **argv);

#endif