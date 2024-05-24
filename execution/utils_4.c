#include "../minishell.h"

extern int	g_signal;

void	herdoc_handler(int signum)
{
	if (signum == SIGINT)
	{
		g_signal = 130;
		ioctl(0, TIOCSTI, "\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	printf_error(char *str)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(": command not found\n", 2);
}