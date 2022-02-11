/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbosquet <jbosquet@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:09:26 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/10 16:56:14 by jbosquet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//	~~	Includes ---------------------------------------------------------------

# include "../libs/libft/includes/libft.h"

# include <readline/history.h>
# include <readline/readline.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
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
	char	**command;
	char	*arguments;
	char	*path;
	char	*path_file_in;
	char	*path_file_out;
	int		filedescriptor_in;
	int		filedescriptor_out;
	int		type_of_infile;
	int		type_of_outfile;
	bool	do_run;
	int		pipes[2];
};

struct	s_minishell {
	t_command	*commands;
	t_list		*garbage;
	pid_t		*pids;
	bool		is_running;
	char		**environnement;
	char		*current_pwd;
	int			number_of_commands;
	int			exit_code;
};

//	~~	Prototypes -------------------------------------------------------------

//	~	environnement/add.c ------------

char
**add_to_environnement(char **environnement, char *new, t_list *garbage);

//	~	environnement/clean.c ----------

void
clean_environnement(char **environnement, int size);

//	~	environnement/copy.c -----------

char
**copy_environnement(char **environnement, int option, t_list *garbage);

//	~	environnement/delete.c ---------

char
**delete_line_in_environnement(char **environnement, char *name, t_list *g);

//	~	environnement/find.c -----------

int
find_line_of_name(char **environnement, char *name, t_list *garbage);

//	~	environnement/get.c ------------

char
*get_name_of_line(char *line, t_list *garbage);

char
*get_value_of_line(char *line, t_list *garbage);

char
*get_env_value(char *name, t_minishell *minishell);

//	~	environnement/replace.c --------

char
**replace_line_in_environnement(char **environnement, int line, char *value,
	t_list *garbage);

//	~	parsing/arguments.c ------------

void
check_number_of_argument(int number_of_arguments);

//	~	parsing/parse_new_line.c -------

void
parse_new_line(t_minishell *minishell, char *new_line);

//	~	parsing/parse_new_line.c -------

char
*check_new_line(char *new_line, t_list *garbage);

//	~	parsing/parse_and_replace_in_quotes.c

void
replace_env(t_minishell *minishell);

//	~	structures/clean.c -------------

bool
clean_minishell(t_minishell *minishell);

//	~	structures/init.c --------------

bool
init_minishell(t_minishell *minishell, char	**envp);

//	~	signals.c ----------------------

void
my_signal(void);

// A SUPPRIMER A LA FIN

void	print_commands(t_minishell *minishell);
void	print_command(char **str);

#endif
