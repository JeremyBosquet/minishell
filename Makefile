# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jbosquet <jbosquet@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/05 17:07:00 by mmosca            #+#    #+#              #
#    Updated: 2022/02/06 15:58:42 by jbosquet         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.SILENT:
.SUFFIXES: .c

##	~~	Includes ---------------------------------------------------------------

include		config/compilations.mk
include		config/prints.mk
include		config/properties.mk
include		config/sources.mk

##	~~	Configurations ---------------------------------------------------------

override	CFLAGS			+=	$(sort $(addprefix -I./, $(dir ${HEADERS})))
override	CFLAGS			+=	${RL_INC}
override	OBJS			:=	$(addprefix ${BINARIES_DIRECTORY}/, ${SOURCES:.c=.o})
override	OBJS_DIRECTORY	:=	$(sort $(dir ${OBJS}))

##	~~	Rules ------------------------------------------------------------------

.PHONY: all # Compile sources files to create the executable file.
all:	header libft ${BUILD_DIRECTORY}/${NAME}


${BINARIES_DIRECTORY}/%.o:	${SOURCES_DIRECTORY}/%.c ${HEADERS} Makefile ${LIBS}
	${CC} ${CFLAGS} -c $< -o $@
	${PRINT_COMPILING}

${OBJS}:	| ${OBJS_DIRECTORY}

${OBJS_DIRECTORY}:
	${MKDIR} $@

${BUILD_DIRECTORY}/${NAME}:	${OBJS}
	${MKDIR} $(dir $@)
	${CC} ${CFLAGS} ${RL_LIB} ${LIBS} -lreadline $^ -o $@
	${LINE}
	${PRINT_CREATING}

.PHONY: libft
libft:
	${MAKE} all -C ${LIBFT_DIRECTORY}

.PHONY: clean # Remove binaries files from project.
clean:
	${RM} ${OBJS}
	${MAKE} clean -C ${LIBFT_DIRECTORY}
	${PRINT_CLEAN}

.PHONY: fclean # Remove executable file from project.
fclean:	header clean
	${RM} ${BUILD_DIRECTORY}/${NAME}
	${MAKE} fclean -C ${LIBFT_DIRECTORY}
	${PRINT_FCLEAN}
	${LINE}

.PHONY: re # Remove alls binaries files and executable files and re-compile them
re:	fclean all

.PHONY: run # Run the program with value of test
run:	header all
ifeq (${DEBUG_MODE}, yes)
	./${BUILD_DIRECTORY}/${NAME}
else
	leaks -atExit -q -- ./${BUILD_DIRECTORY}/${NAME}
endif

.PHONY: header # Display the header with properties about the project.
header:
	printf "${ORANGE}project:\t${END}${PROJECT}\n"
	printf "${ORANGE}author:\t\t${END}${AUTHOR}\n"
	printf "${ORANGE}debug mode:\t${END}${DEBUG_MODE}\n"
	printf "${ORANGE}compiler:\t${END}${CC}\n"
	printf "${ORANGE}flags:\t\t${END}${CFLAGS}\n"
	printf "${ORANGE}date:\t\t${END}${DATE}\n"
	printf "              ____________________________\n\n"

.PHONY: help # Generate list of targets with descriptions.
help: header
	printf "${ITALIC}if you want compile with debug mode, add DEBUG=yes after the rule name.\n${END}"
	printf "${PURPLE}${BOLD}usage:${END} make [rule name]\n\n"
	grep '^.PHONY: .* #' Makefile | sed 's/\.PHONY: \(.*\) # \(.*\)/\1	\2/' | expand -t12
	${PRINT_LINE}
