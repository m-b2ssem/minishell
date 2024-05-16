#include "../minishell.h"

sig_atomic_t g_signal = 0;

void sig_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void    signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        g_signal = 130;
        write(STDOUT_FILENO, "\n", 1);
        rl_on_new_line();
        //rl_replace_line("", 0);
        rl_redisplay();
    }
}

void	parent_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}

void	child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL); // check this line
}