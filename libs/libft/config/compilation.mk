##	~~	Compilations -----------------------------------------------------------

DEBUG_MODE			:=	no

override	CFLAGS	:=	-Wall -Wextra -Werror
override	ARFLAGS	:=	rcs

ifeq (${DEBUG_MODE}, yes)
override	CFLAGS	+= -g3 -fsanitize=address
else
override	CFLAGS	+= -O2 -ggdb3
endif
