##	~~	Headers ----------------------------------------------------------------

override	HEADERS	:=			\
	includes/minishell.h		\
	libs/libft/includes/libft.h

##	~~	Libraries files --------------------------------------------------------

override	LIBS		:=		\
	${LIBFT_DIRECTORY}/libft.a

##	~~	Sources ----------------------------------------------------------------

override	SOURCES	:=	\
	minishell.c
