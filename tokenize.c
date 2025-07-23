#include "minishell.h"

static t_token	*create_pipe_token(t_parser *p)
{
	t_token	*tok;
	char	*val;

	if (p->input[p->pos + 1] == '|')
	{
		val = ft_strdup("||");
		p->pos += 2;
		tok = create_token(TOKEN_OR, val);
	}
	else
	{
		val = ft_strdup("|");
		p->pos++;
		tok = create_token(TOKEN_PIPE, val);
	}
	if (!val || !tok)
	{
		free(val);
		return (NULL);
	}
	return (tok);
}

static t_token	*create_input_token(t_parser *p)
{
	t_token	*tok;
	char	*val;

	if (p->input[p->pos + 1] == '<')
	{
		val = ft_strdup("<<");
		p->pos += 2;
		tok = create_token(TOKEN_REDIR_HEREDOC, val);
	}
	else
	{
		val = ft_strdup("<");
		p->pos++;
		tok = create_token(TOKEN_REDIR_IN, val);
	}
	if (!val || !tok)
	{
		free(val);
		return (NULL);
	}
	return (tok);
}

static t_token	*create_output_token(t_parser *p)
{
	t_token	*tok;
	char	*val;

	if (p->input[p->pos + 1] == '>')
	{
		val = ft_strdup(">>");
		p->pos += 2;
		tok = create_token(TOKEN_REDIR_APPEND, val);
	}
	else
	{
		val = ft_strdup(">");
		p->pos++;
		tok = create_token(TOKEN_REDIR_OUT, val);
	}
	if (!val || !tok)
	{
		free(val);
		return (NULL);
	}
	return (tok);
}

static t_token	*create_and_token(t_parser *p)
{
	t_token *tok;
	char    *val;

	if (p->input[p->pos + 1] == '&')
	{
		val = ft_strdup("&&");
		p->pos += 2;
		tok = create_token(TOKEN_AND, val);
		if (!val || !tok)
		{
			free(val);
			return (NULL);
		}
		return (tok);
	}
	p->error = true;
	p->error_msg = ft_strdup("Unexpected character '&'");
	return (NULL);
}

static t_token	*create_simple_token(t_parser *p, int type, const char *s)
{
	t_token	*tok;
	char	*val;

	val = ft_strdup(s);
	if (!val)
		return (NULL);
	tok = create_token(type, val);
	if (!tok)
		free(val);
	else
		p->pos++;
	return (tok);
}

static t_token	*create_word_token(t_parser *p)
{
	char	*word;
	t_token	*tok;

	word = extract_word(p);
	if (!word)
		return (NULL);
	tok = create_token(TOKEN_WORD, word);
	if (!tok)
		free(word);
	return (tok);
}

static t_token	*next_token(t_parser *p)
{
    char c = p->input[p->pos];

	if (c == '|')
		return (create_pipe_token(p));
	if (c == '<')
		return (create_input_token(p));
	if (c == '>')
		return (create_output_token(p));
	if (c == '&')
		return (create_and_token(p));
	if (c == ';')
		return (create_simple_token(p, TOKEN_SEMICOLON, ";"));
	if (c == '(')
		return (create_simple_token(p, TOKEN_LPAREN, "("));
	if (c == ')')
		return (create_simple_token(p, TOKEN_RPAREN, ")"));
	return (create_word_token(p));
}

t_token	*tokenize(t_parser *p)
{
	t_token *head = NULL;
	t_token *tok;

	while (p->input[p->pos] && !p->error)
	{
		skip_whitespace(p);
		if (!p->input[p->pos] || p->error)
			break;
		tok = next_token(p);
		if (p->error && !tok)
			return (head);
		if (tok)
			add_token(&head, tok);
	}
	add_token(&head, create_token(TOKEN_EOF, NULL));
	return (head);
}
