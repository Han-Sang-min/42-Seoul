# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/16 18:19:21 by sangmhan          #+#    #+#              #
#    Updated: 2023/01/18 09:22:05 by hansangmin       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror -c
NAME 		= libftprintf.a
SOURCES 	= src/ft_printf.c src/PntArgs.c src/PutCharInBuf.c src/PutHexInBuf.c src/PutMemInBuf.c src/PutNbrInBuf.c \
			src/PutSet.c src/PutStrInBuf.c src/PutUnsignedInBuf.c src/Tools.c
OBJECTS 	= $(SOURCES:.c=.o)
INC			= ./include
LIBFTDIR	= ./libft
LIBFTFILE	= libft.a

all: $(NAME) 

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

%.o: %.c
	@$(CC) $(CFLAGS) $< -o $@ -I $(INC)

$(NAME): $(OBJECTS)
	@make -C $(LIBFTDIR)
	@cp $(LIBFTDIR)/$(LIBFTFILE) $(NAME)
	@ar rcs $@ $^

bonus: $(NAME)

clean:
	@make -C $(LIBFTDIR) clean
	@rm -f $(OBJECTS)

fclean:
	@make -C $(LIBFTDIR) fclean
	@rm -f $(NAME)

re: fclean all
