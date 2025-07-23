#include "minishell.h"


char *get_env_path(char **envp)
{
	int i;

	i = 0;
	while (envp[i])
	{
		if (ft_strnstr(envp[i], "PATH=", 5) != NULL)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char *search_in_paths(char *cmd, char **paths)
{
	char *part_path;
	char *part_path_cmd;
	int i;

	i = 0;
	while (paths[i])
	{
		part_path = ft_strjoin(paths[i], "/");
		if (!part_path)
			return (NULL);
		part_path_cmd = ft_strjoin(part_path, cmd);
		free(part_path);
		if (!part_path_cmd)
			return (NULL);
		if (access(part_path_cmd, F_OK) == 0)
			return (part_path_cmd);
		free(part_path_cmd);
		i++;
	}
	return (NULL);
}

char *find_path(char *cmd, char **envp)
{
	char **paths;
	char *env_path;
	char *result;

	if (!cmd || cmd[0] == '\0')
		return (NULL);
	if (ft_strchr(cmd, '/') && access(cmd, F_OK) == 0)
		return (ft_strdup(cmd));
	
	env_path = get_env_path(envp);
	if (!env_path)
		return (NULL);
	
	paths = ft_split(env_path, ':');
	if (!paths)
		return (NULL);
	
	result = search_in_paths(cmd, paths);
	free_tab(paths);
	return (result);
}


void execute_pipeline(t_cmd *cmd_list, t_exec *ex)
{
	t_cmd *current;
	int is_first_cmd;
	int has_pipe;
	
	if (!cmd_list)
		return;
	
	current = cmd_list;
	is_first_cmd = 1;
	ex->prev_pipe = -1;
	
	while (current)
	{
		has_pipe = (current->next != NULL);
		
		if (has_pipe && pipe(ex->pipefd) == -1)
		{
			perror("pipe");
			return;
		}
		if (is_first_cmd && !has_pipe && is_builtin(current->args[0]) && 
		    !current->input_file && !current->output_file && !current->is_heredoc)
		{
			execute_builtin(current, ex);
			break;
		}
		
		fork_and_exec(ex, current, is_first_cmd, has_pipe);		
		current = current->next;
		is_first_cmd = 0;
	}
	wait_child_process();
}

void parse_input(char *input, char **envp)
{
	t_parser *parser;
	t_cmd *cmd_list;
	t_exec exec;
	
	if (!input || !*input)
		return;
	
	parser = init_parser(input);
	if (!parser)
		return;
	
	cmd_list = parse_cmd_line(parser);
	if (!cmd_list)
	{
		if (parser->error && parser->error_msg)
		{
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(parser->error_msg, 2);
			ft_putstr_fd("\n", 2);
		}
		free_parser(parser);
		return;
	}
	
	exec.envp = envp;
	exec.prev_pipe = -1;
	
	execute_pipeline(cmd_list, &exec);
	
	free_cmd(cmd_list);
	free_parser(parser);
}
