
NAME = server

SRC =	main.cpp \
			server.cpp \
			../room/room_manager.cpp \
			../user/user_manager.cpp

HEADER = -I../user \
				-I../room \
				-I../include
OBJDIR =

all : $(NAME)

$(NAME) :
	g++ -std=c++11 -ggdb3 -Wall -Wextra $(HEADER) -c $(SRC)
	g++ -o $(NAME)   *.o -lboost_system -lpthread


clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all
