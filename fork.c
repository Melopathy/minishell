#include "minishell.h"

//make dedicated exit fct
void	execute_command(t_cmd *cmd, t_exec *ex)
{
	char	*path;

	if (!cmd || !cmd->args || !cmd->args[0])
		exit(1);
	if (is_builtin(cmd->args[0]))
	{
		exit(execute_builtin(cmd, ex));
	}
	path = find_path(cmd->args[0], ex->envp);
	if (!path)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	if (execve(path, cmd->args, ex->envp) == -1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(cmd->args[0], 2);
		ft_putstr_fd(": execution failed\n", 2);
		free(path);
		exit(126);
	}
	free(path);
}

//Weird ctrl+c & ctrl+d
//Check signals and fix
//For ctrl+d => if (line == NULL) return "\n"
//AND EOF or 'EOF' to handle var MAYBE
int	handle_heredoc(char *delimiter)
{
	int		pipefd[2];
	char	*line;
	int		delimiter_len;

	if (pipe(pipefd) == -1)
	{
		perror("pipe");
		return (-1);
	}
	delimiter_len = ft_strlen(delimiter);
	ft_putstr_fd("heredoc> ", 1);
	line = get_next_line(STDIN_FILENO);
	while (line != NULL)
	{
		if (line[ft_strlen(line) - 1] == '\n')
			line[ft_strlen(line) - 1] = '\0';
		if (ft_strncmp(line, delimiter, delimiter_len) == 0
			&& line[delimiter_len] == '\0')
		{
			free(line);
			break ;
		}
		write(pipefd[1], line, ft_strlen(line));
		write(pipefd[1], "\n", 1);
		free(line);
		ft_putstr_fd("heredoc> ", 1);
		line = get_next_line(STDIN_FILENO);
	}
	close(pipefd[1]);
	return (pipefd[0]);
}

//Child process with handle_heredoc + file input + file output
//Check to close unused pipes
//Check error handling
void	child_process(t_exec *ex, t_cmd *cmd, int f_cmd, int has_pipe)
{
	int	heredoc_fd;
	int	input_fd;
	int	op_fd;

	if (cmd->is_heredoc)
	{
		heredoc_fd = handle_heredoc(cmd->heredoc_delimiter);
		if (heredoc_fd == -1)
			exit(1);
		dup2(heredoc_fd, STDIN_FILENO);
		close(heredoc_fd);
	}
	else if (cmd->input_file)
	{
		input_fd = open(cmd->input_file, O_RDONLY);
		if (input_fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->input_file, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(1);
		}
		dup2(input_fd, STDIN_FILENO);
		close(input_fd);
	}
	else if (!f_cmd)
	{
		dup2(ex->prev_pipe, STDIN_FILENO);
		close(ex->prev_pipe);
	}
	if (cmd->output_file)
	{
		if (cmd->append_output)
			op_fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			op_fd = open(cmd->output_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (op_fd == -1)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd->output_file, 2);
			ft_putstr_fd(": Permission denied\n", 2);
			exit(1);
		}
		dup2(op_fd, STDOUT_FILENO);
		close(op_fd);
	}
	else if (has_pipe)
	{
		close(ex->pipefd[0]);
		dup2(ex->pipefd[1], STDOUT_FILENO);
		close(ex->pipefd[1]);
	}
	execute_command(cmd, ex);
}

//Check prev_pipe just in case
void	parent_process(t_exec *ex, int f_cmd, int has_pipe)
{
	if (!f_cmd)
		close(ex->prev_pipe);
	if (has_pipe)
	{
		close(ex->pipefd[1]);
		ex->prev_pipe = ex->pipefd[0];
	}
	else
		ex->prev_pipe = -1;
}

//Fork
//Error Check
//Child process reset signals for normal behavior, default behavior is inherited by both the shell and the child process
//so ctrl+c terminate the process, but fuck it shouldnt work so just check the signals idk
//No wait_child_process here, so check if it works properly in exec_pipeline
int	fork_and_exec(t_exec *ex, t_cmd *cmd, int is_first_cmd, int has_pipe)
{
	pid_t	pid;

	pid = fork();
	if (pid == -1)
	{
		ft_putstr_fd("Minishell: fork failed\n", 2);
		return (1);
	}
	else if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		//signal(SIGQUIT, SIG_DFL);
		child_process(ex, cmd, is_first_cmd, has_pipe);
	}
	else
		parent_process(ex, is_first_cmd, has_pipe);
	return (0);
}

//$? store the exit status of the last executed cmd
//Need to store it somewhere to support $?
int	wait_child_process(void)
{
	int	last_status;
	int	new_status;

	last_status = 0;
	while (wait(&new_status) > 0)
	{
		if (WIFEXITED(new_status))
			last_status = WEXITSTATUS(new_status);
		else if (WIFSIGNALED(new_status))
		{
			last_status = 128 + WTERMSIG(new_status);
			if (last_status == 130)
				ft_putchar_fd('\n', 1);
		}
	}
	return (last_status);
}
