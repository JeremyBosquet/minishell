##	~~	Properties -------------------------------------------------------------

##	~	Folders ------------------------

override	BINARIES_DIRECTORY	:=	bin
override	BUILD_DIRECTORY		:=	build
override	LIBS_DIRECTORY		:=	libs
override	LIBFT_DIRECTORY		:=	${LIBS_DIRECTORY}/libft
override	INCLUDES_DIRECTORY	:=	includes
override	SOURCES_DIRECTORY	:=	src

##	~	Commands -----------------------

override	RM					+=	-R
override	MKDIR				:=	mkdir -p

##	~	General ------------------------

override	NAME				:=	minishell
override	PROJECT				:=	minishell
override	AUTHOR				:=	jbosquet - mmosca
override	DATE				:=	2022/02/07
