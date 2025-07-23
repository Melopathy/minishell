# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anlamber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/02 16:20:13 by anlamber          #+#    #+#              #
#    Updated: 2025/04/02 16:20:23 by anlamber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_printf.c \
	print_char.c \
	print_string.c \
	print_number.c \
	print_unsigned.c \
	print_hex.c \
	print_pointer.c \

OBJS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.c ft_printf.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
