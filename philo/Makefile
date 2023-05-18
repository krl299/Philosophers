SRCS=	main.c	\
		utils.c

OBJS=	${SRCS:.c=.o}

GCC=	gcc -Wall -Werror -Wextra

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
