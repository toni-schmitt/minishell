/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putstr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/08 20:17:59 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/14 16:49:54 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "libft.h"

int	ft_putstr_fd(int fd, char *s)
{
	if (s == NULL)
		return (0);
	return (write(fd, s, ft_strlen((const char *)s)));
}
