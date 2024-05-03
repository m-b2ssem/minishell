NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
LIBFT = ./libft/libft.a
SRC =	main.c redirections/redirections.c redirections/heredoc.c builtin/builtin_pwd.c builtin/builtin_cd.c \
		builtin/builtin_echo.c builtin/builtin_export.c builtin/builtin_env.c builtin/builtin_unset.c builtin/builtin_exit.c\
		execution/execuation.c execution/piping.c execution/utils_1.c parsing/pars_idea.c 


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
