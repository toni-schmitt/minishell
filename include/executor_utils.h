/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:18:55 by toni              #+#    #+#             */
/*   Updated: 2021/12/14 16:31:24 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

int		clean_exp_tok_cmds(t_exp_tok *exp_tok);
int		handle_inbuilt_redir(t_exp_tok *exp_tok);
int		execute_inbuilt(char *cmd[]);
bool	is_inbuilt(char *cmd);

#endif