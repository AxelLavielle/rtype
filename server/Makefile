CC	=	g++

DIR	=	rtype_server/rtype_server

NAME	=	server

SRC	=	$(DIR)/ADlLoader.cpp		\
		$(DIR)/AEntity.cpp		\
		$(DIR)/ASocketServer.cpp	\
		$(DIR)/Barrier.cpp		\
		$(DIR)/DlManager.cpp		\
		$(DIR)/main.cpp			\
		$(DIR)/Monster.cpp		\
		$(DIR)/Player.cpp		\
		$(DIR)/PowerUp.cpp		\
		$(DIR)/SocketServerTCP.cpp	\
		$(DIR)/UDlLoader.cpp		\
		$(DIR)/WDlLoader.cpp		\

OBJ	=	$(SRC:.cpp=.o)

CPPFLAGS=	-W -Wall -Wextra -ansi -pedantic -g -I$(DIR)

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		rm -rf $(DIR)/$(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
