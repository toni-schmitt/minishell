/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/22 16:03:18 by tschmitt          #+#    #+#             */
/*   Updated: 2021/12/14 16:44:03 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putptr_fd(int fd, void *ptr)
{
	return (ft_putstr_fd(fd, "0x") + \
	ft_putlhex_fd(fd, (unsigned long long)ptr));
}
