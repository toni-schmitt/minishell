/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_perror.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/13 13:03:40 by tblaase           #+#    #+#             */
/*   Updated: 2021/12/13 13:07:57 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/**
 * @brief  will perror with the given message *msg and return exit_status
 * @note
 * @param  exit_status: the exit status you want ft_perror to give
 * @param  *msg: the message that should be printet by perror before the error
 * @retval exit_status
 */
int	ft_perror(int exit_status, char *msg)
{
	perror(msg);
	return (exit_status);
}
