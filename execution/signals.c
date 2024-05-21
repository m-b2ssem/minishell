#include "../minishell.h"

sig_atomic_t g_signal = 0;


void herdoc_handler(int signum)
{
    if (signum == SIGINT)
    {
        g_signal = 130;
        ioctl(0, TIOCSTI, "\n");
        //rl_replace_line("", 0);
        rl_on_new_line();
    }
}

void    signal_handler(int signum)
{
    if (signum == SIGINT)
    {
        g_signal = 130;
        write(STDOUT_FILENO, "\n", 1);
        //rl_replace_line("", 0);
        rl_on_new_line();
        rl_redisplay();
    }
}

void sig_ign(void)
{
	signal(SIGINT, SIG_IGN);
	signal(SIGQUIT, SIG_IGN);
}

void	heredoc_signals(void)
{
	signal(SIGINT, herdoc_handler);
	signal(SIGQUIT, SIG_IGN);
}
void	child_signal(void)
{
	signal(SIGINT, SIG_DFL);
	signal(SIGQUIT, SIG_DFL);
}

void	parent_signals(void)
{
	signal(SIGINT, signal_handler);
	signal(SIGQUIT, SIG_IGN);
}
