NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
SRC =	main.c


OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ) $(M_OBJ)
	@make -C ./libft
	$(CC) $(CFLAGS) $(OBJ)  $(LIBFT)  -o $(NAME)


all		: $(NAME)

clean	:
	@rm -f $(OBJ)
	@make -C ./libft clean

fclean	: clean
	@rm -rf $(NAME) $(BONUS)
	@make -C ./libft fclean


re		: fclean all