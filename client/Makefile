CC	=	g++

DIR	=	rtype_client/rtype_client

NAME	=	client

SRC	=	$(DIR)/AEventManager.cpp 	\
		$(DIR)/AGraphManager.cpp 	\
		$(DIR)/AGUIElement.cpp		\
		$(DIR)/AMenu.cpp 		\
		$(DIR)/ASocketClient.cpp 	\
		$(DIR)/ASoundManager.cpp 	\
		$(DIR)/Button.cpp 		\
		$(DIR)/CheckBox.cpp 		\
		$(DIR)/client.cpp 		\
		$(DIR)/CmdManager.cpp 		\
		$(DIR)/Color.cpp 		\
		$(DIR)/CursorBox.cpp 		\
		$(DIR)/Game.cpp 		\
		$(DIR)/InputBox.cpp 		\
		$(DIR)/ListBox.cpp 		\
		$(DIR)/main.cpp 		\
		$(DIR)/Menu.cpp 		\
		$(DIR)/Rect.cpp 		\
		$(DIR)/RectDecor.cpp 		\
		$(DIR)/SFML.cpp 		\
		$(DIR)/SFMLEvent.cpp 		\
		$(DIR)/SFMLSOund.cpp 		\
		$(DIR)/SocketClientTCP.cpp	\
		$(DIR)/SocketClientUDP.cpp	\

OBJ	=	$(SRC:.cpp=.o)

CPPFLAGS=	-W -Wall -Wextra -ansi -pedantic -g -I$(DIR) -std=gnu++11

LDFLAGS	=	-lsfml-graphics -lsfml-window -lsfml-system

all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		rm -rf $(DIR)/$(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
