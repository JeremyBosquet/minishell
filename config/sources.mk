##	~~	Headers ----------------------------------------------------------------

override	HEADERS	:=			\
	includes/minishell.h		\
	libs/libft/includes/libft.h

##	~~	Libraries files --------------------------------------------------------

override	LIBS		:=		\
	${LIBFT_DIRECTORY}/libft.a

##	~~	Sources ----------------------------------------------------------------

override	SOURCES	:=			\
	environnement/add.c			\
	environnement/clean.c		\
	environnement/copy.c		\
	environnement/delete.c		\
	environnement/find.c		\
	environnement/get.c			\
	environnement/replace.c		\
	parsing/arguments.c			\
	parsing/check.c				\
	parsing/parse_new_line.c	\
	structures/clean.c			\
	structures/init.c			\
	minishell.c					\
	signals.c