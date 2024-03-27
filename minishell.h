#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <signal.h>
# include <stdio.h>
# include <string.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
#include <sys/fcntl.h>

typedef struct s_commande_line	t_commande_line;
typedef struct s_token			t_token;

struct				s_commande_line
{
	char			*string;
	t_token			*first_token;
	char			**envp;
	char			**argv;
	int				fd_in;
	int				fd_out;
	char			*name_file;
	t_commande_line	*next;
};

typedef enum token
{
	NON,
	ARG,
	BUILTIN,
	OPEN_FILE,
	HERE_DOC,
	LIMITOR,
	CREAT_FILE,
	WRITE_FILE,
	FILE_IN,
	FILE_OUT,
	FILE_OUT_OVER,
	ENDS
}				t_e_token;

struct			s_token
{
	char		*str;
	t_e_token	type;
	bool		expanded;
	t_token		*next;
};

void	redirections(char *cml);
int		builtin_pwd();
int		cd(char *new_path);

#endif