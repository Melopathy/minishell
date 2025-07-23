
#include "minishell.h"

static int is_cmd_token(int type)
{
    return (type == TOKEN_WORD
         || type == TOKEN_REDIR_IN
         || type == TOKEN_REDIR_OUT
         || type == TOKEN_REDIR_APPEND
         || type == TOKEN_REDIR_HEREDOC);
}

static t_cmd *cleanup_cmd(t_cmd *cmd, char **args, int argc)
{
	free_args(args, argc);
	free(cmd);
	return (NULL);
}

static int	set_error(t_parser *p)
{
	p->error = 1;
	p->error_msg = ft_strdup("Syntax error");
	return (1);
}

static int	handle_word(t_parser *p, char **args, int *argc)
{
	args[*argc] = ft_strdup(p->current->value);
	if (!args[*argc])
		return (1);
	(*argc)++;
	p->current = p->current->next;
	return (0);
}

static int	handle_input(t_parser *p, t_cmd *cmd)
{
	p->current = p->current->next;
	if (!p->current || p->current->type != TOKEN_WORD)
		return (set_error(p));
	free(cmd->input_file);
	cmd->input_file = ft_strdup(p->current->value);
	if (!cmd->input_file)
		return (1);
	p->current = p->current->next;
	return (0);
}

static int	handle_output(t_parser *p, t_cmd *cmd, bool append)
{
	p->current = p->current->next;
	if (!p->current || p->current->type != TOKEN_WORD)
		return (set_error(p));
	free(cmd->output_file);
	cmd->output_file = ft_strdup(p->current->value);
	if (!cmd->output_file)
		return (1);
	cmd->append_output = append;
	p->current = p->current->next;
	return (0);
}

static int	handle_heredoc_parse(t_parser *p, t_cmd *cmd)
{
	p->current = p->current->next;
	if (!p->current || p->current->type != TOKEN_WORD)
		return (set_error(p));
	free(cmd->heredoc_delimiter);
	cmd->heredoc_delimiter = ft_strdup(p->current->value);
	if (!cmd->heredoc_delimiter)
		return (1);
	cmd->is_heredoc = 1;
	p->current = p->current->next;
	return (0);
}

static int	process_token(t_parser *p, t_cmd *cmd, char **args, int *argc)
{
	int err;

	err = 0;
	if (p->current->type == TOKEN_WORD)
		err = handle_word(p, args, argc);
	else if (p->current->type == TOKEN_REDIR_IN)
		err = handle_input(p, cmd);
	else if (p->current->type == TOKEN_REDIR_OUT)
		err = handle_output(p, cmd, 0);
	else if (p->current->type == TOKEN_REDIR_APPEND)
		err = handle_output(p, cmd, 1);
	else if (p->current->type == TOKEN_REDIR_HEREDOC)
		err = handle_heredoc_parse(p, cmd);
	return (err);
}

t_cmd	*parse_simple_cmd(t_parser *p)
{
	t_cmd	*cmd;
	char	**args;
	int		argc;

	cmd = create_cmd();
	if (!cmd)
		return (NULL);
	args = malloc(sizeof(char *) * 256);
	if (!args)
		return (free(cmd), NULL);
	argc = 0;
	while (p->current && is_cmd_token(p->current->type))
	{
		if (process_token(p, cmd, args, &argc))
			return (cleanup_cmd(cmd, args, argc));
	}
	args[argc] = NULL;
	cmd->args = args;
	cmd->argc = argc;
	return (cmd);
}