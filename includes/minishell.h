/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmosca <mmosca@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/05 17:09:26 by mmosca            #+#    #+#             */
/*   Updated: 2022/02/17 13:38:56 by mmosca           ###   ########.fr       */
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
# include <errno.h>
# include <curses.h>
# include <term.h>
# include <termios.h>
# include <fcntl.h>
# include <signal.h>

//	~~	Globals ----------------------------------------------------------------

int							g_exit_code;

//	~~	Defines ----------------------------------------------------------------

# define S_ERROR "syntax error: "

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

struct s_command
{
	char	**command;
	int		fd_in;
	int		fd_out;
	char	*file_out;
	char	*file_in;
	int		type_infile;
	int		type_outfile;
	bool	do_open_in;
	bool	do_open_out;
	bool	do_run;
	int		pipes[2];
};

struct	s_minishell {
	t_command	*commands;
	t_list		*garbage;
	pid_t		*pids;
	bool		is_running;
	char		**environnement;
	char		**env_export;
	char		*current_pwd;
	int			number_of_commands;
	int			exit_code;
};

//	~~	Prototypes -------------------------------------------------------------

char
**add_to_environnement(char **environnement, char *new, t_list *garbage);

void
clean_environnement(char **environnement, int size);

char
**copy_environnement(char **environnement, int option, t_list *garbage);

char
**delete_line_in_environnement(char **environnement, char *name, t_list *g);

int
find_line_of_name(char **environnement, char *name, t_list *garbage);

char
*get_name_of_line(char *line, t_list *garbage);

char
*get_value_of_line(char *line, t_list *garbage);

char
*get_env_value(char *name, t_minishell *minishell);

char
**replace_line_in_environnement(char **environnement, int line, char *value,
	t_list *garbage);

void
check_number_of_argument(int number_of_arguments);

void
parse_new_line(t_minishell *minishell, char *new_line);

char
*check_new_line(char *new_line, t_list *garbage);

void
replace_env(char **tabs, t_minishell *minishell);

void
replace_quotes(char ***tabs, t_minishell *minishell);

void
redirections(t_minishell *minishell, int j);

bool
clean_minishell(t_minishell *minishell);

bool
init_minishell(t_minishell *minishell, char	**envp);

void
my_signal(void);

char
*replace_values_quotes(char *string, t_minishell *minishell);

int
check_pipe(char *new_line);

int
check_chevrons_between(char *new_line);

int
check_chevrons_invalid(char *new_line);

int
check_chevrons_invalid_number(char *new_line);

int
check_quotes(char *new_line);

char
*parse_when_dollar(char *string, int *i, t_minishell *minishell);

void
init_fd_command(t_minishell *minishell, int i);

char
**redir_hered(t_minishell *minishell, int i, int *j);

char
**remove_line_2array(char **tabs, int line, int size, t_list *g);

char
**clean_redirection(t_minishell *minishell, int i, int *j);

void
signal_heredoc(int signo);

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

char
**add_to_export(char **environnement, char *command, t_list *garbage);

int
find_line_of_name2(char **environnement, char *name);

char
**delete_line_in_export(char **environnement, char *name, t_list *g);

// A SUPPRIMER A LA FIN

void	print_commands(t_minishell *minishell);
void	print_command(char **str);

#endif
