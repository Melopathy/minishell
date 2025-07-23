#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <stddef.h>
# include <string.h>
# include <unistd.h>
# include <signal.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "libft/libft.h"

typedef enum e_tk_type {
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_IN,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_APPEND,
	TOKEN_REDIR_HEREDOC,
	TOKEN_AND,
	TOKEN_OR,
	TOKEN_SEMICOLON,
	TOKEN_LPAREN,
	TOKEN_RPAREN,
	TOKEN_EOF,
	TOKEN_ERROR,
} t_tk_type;

typedef struct s_token {
    t_tk_type type;
    char *value;
    struct s_token *next;
} t_token;

typedef struct s_cmd {
    char **args;
    int argc;
    char *input_file;
    char *output_file;
    bool append_output;
    bool is_heredoc;
    char *heredoc_delimiter;
    struct s_cmd *next;
} t_cmd;

typedef struct s_parser {
    t_token *tokens;
    t_token *current;
    char *input;
    int pos;
    bool error;
    char *error_msg;
} t_parser;

typedef struct s_exec {
    int prev_pipe;
    int pipefd[2];
    char **envp;
} t_exec;

/* Main */
void setup_sigaction(void);
void handle_sigint(int sig);

/* Parsing */
void parse_input(char *input, char **envp);
char *find_path(char *cmd, char **envp);
char *get_env_path(char **envp);
char *search_in_paths(char *cmd, char **paths);
void execute_pipeline(t_cmd *cmd_list, t_exec *ex);

/* Clean Parse */
t_parser *init_parser(char *input);
t_token *create_token(t_tk_type type, char *value);
void add_token(t_token **head, t_token *new_token);
void skip_whitespace(t_parser *parse);
char *extract_word(t_parser *parse);
t_cmd *create_cmd(void);
t_cmd *parse_pipeline(t_parser *parse);
t_cmd *parse_cmd_line(t_parser *parse);

/* Fork and Exec */
void execute_command(t_cmd *cmd, t_exec *ex);
int	handle_heredoc(char *delimiter);
void child_process(t_exec *ex, t_cmd *cmd, int f_cmd, int has_pipe);
void parent_process(t_exec *ex, int f_cmd, int has_pipe);
int fork_and_exec(t_exec *ex, t_cmd *cmd, int is_first_cmd, int has_pipe);
int wait_child_process(void);

/* Builtins */
int is_builtin(char *cmd);
int execute_builtin(t_cmd *cmd, t_exec *ex);
int builtin_cd(t_cmd *cmd);
int builtin_echo(t_cmd *cmd);
int builtin_env(t_exec *ex);
int builtin_exit(t_cmd *cmd);
int builtin_pwd(void);

/* Parse simple commands */
t_cmd	*parse_simple_cmd(t_parser *p);

/* Tokenize */
t_token *tokenize(t_parser *p);

/* String_utils */
int	ft_strcmp(const char *s1, const char *s2);

/* Memory_utils */
void free_args(char **args, int argc);
void free_tab(char **tab);
void free_tokens(t_token *tokens);
void free_cmd(t_cmd *cmd);
void free_parser(t_parser *parse);

#endif