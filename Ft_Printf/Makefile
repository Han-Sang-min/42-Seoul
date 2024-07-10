# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/16 18:19:21 by sangmhan          #+#    #+#              #
#    Updated: 2022/07/28 20:37:39 by hansangmin       ###   ########.fr        #
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

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@ -I $(INC)

$(NAME): $(OBJECTS)
	make -C $(LIBFTDIR)
	cp $(LIBFTDIR)/$(LIBFTFILE) $(NAME)
	ar rcs $@ $^

bonus: $(NAME)

clean:
	make -C $(LIBFTDIR) clean
	rm -f $(OBJECTS)

fclean: clean
	make -C $(LIBFTDIR) fclean
	rm -f $(NAME)

re: fclean all
