##	~~	Compilations -----------------------------------------------------------

DEBUG_MODE			:=	no

override	RL_LIB	:= -L$(shell brew --prefix readline)/lib
override	RL_INC	:= -I$(shell brew --prefix readline)/include

override	CFLAGS	:=	-Wall -Wextra -Werror

ifeq (${DEBUG_MODE}, yes)
override	CFLAGS	+= -g3 -fsanitize=address
else
override	CFLAGS	+= -O2 -ggdb3
endif
