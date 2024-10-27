
NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror
LIB = -lpthread 

SRC = \
    ./src/main.c \
    ./src/init.c \
    ./src/philo_routine.c \
    ./src/monitor.c \
    ./src/monitor_checks.c \
    ./src/utils.c 

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
