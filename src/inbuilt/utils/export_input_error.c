/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_input_error.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 14:00:54 by tblaase           #+#    #+#             */
/*   Updated: 2021/11/23 16:31:06 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
checks the input of export for errors and prints the corresponding message
*/
int	export_input_error(char **argv)
{
	char	**split;
	char	*var;
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (argv && argv[i])
	{
		split = ft_split(argv[i], '=');
		var = ft_strdup(split[0]);
		ft_free_str_array(&split);
		if (var == NULL)
			return (EXIT_FAILURE);
		while (var[j] != '\0')
		{
			if (ft_isalnum(var[j]) == 0 && var[j] != '_')
			{
				ft_printf("export: `%s': not a valid identifier\n", argv[i]);
				ft_free_str(&var);
				return (EXIT_FAILURE);
			}
			j++;
		}
		i++;
	}
	return (EXIT_SUCCESS);
}
