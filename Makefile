
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/03 11:48:43 by amirfatt          #+#    #+#              #
#    Updated: 2023/12/05 15:32:34 by amirfatt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= minishell
CC= cc
FLAGS= -g
#LAGS= -g -Wall -Wextra -Werror

INCLUDE= -I includes
LIBFT= cd libft && make

SRC=  env_var.c


OBJECTS= $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(LIBFT)
	$(CC) $(OBJECTS) -o $(NAME) libft/libft.a
	@echo "------------GAME Creation------------"

%.o: %.c
	$(CC) $(INCLUDE) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS)
	cd libft && make clean
	@echo "------------Object files deletion------------"

fclean: clean
	rm -f $(NAME)
	cd libft && make fclean
	@echo "------------Exec files deletion------------"

re: fclean all

.PHONY: all clean fclean re
