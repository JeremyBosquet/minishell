/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell2.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:24:20 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/08 10:09:40 by mmosca           ###   ########lyon.fr   */
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

#endif
