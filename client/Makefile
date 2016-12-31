CC	=	g++

DIR	=	rtype_client/rtype_client

COM	=	../common/

SER	=	../common/Serialize

NAME	=	client

SRC	=	$(SER)/ACommand.cpp	 	\
		$(SER)/AEntity.cpp	 	\
		$(DIR)/AEventManager.cpp 	\
		$(DIR)/AGraphManager.cpp 	\
		$(DIR)/AGUIElement.cpp		\
		$(DIR)/AMenu.cpp 		\
		$(COM)/AMutex.cpp 		\
		$(DIR)/APage.cpp 		\
		$(DIR)/ASocketClient.cpp 	\
		$(DIR)/ASoundManager.cpp 	\
		$(COM)/AThreadPool.cpp	 	\
		$(COM)/AThread.cpp	 	\
		$(SER)/BasicCmd.cpp 		\
		$(DIR)/Button.cpp 		\
		$(SER)/Barrier.cpp 		\
		$(DIR)/CheckBox.cpp 		\
		$(SER)/ChatInfoCmd.cpp 		\
		$(DIR)/Client.cpp 		\
		$(DIR)/CmdManager.cpp 		\
		$(DIR)/Color.cpp 		\
		$(DIR)/CreateRoomPage.cpp	\
		$(DIR)/CursorBox.cpp 		\
		$(DIR)/EndGamePage.cpp 		\
		$(SER)/EntityCmd.cpp 		\
		$(DIR)/Game.cpp 		\
		$(DIR)/GUIPage.cpp 		\
		$(DIR)/HomePage.cpp 		\
		$(DIR)/InputBox.cpp 		\
		$(DIR)/InputKey.cpp 		\
		$(SER)/InputCmd.cpp 		\
		$(SER)/CollisionBox.cpp	 	\
		$(DIR)/InsideRoomPage.cpp	\
		$(SER)/ListRoomCmd.cpp 		\
		$(DIR)/ListBox.cpp 		\
		$(DIR)/LobbyPage.cpp 		\
		$(DIR)/main.cpp 		\
		$(DIR)/SaveConfig.cpp 		\
		$(DIR)/Menu.cpp 		\
		$(COM)/Mutex.cpp 		\
		$(DIR)/PausePage.cpp 		\
		$(SER)/Player.cpp 		\
		$(SER)/PowerUp.cpp 		\
		$(DIR)/Rect.cpp 		\
		$(DIR)/RectDecor.cpp 		\
		$(SER)/RoomInfoCmd.cpp 		\
		$(SER)/Serialize.cpp		\
		$(DIR)/SettingsNextPage.cpp	\
		$(DIR)/SettingsPage.cpp		\
		$(DIR)/SFML.cpp 		\
		$(DIR)/SFMLEvent.cpp 		\
		$(DIR)/SFMLSound.cpp 		\
		$(DIR)/SocketClientTCP.cpp	\
		$(DIR)/SocketClientUDP.cpp	\
		$(DIR)/Sound.cpp		\
		$(DIR)/LoadingPage.cpp		\
		$(COM)/ThreadPool.cpp		\
		$(COM)/Thread.cpp		\
		$(COM)/MemTools.cpp		\
		$(DIR)/PathFileManager.cpp

OBJ	=	$(SRC:.cpp=.o)

CPPFLAGS=	-W -Wall -Wextra -ansi -pedantic -g -I$(DIR) -I../common/ -I../common/Serialize -std=c++11 -std=gnu++11 -I/usr/local/include

LDFLAGS	=	 -pthread -L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		rm -rf $(DIR)/$(OBJ)
		rm -rf $(COM)/$(OBJ)
		rm -rf $(SER)/$(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
