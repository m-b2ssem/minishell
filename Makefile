NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = ./libft/libft.a
SRC =	main.c redirections/redirections.c redirections/heredoc.c builtin/builtin_pwd.c builtin/builtin_cd.c \
		builtin/builtin_echo.c builtin/builtin_export.c builtin/builtin_env.c builtin/builtin_unset.c builtin/builtin_exit.c \
		execution/execuation.c execution/piping.c execution/signals.c execution/utils_1.c environment/env_list.c \
		parsing/free_shell.c parsing/ft_helper.c parsing/init_arguments.c parsing/init_tokens.c parsing/quote_handling.c \
		parsing/redirection_spell_check.c parsing/REV_expansion.c parsing/REV_helper.c parsing/REV_organise.c parsing/REV_tok_helper.c \
		parsing/split_cmd.c parsing/start_parse.c parsing/token_type.c parsing/tokenize_arguments.c parsing/tokenize_helper_two.c \
		parsing/tokenize_helper.c

SUP = readline_suppression.supp

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

debug:
	valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=$(SUP) ./minishell
