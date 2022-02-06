.SILENT:

##	~~	Includes ---------------------------------------------------------------

include		config/compilation.mk
include		config/prints.mk
include		config/properties.mk
include		config/sources.mk

##	~~	Configurations ---------------------------------------------------------

override	CFLAGS			+=	$(sort $(addprefix -I./, $(dir ${HEADERS})))
override	OBJS			:=	$(addprefix ${BINARIES_DIRECTORY}/, ${SOURCES:.c=.o})

##	~~	Rules ------------------------------------------------------------------

.PHONY: all
all: ${NAME}

bin/%.o:	${SOURCES_DIRECTORY}/%.c ${HEADERS} Makefile
	${MKDIR} $(dir $@)
	${CC} ${CFLAGS} -c $< -o $@
	${PRINT_COMPILING}

${NAME}:	${OBJS}
	${AR} ${ARFLAGS} $@ $^
	printf "\n"

.PHONY: clean # Remove binaries files from project.
clean:
	${RM} ${OBJS}

.PHONY: fclean # Remove executable file from project.
fclean: clean
	${RM} ${NAME}

.PHONY: re # Remove alls binaries files and executable files and re-compile them
re:	fclean all
