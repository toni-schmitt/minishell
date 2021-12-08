/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 22:00:00 by toni              #+#    #+#             */
/*   Updated: 2021/12/08 17:54:49 by tblaase          ###   ########.fr       */
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
int		wait_for_heredoc(t_par_tok *par_tok, t_exp_tok *exp_tok);
int		handle_redir(t_par_tok **par_toks, t_exp_tok **exp_toks);

#endif