SRCS:	main.c

OBJS:	${SRCS:.c=.o}

GCC:	gcc -Wall -Werror -Wextra

NAME:	philo_bonus

RM:		rm -rf

.c.o:
		@${GCC} -o ${<:.c=.o}
all:	$(NAME)

$(NAME):	${OBJS}
		@${GCC} ${OBJS} -o ${NAME}

clean:
		${RM} ${OBJS}

fclean:	clean
		@${RM} ${NAME}

re:		fclean	all

.PHONY:	all	NAME	clean	fclean	re
