/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:09:26 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/06 11:56:29 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//	~~	Includes ---------------------------------------------------------------

# include "../libs/libft/includes/libft.h"

# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>

enum	e_redirection {
	HEREDOC,
	SIMPLE,
	TRUNC,
	APPEND
};

typedef struct s_command
{
	char	**cmd;
	char	*args;
	char	*path;
	char	*path_file_in;
	char	*path_file_out;
	int		filedescriptor_in;
	int		filedescriptor_out;
	int 	type_of_infile;
	int 	type_of_outfile;
}	t_command;

struct	minishell {
	int 		last_exit_code;
	int			nb_cmds;
	char		**env;
	t_command	*cmds;
};

#endif
