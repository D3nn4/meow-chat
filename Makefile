NAME = meowChat

SRC =	main.cpp \
			./room/room_manager.cpp \
			./room/room_manager.t.cpp \
			./user/user_manager.cpp \
			./user/user_manager.t.cpp

HEADER =-I/home/me/googletest/include \
				-I ./room \
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
