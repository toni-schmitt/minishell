/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 22:00:00 by toni              #+#    #+#             */
/*   Updated: 2021/12/04 22:01:07 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_UTILS_H
# define EXPANDER_UTILS_H

// HEREDOC UTILS

/**
 * @brief  Searches for heredoc in par_toks and waits if found
 * @note   
 * @param  *par_toks[]: 
 * @retval int to indicate success or failure
 */
int		check_for_heredoc(t_par_tok *par_toks[]);

#endif