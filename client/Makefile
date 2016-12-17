CC	=	g++

DIR	=	rtype_client/rtype_client

COM	=	../common/Serialize

NAME	=	client

SRC	=	$(COM)/ACommand.cpp	 	\
		$(DIR)/AEventManager.cpp 	\
		$(DIR)/AGraphManager.cpp 	\
		$(DIR)/AGUIElement.cpp		\
		$(DIR)/AMenu.cpp 		\
		$(DIR)/ASocketClient.cpp 	\
		$(DIR)/ASoundManager.cpp 	\
		$(DIR)/Button.cpp 		\
		$(DIR)/CheckBox.cpp 		\
		$(COM)/ChatInfoCmd.cpp 		\
		$(DIR)/Client.cpp 		\
		$(DIR)/CmdManager.cpp 		\
		$(DIR)/Color.cpp 		\
		$(DIR)/CreateRoomPage.cpp	\
		$(DIR)/CursorBox.cpp 		\
		$(COM)/EntityCmd.cpp 		\
		$(DIR)/Game.cpp 		\
		$(DIR)/GUIPage.cpp 		\
		$(DIR)/HomePage.cpp 		\
		$(DIR)/InputBox.cpp 		\
		$(COM)/InputCmd.cpp 		\
		$(DIR)/InsideRoomPage.cpp	\
		$(COM)/ListInfoCmd.cpp 		\
		$(DIR)/ListBox.cpp 		\
		$(DIR)/LobbyPage.cpp 		\
		$(DIR)/main.cpp 		\
		$(DIR)/Menu.cpp 		\
		$(DIR)/APage.cpp 		\
		$(DIR)/Rect.cpp 		\
		$(DIR)/RectDecor.cpp 		\
		$(COM)/RoomInfoCmd.cpp 		\
		$(DIR)/RoomListPage.cpp		\
		$(COM)/Serialize.cpp		\
		$(DIR)/SettingsPage.cpp		\
		$(DIR)/SFML.cpp 		\
		$(DIR)/SFMLEvent.cpp 		\
		$(DIR)/SFMLSound.cpp 		\
		$(DIR)/SocketClientTCP.cpp	\
		$(DIR)/SocketClientUDP.cpp	\
		$(DIR)/Sound.cpp		\
		$(DIR)/PathFileManager.cpp

OBJ	=	$(SRC:.cpp=.o)

CPPFLAGS=	-W -Wall -Wextra -ansi -pedantic -g -I$(DIR) -I../common/ -I../common/Serialize -std=c++11 -std=gnu++11 -I/usr/local/include

LDFLAGS	=	-L/usr/local/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		rm -rf $(DIR)/$(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
