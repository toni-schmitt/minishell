/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/08/15 17:34:49 by tschmitt          #+#    #+#             */
/*   Updated: 2021/11/02 16:25:23 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
frees the given string and sets it to NULL
*/
void	ft_free_str(char **str)
{
	free(*str);
	*str = NULL;
}
