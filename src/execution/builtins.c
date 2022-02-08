/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 09:32:32 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/08 09:37:00 by mmosca           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "minishell2.h"

bool
	is_builtins(char *command)
{
	if (ft_strcmp(command, "echo") == 0 OR ft_strcmp(command, "cd") == 0 \
	OR ft_strcmp(command, "pwd") == 0 OR ft_strcmp(command, "export") == 0 \
	OR ft_strcmp(command, "unset") == 0 OR ft_strcmp(command, "env") == 0 \
	OR ft_strcmp(command, "exit") == 0)
		return (true);
	return (false);
}
