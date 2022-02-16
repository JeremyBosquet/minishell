##	~~	Headers ----------------------------------------------------------------

override	HEADERS	:=			\
	includes/minishell.h		\
	libs/libft/includes/libft.h

##	~~	Libraries files --------------------------------------------------------

override	LIBS		:=		\
	${LIBFT_DIRECTORY}/libft.a

##	~~	Sources ----------------------------------------------------------------

override	SOURCES	:=						\
	environnement/add.c						\
	environnement/clean.c					\
	environnement/copy.c					\
	environnement/delete.c					\
	environnement/find.c					\
	environnement/get.c						\
	environnement/replace.c					\
	parsing/arguments.c						\
	parsing/check.c							\
	parsing/check_pipe.c					\
	parsing/check_quotes.c					\
	parsing/check_chevrons.c				\
	parsing/replace_env.c					\
	parsing/replace_env2.c					\
	parsing/replace_quotes.c				\
	parsing/parse_new_line.c				\
	parsing/print.c							\
	parsing/redirections.c					\
	structures/clean.c						\
	structures/init.c						\
	minishell.c								\
	signals.c