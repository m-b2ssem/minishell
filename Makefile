NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT =	library/libft/libft.a
GETNEXTLINE = 	library/get_next_line/getnextline.a
SRC =	main.c redirections/redirections.c redirections/heredoc.c \
		builtin/builtin_pwd.c builtin/builtin_cd.c builtin/builtin_echo.c builtin/builtin_export.c builtin/builtin_env.c \
		builtin/builtin_unset.c builtin/builtin_exit.c builtin/export_utils.c\
		execution/execuation.c execution/piping.c execution/signals.c execution/utils_1.c execution/utils_2.c execution/utils_3.c execution/utils_4.c\
		environment/env_list.c \
		parsing/start_parse.c parsing/start_parse_checker.c parsing/split_cmd.c parsing/create_array_exec.c parsing/debug_helper.c \
		parsing/expansion.c parsing/free_shell.c parsing/expansion_helper.c \
		parsing/init_arguments.c parsing/init_tokens.c parsing/quote_joining.c parsing/quote_joining_util_1.c parsing/quote_joining_util_2.c parsing/quote_join_helper.c parsing/redir_relations.c \
		parsing/redirection_spell_check.c parsing/token_type.c parsing/tokenize_arguments.c parsing/tokenize_helper.c parsing/tokenize_helper_two.c \
		parsing/trim_quotes.c parsing/echo_edgecase.c parsing/handle_backlash.c parsing/builtin_edgecases.c\

SUP = readline_suppression.supp

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	@make -C ./library/libft
	@make -C ./library/get_next_line
	$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFT) $(GETNEXTLINE)  -o $(NAME)


all		: $(NAME)

clean	:
	@rm -f $(OBJ)
	@make -C ./library/libft clean

fclean	: clean
	@rm -rf $(NAME)
	@make -C ./library/libft fclean
	@make -C ./library/get_next_line fclean

re		: fclean all

debug: re
	valgrind -s --leak-check=full --show-leak-kinds=all --suppressions=$(SUP) ./minishell
