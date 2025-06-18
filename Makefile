CC = cc
SRC = philo.c main.c
OBJ := $(SRC:%.c=%.o)
NAME = prog
CFLAGS = -Wall -Wextra -Werror

all: $(NAME)

$(NAME):	$(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY: all clean fclean re
