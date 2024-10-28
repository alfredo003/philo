# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: achivela <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/28 12:01:45 by achivela          #+#    #+#              #
#    Updated: 2024/10/28 12:01:47 by achivela         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = philo

CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC = ./src/main.c \
      ./src/validation.c \
      ./src/start_phi.c \
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

