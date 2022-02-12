/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:24:20 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/12 16:27:48 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

# include "minishell.h"
# include <errno.h>

bool
is_builtins(char *command);

void
child(t_minishell *minishell);

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
