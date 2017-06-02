NAME = libchat

SRC = ./room/room_manager.cpp \
			./user/user_manager.cpp \
			./client/client.cpp

HEADER = -I ./room \
				-I ./user

OBJDIR =

all : $(NAME)

$(NAME) :
	g++ -std=c++11 -ggdb3 -Wall -Wextra $(HEADER) -c $(SRC)
	g++ -o $(NAME)   *.o -L/home/me/googletest/lib -lgtest -lgmock -lpthread


clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all
