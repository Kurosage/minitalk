NAME1 	= server
NAME2 	= client
SRC1 	= server.c utils.c
SRC2 	= client.c utils.c
FLAGS 	= -Wall -Wextra -Werror
RM		= rm -f
all: ${NAME1} ${NAME2}

${NAME1}:	
			@gcc ${FLAGS} ${SRC1} -o ${NAME1}

${NAME2}:	
			@gcc ${FLAGS} ${SRC2} -o ${NAME2}

clean:
			@${RM} ${NAME1} ${NAME2}
fclean:		clean
			@${RM} ${NAME1} ${NAME2}

re:		fclean all

.PHONY: all clean fclean re