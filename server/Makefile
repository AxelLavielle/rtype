
CC		=	g++

DIR		=	rtype_server/rtype_server

COMMON		=	../common

SERIALIZE	=	../common/Serialize

NAME		=	server

SRC		=	$(DIR)/ASocketServer.cpp		\
			$(DIR)/main.cpp				\
			$(DIR)/SocketServerTCP.cpp		\
			$(DIR)/SocketServerUDP.cpp		\
			$(DIR)/ClientManager.cpp		\
			$(DIR)/ServerClient.cpp			\
			$(DIR)/Server.cpp			\
			$(DIR)/Room.cpp				\
			$(DIR)/Game.cpp				\
			$(DIR)/RoomManager.cpp			\
			$(DIR)/SocketAddress.cpp		\
			$(DIR)/CmdManager.cpp			\
			$(DIR)/Wave.cpp				\
			$(DIR)/DlManager.cpp			\
			$(DIR)/DlLoader.cpp			\
			$(DIR)/ADlLoader.cpp			\
			$(DIR)/DirectoryBrowser.cpp		\
			$(DIR)/ADirectoryBrowser.cpp		\
			$(COMMON)/MemTools.cpp			\
			$(COMMON)/Thread.cpp			\
			$(COMMON)/Mutex.cpp			\
			$(COMMON)/AThread.cpp			\
			$(COMMON)/AMutex.cpp			\
			$(COMMON)/ThreadPool.cpp		\
			$(COMMON)/PathFileManager.cpp		\
			$(SERIALIZE)/AEntity.cpp		\
			$(SERIALIZE)/Serialize.cpp		\
			$(SERIALIZE)/InputCmd.cpp		\
			$(SERIALIZE)/RoomInfoCmd.cpp		\
			$(SERIALIZE)/BasicCmd.cpp		\
			$(SERIALIZE)/ListRoomCmd.cpp		\
			$(SERIALIZE)/ACommand.cpp		\
			$(SERIALIZE)/Player.cpp			\
			$(SERIALIZE)/PowerUp.cpp		\
			$(SERIALIZE)/Barrier.cpp		\
			$(SERIALIZE)/Missile.cpp		\
			$(SERIALIZE)/CollisionBox.cpp		\


OBJ		=	$(SRC:.cpp=.o)

LDFLAGS 	=  	-pthread -ldl

CPPFLAGS	=	-W -Wall -Wextra -ansi -g -std=c++11 -I$(DIR) -I$(COMMON) -I$(SERIALIZE)


all		:	$(NAME)

$(NAME)		:	$(OBJ)
			$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean		:
			rm -rf $(DIR)/$(OBJ)

fclean		:	clean
			rm -rf $(NAME)

re		:	fclean all

.PHONY		:	all clean fclean re
