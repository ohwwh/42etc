# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ohw <ohw@student.42seoul.kr>               +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/23 02:36:10 by ohw               #+#    #+#              #
#    Updated: 2022/04/28 12:44:39 by hoh              ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
AR = ar
ARFLAGS = -rc
NAME=libohw.a
LIBFTDIR=./srcs/libft/
GNLDIR=./srcs/get_next_line/
PRINTFDIR=./srcs/ft_printf/
INCSDIR=./includes/

LIBFT_NAME= ft_isalpha.c ft_isdigit.c ft_isalnum.c\
	ft_isascii.c ft_isprint.c ft_strlen.c\
	ft_memset.c ft_bzero.c ft_memcpy.c\
	ft_memmove.c ft_strlcpy.c ft_strlcat.c\
	ft_toupper.c ft_tolower.c ft_strchr.c\
	ft_strrchr.c ft_strncmp.c ft_memchr.c\
	ft_memcmp.c ft_strnstr.c ft_atoi.c\
	ft_calloc.c ft_strdup.c\
	ft_substr.c ft_strjoin.c ft_strtrim.c\
	ft_split.c ft_itoa.c ft_itoa_base.c ft_strmapi.c\
	ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c\
	ft_putendl_fd.c ft_putnbr_fd.c\
	ft_lstnew.c ft_lstadd_front.c ft_lstsize.c\
	ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c\
	ft_lstclear.c ft_lstiter.c ft_lstmap.c
GNL_NAME=get_next_line.c get_next_line_utils.c
PRINTF_NAME=ft_checkdigit_address.c ft_checkdigit.c\
	ft_printf_nbr.c ft_printf_non_nbr.c\
	ft_putaddress_fd.c ft_putnbr_base_fd.c\
	ft_printf.c
PRINTF_BONUS_NAME=ft_checkdigit_address.c ft_checkdigit.c\
	ft_printf_nbr.c ft_printf_non_nbr.c\
	ft_putaddress_fd.c ft_putaddress_precision.c\
	ft_putnbr_base_fd.c ft_putnbr_base_precision.c\
	ft_putstr_precision.c ft_printf.c\
	ft_strtol_util.c ft_strtol.c
LIBFT_SRCS=$(addprefix $(LIBFTDIR), $(LIBFT_NAME))
GNL_SRCS=$(addprefix $(GNLDIR), $(GNL_NAME))
PRINTF_SRCS=$(addprefix $(PRINTFDIR), $(PRINTF_NAME))

LIBFT_OBJS=${LIBFT_SRCS:.c=.o}
GNL_OBJS=${GNL_SRCS:.c=.o}
PRINTF_OBJS=${PRINTF_SRCS:.c=.o}

.PHONY: all clean fclean re libft get_next_line ft_printf

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@ -I$(INCSDIR)
	$(AR) $(ARFLAGS) $(NAME) $@

all : $(NAME)

$(NAME): libft get_next_line ft_printf

libft: $(LIBFT_OBJS)
get_next_line: $(GNL_OBJS)
ft_printf: $(PRINTF_OBJS)

clean:
	rm -f $(LIBFT_OBJS) $(GNL_OBJS) $(PRINTF_OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
