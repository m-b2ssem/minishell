NAME = test
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = ./libft/libft.a
SRC =	main.c parsing.c tokenizing.c tok_helper.c expansion.c helper.c


OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	@make -C ./libft
	$(CC) $(CFLAGS) $(OBJ) -lreadline  $(LIBFT)  -o $(NAME)


all		: $(NAME)

clean	:
	@rm -f $(OBJ)
	@make -C ./libft clean

fclean	: clean
	@rm -rf $(NAME)
	@make -C ./libft fclean


re		: fclean all
