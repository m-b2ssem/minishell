# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: amirfatt <amirfatt@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/05/26 17:57:51 by amirfatt          #+#    #+#              #
#    Updated: 2024/05/26 21:21:55 by amirfatt         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = ./libft/libft.a
SRC =	main.c redirections/redirections.c redirections/heredoc.c  redirections/her_util.c\
		builtin/builtin_pwd.c builtin/builtin_cd.c builtin/builtin_echo.c builtin/builtin_export.c builtin/builtin_env.c \
		builtin/builtin_unset.c builtin/builtin_exit.c builtin/export_utils.c\
		execution/execuation.c execution/piping.c execution/signals.c execution/utils_1.c execution/utils_2.c execution/utils_3.c execution/utils_4.c\
		environment/env_list.c debug.c\
		parsing/start_parse.c parsing/split_cmd.c parsing/create_array_exec.c \
		parsing/expansion.c parsing/free_shell.c parsing/expansion_helper.c parsing/remove_blanks.c\
		parsing/init_arguments.c parsing/init_tokens.c parsing/quote_joining.c parsing/quote_joining_util_1.c parsing/quote_joining_util_2.c parsing/quote_join_helper.c parsing/redir_relations.c \
		parsing/redirection_spell_check.c parsing/token_type.c parsing/tokenize_arguments.c parsing/tokenize_helper.c parsing/tokenize_helper_two.c \
		parsing/trim_quotes.c parsing/echo_edgecase.c parsing/builtin_edgecases.c parsing/string_utils.c builtin/export_utils_2.c\
		parsing/expansion_utils_3.c parsing/expansion_utils_2.c parsing/expansion_utils.c parsing/expansion_utils_4.c parsing/start_parse_checker.c\

SUP = readline_suppression.supp

OBJ = $(SRC:.c=.o)

$(NAME) : $(OBJ)
	@make -C ./libft
	$(CC) $(CFLAGS) $(OBJ) -lreadline $(LIBFT) -o $(NAME)


all		: $(NAME)

clean	:
	@rm -f $(OBJ)
	@make -C ./libft clean

fclean	: clean
	@rm -rf $(NAME)
	@make -C ./libft fclean

re		: fclean all

debug: all
	valgrind -s --leak-check=full --show-leak-kinds=all --trace-children=yes --track-fds=yes --suppressions=$(SUP) ./minishell
