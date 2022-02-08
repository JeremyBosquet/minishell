/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:24:20 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/08 14:59:54 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL2_H
# define MINISHELL2_H

# include "minishell.h"

bool
is_builtins(char *command);

void
execute(t_minishell *minishell);

void
builtins_exit(t_minishell *minishell);

void
builtins_pwd(t_minishell *minishell);

bool
is_special_builtins(char *command);

void
execute_special_builtins(t_minishell *minishell);

#endif
