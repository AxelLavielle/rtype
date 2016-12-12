CC	=	g++

DIR	=	rtype_client/rtype_client

NAME	=	client

SRC	=	$(DIR)/AEventManager.cpp 	\
		$(DIR)/AGraphManager.cpp 	\
		$(DIR)/AMenu.cpp 		\
		$(DIR)/ASocketClient.cpp 	\
		$(DIR)/ASoundManager.cpp 	\
		$(DIR)/Button.cpp 		\
		$(DIR)/client.cpp 		\
		$(DIR)/CmdManager.cpp 		\
		$(DIR)/Color.cpp 		\
		$(DIR)/InputBox.cpp 		\
		$(DIR)/ListBox.cpp 		\
		$(DIR)/main.cpp 		\
		$(DIR)/Menu.cpp 		\
		$(DIR)/Rect.cpp 		\
		$(DIR)/SFML.cpp 		\
		$(DIR)/SFMLEvent.cpp 		\
		$(DIR)/SFMLSOund.cpp 		\
		$(DIR)/SocketClientTCP.cpp

OBJ	=	$(SRC:.cpp=.o)

CPPFLAGS=	-W -Wall -Wextra -ansi -pedantic -g -I$(DIR) -Ires/lib/SFML/include/SFML -Ires/lib/SFML/include/SFML/Audio -Ires/lib/SFML/include/SFML/Graphics -Ires/lib/SFML/include/SFML/Network -Ires/lib/SFML/include/SFMLSystem -Ires/lib/SFML/include/SFML/Window

LDFLAGS	=	-Lres/lib/SFML/lib/ -lsfml-graphics -lsfml-window -lsfml-system


all:		$(NAME)

$(NAME):	$(OBJ)
		$(CC) $(OBJ) -o $(NAME) $(LDFLAGS)

clean:
		rm -rf $(DIR)/$(OBJ)

fclean:		clean
		rm -rf $(NAME)

re:		fclean all

.PHONY:		all clean fclean re
