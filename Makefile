NAME = minishell

SRCS = main.c \
	parsing.c \
	clean_parse.c \
	fork.c \
	builtins.c \
	string_utils.c \
	memory_utils.c \
	tokenize.c \
	parse_simple_cmd.c

OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -g
INCLUDES = -I./la_libft
READLINE = -lreadline

LIBS = -L./la_libft -lft
LIBFT_DIR = ./la_libft

all: la_libft $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJS) $(LIBS) $(READLINE)

%.o: %.c minishell.h
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@
	
libft:
	@make -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	@make clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	@make fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean libft re