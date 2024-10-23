NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = -lpthread

SRC = \
    ./src/main.c \
    ./src/inits.c \
    ./src/utils.c \
    ./src/philo.c \
    ./src/routine.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAGS) $(LIB) -o $(NAME)

all: $(NAME)

clean:
	@rm -rf $(OBJ)

fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re

