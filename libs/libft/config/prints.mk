##	~~	Colors -----------------------------------------------------------------

override	GREY		:=	\033[30m
override	RED			:=	\033[31m
override	GREEN		:=	\033[32m
override	ORANGE		:=	\033[33m
override	BLUE		:=	\033[34m
override	PURPLE		:=	\033[35m
override	LIGHTBLUE	:=	\033[36m
override	WHITE		:=	\033[37m

##	~~	Styles -----------------------------------------------------------------

override	END			:=	\033[0m
override	BOLD		:=	\033[1m
override	ITALIC		:=	\033[3m
override	UNDERLINE	:=	\033[4m
override	DEL_LINE	:=	\033[2K\r

##	~~	Prints -----------------------------------------------------------------

define	PRINT_CLEAN
	printf "[ ${RED}removing${END} ]\t${LIGHTBLUE}binaries files${END}\n"
endef

define	PRINT_FCLEAN
	printf "[ ${RED}removing${END} ]\t${LIGHTBLUE}executable file${END}\n"
endef

define	PRINT_COMPILING
	printf "%-65b%b" "[ ${ORANGE}compiling${END} ]\t${LIGHTBLUE}$<${END}" "${GREEN}[✓]${END}\n"
endef

define	PRINT_CREATING
	printf "[ ${ORANGE}creating${END} ]\t${LIGHTBLUE}$@${END}\n"
endef

define LINE
	printf "\n              ----------------------------\n\n"
endef
