
CC	=	g++

DIR	=	rtype_server/rtype_server

COMMON	=	../common/

NAME	=	server

SRC	=	$(DIR)/ASocketServer.cpp	\
		$(DIR)/main.cpp			\
		$(DIR)/SocketServerTCP.cpp	\
		$(DIR)/SocketServerUDP.cpp	\
		$(DIR)/ClientManager.cpp	\
		$(DIR)/ServerClient.cpp		\
		$(DIR)/Server.cpp		\
		$(DIR)/Room.cpp			\
		$(DIR)/RoomManager.cpp		\
		$(COMMON)/MemTools.cpp		\

OBJ	=	$(SRC:.cpp=.o)

CPPFLAGS=	-W -Wall -Wextra -ansi -pedantic -g -std=c++11 -I$(DIR) -I$(COMMON)


all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		rm -rf $(DIR)/$(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
