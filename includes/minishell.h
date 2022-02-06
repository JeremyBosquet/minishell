/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:09:26 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/06 14:09:54 by mmosca           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//	~~	Includes ---------------------------------------------------------------

# include "../libs/libft/includes/libft.h"

# include <readline/history.h>
# include <readline/readline.h>
# include <fcntl.h>
# include <signal.h>

//	~~	Enums ------------------------------------------------------------------

enum e_redirection {
	HEREDOC,
	SIMPLE,
	TRUNC,
	APPEND,
};

//	~~	Typedefs ---------------------------------------------------------------

typedef struct s_command	t_command;
typedef struct s_minishell	t_minishell;

//	~~	Structures -------------------------------------------------------------

struct s_command {
	char	**cmd;
	char	*args;
	char	*path;
	char	*path_file_in;
	char	*path_file_out;
	int		filedescriptor_in;
	int		filedescriptor_out;
	int		type_of_infile;
	int		type_of_outfile;
};

struct	s_minishell {
	t_command	*cmds;
	bool		is_running;
	char		**env;
	int			nb_cmds;
	int			last_exit_code;
};

//	~~	Prototypes -------------------------------------------------------------

#endif
