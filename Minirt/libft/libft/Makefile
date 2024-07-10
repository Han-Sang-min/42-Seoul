# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/16 18:19:21 by sangmhan          #+#    #+#              #
#    Updated: 2023/01/18 09:21:13 by hansangmin       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc
CFLAGS = -Wall -Wextra -Werror -c
NAME = libft.a
SRCS = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isspace.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c\
 ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c ft_tolower.c ft_strlcat.c\
 ft_calloc.c ft_strdup.c ft_atoi.c ft_toupper.c ft_strrchr.c ft_strcat.c ft_strchr.c ft_substr.c ft_strjoin.c ft_strtrim.c\
 ft_split.c ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_striteri.c get_next_line.c\
 ft_strcmp.c
SRCS_B =  ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c

OBJECTS = $(SRCS:.c=.o)
OBJECTS_B = $(SRCS_B:.c=.o)

# Colors
DEF_COLOR = \033[0;39m
GRAY = \033[0;90m
RED = \033[0;91m
GREEN = \033[0;92m
YELLOW = \033[0;93m
BLUE = \033[0;94m
MAGENTA = \033[0;95m
CYAN = \033[0;96m
WHITE = \033[0;97m

ifdef WITH_BONUS
	OBJ_FILES = $(OBJECTS) $(OBJECTS_B)
else
	OBJ_FILES = $(OBJECTS)
endif

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I .

$(NAME) : $(OBJ_FILES)
	@ar rcus $@ $^

bonus :
	@make WITH_BONUS=1 all

clean :
	@rm -f $(OBJ_FILES)

fclean :
	@rm -f $(NAME)

re : fclean all

.PHONY: all bonus clean fclean re