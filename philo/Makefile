SRCS=	main.c			\
		utils.c			\
		create.c		\
		clear_table.c	\
		actions.c		\
		routines.c

OBJS=	${SRCS:.c=.o}

GCC=	gcc -Wall -Werror -Wextra -pthread -D _BSD_SOURCE

NAME=	philo

RM=		rm -rf

.c.o:
		${GCC} -c $< -o ${<:.c=.o}

all:	$(NAME)

$(NAME):	${OBJS}
		${GCC} ${OBJS} -o ${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		${RM} ${NAME}

re:		fclean	all

.PHONY:	all	NAME	clean	fclean	re
