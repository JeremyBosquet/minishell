##	~~	Properties -------------------------------------------------------------

##	~	Folders ------------------------

override	BINARIES_DIRECTORY	:=	.bin
override	BUILD_DIRECTORY		:=	build
override	LIBS_DIRECTORY		:=	libs
override	LIBFT_DIRECTORY		:=	${LIBS_DIRECTORY}/libft
override	INCLUDES_DIRECTORY	:=	includes
override	SOURCES_DIRECTORY	:=	src

override	VPATH				:=	src/:src/builtins/:src/environnement/:src/execution/:src/parsing/:src/structures/

##	~	Commands -----------------------

override	RM					+=	-R
override	MKDIR				:=	mkdir -p

##	~	General ------------------------

override	NAME				:=	minishell
override	PROJECT				:=	minishell
override	AUTHOR				:=	jbosquet - mmosca
override	DATE				:=	2022/02/07
