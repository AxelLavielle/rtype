
CC		=	g++

DIR		=	rtype_server/rtype_server

COMMON		=	../common

SERIALIZE	=	../common/Serialize

NAME		=	server

SRC		=	$(DIR)/ASocketServer.cpp	\
			$(DIR)/main.cpp			\
			$(DIR)/SocketServerTCP.cpp	\
			$(DIR)/SocketServerUDP.cpp	\
			$(DIR)/ClientManager.cpp	\
			$(DIR)/ServerClient.cpp		\
			$(DIR)/Server.cpp		\
			$(DIR)/Room.cpp			\
			$(DIR)/RoomManager.cpp		\
			$(DIR)/CmdManager.cpp		\
			$(COMMON)/MemTools.cpp		\
			$(COMMON)/Thread.cpp		\
			$(COMMON)/Mutex.cpp		\
			$(COMMON)/AThread.cpp		\
			$(COMMON)/AMutex.cpp		\
			$(COMMON)/ThreadPool.cpp	\
			$(SERIALIZE)/AEntity.cpp	\
			$(SERIALIZE)/Serialize.cpp	\
			$(SERIALIZE)/BasicCmd.cpp	\
			$(SERIALIZE)/ListRoomCmd.cpp	\
			$(SERIALIZE)/ACommand.cpp	\
			$(SERIALIZE)/Player.cpp		\
			$(SERIALIZE)/PowerUp.cpp	\
			$(SERIALIZE)/Monster.cpp	\
			$(SERIALIZE)/Barrier.cpp	\

OBJ		=	$(SRC:.cpp=.o)

CPPFLAGS	=	-W -Wall -Wextra -ansi -pedantic -g -std=c++11 -I$(DIR) -I$(COMMON) -I$(SERIALIZE)


all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean		:
			rm -rf $(DIR)/$(OBJ)

fclean		:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
