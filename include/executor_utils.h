/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tblaase <tblaase@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/14 16:18:55 by toni              #+#    #+#             */
/*   Updated: 2021/12/20 15:22:06 by tblaase          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_UTILS_H
# define EXECUTOR_UTILS_H

int		clean_exp_tok_cmds(t_exp_tok *exp_tok);
int		handle_inbuilt_redir(t_exp_tok *exp_tok);
int		execute_inbuilt(t_exp_tok *exp_tok);
bool	is_inbuilt(char *cmd);
int		execute_child(t_exp_tok *exp_tok, char *abs_cmd_path, int status);
int		execute_inbuilt_child(t_exp_tok *exp_tok);
int		execute_inbuilt_reset_fds(t_exp_tok *exp_tok, int saved_fds[2]);

#endif