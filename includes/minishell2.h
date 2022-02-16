/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:24:20 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/16 17:29:20 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

# include "minishell.h"
# include <errno.h>

void
signal_heredoc(int signo);

char
**add_oldpwd(char **environnement, t_list *garbage);

void
child_loop(t_minishell *minishell, int i, int j);

void
wait_exec(t_minishell *minishell);

bool
is_builtins(char *command);

char
**ft_dup_2array(char **src, t_list *garbage, int opt);

void
execute(t_minishell *minishell);

void
handle_signals(int signo);

void
signal_child(int signo);

int
builtin_cd(t_minishell *minishell, int i);

void
builtin_echo(t_minishell *minishell, int i);

void
builtin_exit(t_minishell *minishell, int i);

void
builtin_pwd(t_minishell *minishell, int i);

void
builtin_env(t_minishell *minishell, int i);

int
builtin_unset(t_minishell *minishell, int i);

int
builtin_export(t_minishell *minishell, int i);

bool
is_special_builtins(char *command);

void
execute_special_builtins(t_minishell *minishell);

void
execute_builtins(t_minishell *minishell, char *command, int i);

char
*check_path(char *command, char **environnement, t_list *garbage);

#endif
