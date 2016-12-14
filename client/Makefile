CC	=	g++

DIR	=	rtype_client/rtype_client

NAME	=	client

SRC	=	$(DIR)/ACommand.cpp	 	\
		$(DIR)/AEventManager.cpp 	\
		$(DIR)/AGraphManager.cpp 	\
		$(DIR)/AGUIElement.cpp		\
		$(DIR)/AMenu.cpp 		\
		$(DIR)/ASocketClient.cpp 	\
		$(DIR)/ASoundManager.cpp 	\
		$(DIR)/Button.cpp 		\
		$(DIR)/CheckBox.cpp 		\
		$(DIR)/ChatInfoCmd.cpp 		\
		$(DIR)/client.cpp 		\
		$(DIR)/CmdManager.cpp 		\
		$(DIR)/Color.cpp 		\
		$(DIR)/CursorBox.cpp 		\
		$(DIR)/EntityCmd.cpp 		\
		$(DIR)/Game.cpp 		\
		$(DIR)/InputBox.cpp 		\
		$(DIR)/InputCmd.cpp 		\
		$(DIR)/ListInfoCmd.cpp 		\
		$(DIR)/ListBox.cpp 		\
		$(DIR)/main.cpp 		\
		$(DIR)/Menu.cpp 		\
		$(DIR)/Rect.cpp 		\
		$(DIR)/RectDecor.cpp 		\
		$(DIR)/RoomInfoCmd.cpp 		\
		$(DIR)/SFML.cpp 		\
		$(DIR)/SFMLEvent.cpp 		\
		$(DIR)/SFMLSound.cpp 		\
		$(DIR)/SocketClientTCP.cpp	\
		$(DIR)/Sound.cpp

OBJ	=	$(SRC:.cpp=.o)

CPPFLAGS=	-W -Wall -Wextra -ansi -pedantic -g -I$(DIR) -std=c++11 -std=gnu++11 -I../common

LDFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		rm -rf $(DIR)/$(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
