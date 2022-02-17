##	~~	Headers ----------------------------------------------------------------

override	HEADERS	:=			\
	includes/minishell.h		\
	libs/libft/includes/libft.h

##	~~	Libraries files --------------------------------------------------------

override	LIBS		:=		\
	${LIBFT_DIRECTORY}/libft.a

##	~~	Sources ----------------------------------------------------------------

override	SOURCES	:=		\
	cd.c					\
	echo.c					\
	env.c					\
	exit.c					\
	export.c				\
	export_utils.c			\
	pwd.c					\
	unset.c					\
	builtins.c				\
	execute.c				\
	execute_utils.c			\
	path.c					\
	add.c					\
	clean.c					\
	copy.c					\
	delete.c				\
	find.c					\
	get.c					\
	replace.c				\
	arguments.c				\
	check.c					\
	check_pipe.c			\
	check_quotes.c			\
	check_chevrons.c		\
	replace_env.c			\
	replace_env2.c			\
	replace_quotes.c		\
	parse_new_line.c		\
	print.c					\
	redirections.c			\
	redirections2.c			\
	utils.c					\
	clean_struct.c			\
	init.c					\
	minishell.c				\
	signals.c