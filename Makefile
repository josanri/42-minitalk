NAME		= minitalk
SRC_S		= ft_server.c
SRC_C		= ft_client.c ft_putnbr.c
OBJS_S		= ${SRC_S:.c=.o}
OBJS_C		= ${SRC_C:.c=.o}

SRC_SB		= ft_server_bonus.c
SRC_CB		= ft_client_bonus.c ft_putnbr_bonus.c
OBJS_SB		= ${SRC_SB:.c=.o}
OBJS_CB		= ${SRC_CB:.c=.o}

N_SERVER	= server
N_CLIENT	= client

CC			= gcc
CFLAGS		=	-Wall -Wextra -Werror
RM			=	rm -f

all: server client

${NAME}: all

server: ${OBJS_S}
	${CC} ${CFLAGS} ${OBJS_S} -o ${N_SERVER}

client: ${OBJS_C}
	${CC} ${CFLAGS} ${OBJS_C} -o ${N_CLIENT}

server_bonus: ${OBJS_SB}
	${CC} ${CFLAGS} ${OBJS_SB} -o ${N_SERVER}

client_bonus: ${OBJS_CB}
	${CC} ${CFLAGS} ${OBJS_CB} -o ${N_CLIENT}

.c.o:
	@${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

clean:	
	${RM} ${OBJS_S} ${OBJS_C} ${OBJS_SB} ${OBJS_CB}
	@echo "🗑️  Temporal files removed succesfully 🗑️"

fclean:	clean
	${RM} ${N_CLIENT} ${N_SERVER}
	@echo "🗑️  Executables removed succesfully 🗑️"


bonus: server_bonus client_bonus
	@echo "✅ Bonus compiled succesfully ✅"

re: fclean all

.PHONY: all bonus clean fclean re