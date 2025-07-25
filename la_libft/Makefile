# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anlamber <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/31 08:54:07 by anlamber          #+#    #+#              #
#    Updated: 2025/04/02 12:50:06 by anlamber         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

CC = gcc
CFLAGS = -Wall -Wextra -Werror

SRC = ft_isalnum.c \
	ft_isprint.c \
	ft_memcmp.c \
	ft_putchar_fd.c \
	ft_split.c \
	ft_strlcat.c \
	ft_strncmp.c \
	ft_substr.c \
	ft_atoi.c \
	ft_isalpha.c \
	ft_itoa.c \
	ft_putendl_fd.c \
	ft_strchr.c  \
	ft_strlcpy.c \
	ft_strnstr.c \
	ft_tolower.c \
	ft_bzero.c \
	ft_isascii.c \
	ft_memcpy.c \
	ft_memmove.c \
	ft_putnbr_fd.c \
	ft_strdup.c \
	ft_strlen.c \
	ft_strrchr.c \
	ft_toupper.c \
	ft_calloc.c \
	ft_isdigit.c \
	ft_memchr.c \
	ft_memset.c \
	ft_putstr_fd.c \
	ft_strjoin.c \
	ft_strmapi.c \
	ft_strtrim.c \
	ft_striteri.c 

GNL_SRCS = le_gnl/get_next_line.c le_gnl/get_next_line_utils.c

PRINTF_SRCS = le_printf/ft_printf.c \
	le_printf/print_char.c \
	le_printf/print_string.c \
	le_printf/print_number.c \
	le_printf/print_unsigned.c \
	le_printf/print_hex.c \
	le_printf/print_pointer.c \

SRCS = $(SRC) $(GNL_SRCS) $(PRINTF_SRCS)

OBJS = $(SRCS:.c=.o)

BONUS =	ft_lstadd_back.c \
	ft_lstadd_front.c \
	ft_lstclear.c \
	ft_lstdelone.c \
	ft_lstiter.c \
	ft_lstlast.c \
	ft_lstmap.c \
	ft_lstnew.c \
	ft_lstsize.c

BONUS_OBJS = $(BONUS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(OBJS) $(BONUS_OBJS)
	ar rcs $(NAME) $(OBJS) $(BONUS_OBJS)
	
clean:
	rm -f $(OBJS) $(BONUS_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re bonus
