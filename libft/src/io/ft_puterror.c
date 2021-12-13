/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puterror.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/22 20:42:48 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/13 13:39:11 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_puterror(char *message)
{
	ft_printf("%s\n", message);
	exit(EXIT_FAILURE); // why exit and return?????
	return (EXIT_FAILURE);
}
