NAME = libchat.a

SRC = ./srcs/*.cpp

OBJDIR =

all : $(NAME)

$(NAME) :
	g++ -std=c++11 -c $(SRC) -Iincludes -lpthread
	ar rvs $(NAME) *.o

clean :
	rm -f *.o

fclean : clean
	rm -f $(NAME)

re : fclean all
