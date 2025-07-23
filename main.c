#include "minishell.h"

//Might need to add some Error Checking and test

/*Error a Check:
minishell> ls |wc -l
==35810== Warning: invalid file descriptor -1 in syscall close()
12
=>prob caused by else ex->prev_pipe = -1
so either always check before closing
if (fd >= 0)
	close(fd);
or check
if (ex->prev_pipe != -1)
	close(ex->prev_pipe);
*/

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putchar_fd('\n', 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
}

void	setup_sigaction(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	signal(SIGQUIT, SIG_IGN);
}

int	main(int argc, char **argv, char **envp)
{
	char	*input;

	(void)argc;
	(void)argv;
	setup_sigaction();
	while (1)
	{
		input = readline("\1\033[1;33m\2minishell\1\033[0m\2> ");
		if (input == NULL)
		{
			rl_on_new_line();
			printf("exit\n");
			break ;
		}
		if (*input)
		{
			add_history(input);
			parse_input(input, envp);
		}
		free(input);
	}
	rl_clear_history();
	return (0);
}
