/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toni <toni@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/04 22:00:00 by toni              #+#    #+#             */
/*   Updated: 2021/12/14 17:13:54 by toni             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPANDER_UTILS_H
# define EXPANDER_UTILS_H

char	*interprete_env_var(char *lex_tok);

// HEREDOC UTILS

int		wait_for_heredoc(
			t_par_tok *par_tok, t_exp_tok *exp_tok, char *buf, char *heredoc
			);
int		handle_redir(t_par_tok *par_tok, t_exp_tok *exp_tok, int pipe_type);
int		handle_pipes(t_exp_tok *exp_tok, int pipe_type);
int		set_pipe_type(t_par_tok **par_toks, int i);
int		handle_subshell(t_exp_tok *exp_tok);

// EXPANDER UTILS

int		free_exp_toks(t_exp_tok *exp_toks[], int exit_status);
size_t	get_tok_size(t_par_tok *par_toks[]);
int		init(t_exp_tok **exp_tok);
int		get_tokens(t_par_tok *par_toks[]);
int		repinterprete_env_vars(t_par_tok *par_toks[], t_exp_tok *exp_toks[]);

#endif