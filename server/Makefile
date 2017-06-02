
NAME = server

SRC =	main.cpp \
			server.cpp \

HEADER =	-I../lib/includes

LIB = -lchat -L../lib

all : $(NAME)

$(NAME) :
	g++ -std=c++11 -ggdb3 -Wall -Wextra $(HEADER) -c $(SRC)
	g++ -o $(NAME)   *.o -lboost_system -lpthread $(LIB)


clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all
