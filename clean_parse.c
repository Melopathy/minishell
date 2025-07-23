#include "minishell.h"

t_parser *init_parser(char *input)
{
	t_parser *parse;
	
	parse = malloc(sizeof(t_parser));
	if (!parse)
		return (NULL);
	parse->input = ft_strdup(input);
	if (!parse->input)
	{
		free(parse);
		return (NULL);
	}
	parse->pos = 0;
	parse->tokens = NULL;
	parse->current = NULL;
	parse->error = 0;
	parse->error_msg = NULL;
	return (parse);
}

t_token *create_token(t_tk_type type, char *value)
{
	t_token *token;
	
	token = malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->type = type;
	if (value)
		token->value = ft_strdup(value);
	else
		token->value = NULL;
	token->next = NULL;
	return (token);
}

void add_token(t_token **head, t_token *new_token)
{
	t_token *current;
	
	if (!*head)
	{
		*head = new_token;
		return;
	}
	current = *head;
	while (current->next)
		current = current->next;
	current->next = new_token;
}

void skip_whitespace(t_parser *parse)
{
	while (parse->input[parse->pos] && 
		(parse->input[parse->pos] == ' ' || 
		 parse->input[parse->pos] == '\t' || 
		 parse->input[parse->pos] == '\n'))
		parse->pos++;
}

char *extract_word(t_parser *parse)
{
	int start;
	int len;
	char *word;
	
	start = parse->pos;
	while (parse->input[parse->pos] && 
		   parse->input[parse->pos] != ' ' && 
		   parse->input[parse->pos] != '\t' && 
		   parse->input[parse->pos] != '\n' && 
		   parse->input[parse->pos] != '|' && 
		   parse->input[parse->pos] != '<' && 
		   parse->input[parse->pos] != '>' && 
		   parse->input[parse->pos] != '&' && 
		   parse->input[parse->pos] != ';' && 
		   parse->input[parse->pos] != '(' && 
		   parse->input[parse->pos] != ')')
		parse->pos++;
	len = parse->pos - start;
	if (len == 0)
		return (NULL);
	word = malloc(len + 1);
	if (!word)
		return (NULL);
	ft_strlcpy(word, &parse->input[start], len + 1);
	return (word);
}

t_cmd *create_cmd(void)
{
	t_cmd *cmd;
	
	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->args = NULL;
	cmd->argc = 0;
	cmd->input_file = NULL;
	cmd->output_file = NULL;
	cmd->append_output = 0;
	cmd->is_heredoc = 0;
	cmd->heredoc_delimiter = NULL;
	cmd->next = NULL;
	return (cmd);
}

t_cmd	*parse_pipeline(t_parser *parse)
{
	t_cmd *left;
	
	left = parse_simple_cmd(parse);
	if (!left || parse->error)
		return (left);
	
	while (parse->current && parse->current->type == TOKEN_PIPE)
	{
		parse->current = parse->current->next;
		t_cmd *right = parse_simple_cmd(parse);
		if (!right || parse->error)
		{
			free_cmd(left);
			return (NULL);
		}
		t_cmd *current = left;
		while (current->next)
			current = current->next;
		current->next = right;
	}
	return (left);
}

t_cmd	*parse_cmd_line(t_parser *parse)
{
	parse->tokens = tokenize(parse);
	parse->current = parse->tokens;
	if (parse->error)
		return (NULL);
	return (parse_pipeline(parse));
}