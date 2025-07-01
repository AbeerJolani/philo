CC = cc
SRC = philo.c utils.c life.c mutex.c threads.c help.c main.c
OBJ := $(SRC:%.c=%.o)
NAME = philo
CFLAGS = -Wall -Wextra -Werror -Iinclude

all: $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
