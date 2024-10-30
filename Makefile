NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ./src/main.c \
      ./src/validation.c \
      ./src/init.c \
      ./src/routine.c \
      ./src/utils.c \


OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(CFLAGS) -o $(NAME) $(OBJ)

%.o: %.c 
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

