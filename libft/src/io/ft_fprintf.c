/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fprintf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:36:48 by toni              #+#    #+#             */
/*   Updated: 2021/12/14 16:49:21 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_handle(char c, va_list args, int fd)
{
	if (c == 'i' || c == 'd')
		return (ft_putnbr_fd(fd, va_arg(args, int)));
	if (c == 's')
		return (ft_putstr_fd(fd, va_arg(args, char *)));
	if (c == 'c')
		return (ft_putchar_fd(fd, va_arg(args, int)));
	if (c == 'p')
		return (ft_putptr_fd(fd, va_arg(args, void *)));
	if (c == 'u')
		return (ft_putunbr_fd(fd, va_arg(args, unsigned int)));
	if (c == 'x')
		return (ft_putlhex_fd(fd, va_arg(args, unsigned int)));
	if (c == 'X')
		return (ft_putuhex_fd(fd, va_arg(args, unsigned int)));
	if (c == '%')
		return (ft_putchar_fd(fd, '%'));
	return (0);
}

int	ft_fprintf(int fd, const char *format, ...)
{
	va_list	args;
	int		printed_chars;

	va_start(args, format);
	printed_chars = 0;
	while (*format)
	{
		if (*format == '%')
		{
			printed_chars += ft_handle(*(++format), args, fd);
			if (!(*format))
				break ;
		}
		else
			printed_chars += ft_putchar_fd(*format, fd);
		format++;
	}
	va_end(args);
	return (printed_chars);
}
