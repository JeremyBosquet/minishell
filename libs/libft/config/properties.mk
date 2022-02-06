##	~~	Properties -------------------------------------------------------------

##	~	Folders ------------------------

override	BINARIES_DIRECTORY	:=	bin
override	BUILD_DIRECTORY		:=	build
override	INCLUDES_DIRECTORY	:=	includes
override	SOURCES_DIRECTORY	:=	src

##	~	Commands -----------------------

override	RM					+=	-R
override	MKDIR				:=	mkdir -p

##	~	General ------------------------

override	NAME				:=	libft.a
override	PROJECT				:=	libft
override	AUTHOR				:=	mmosca
override	DATE				:=	2021/11/02
