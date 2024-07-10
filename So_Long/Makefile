# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/03 15:07:14 by hansangmin        #+#    #+#              #
#    Updated: 2022/10/02 20:52:32 by hansangmin       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
NAME 		= so_long
SRC			= ./src
SOURCES 	= $(SRC)/main.c $(SRC)/error_check.c $(SRC)/error_set.c \
			  $(SRC)/init.c $(SRC)/make_board.c $(SRC)/read_map.c $(SRC)/key_press.c
OBJECTS 	= $(SOURCES:.c=.o)
INC			= ./include

all: $(NAME)

%.o: %.c
	arch -x86_64 $(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(NAME): $(OBJECTS)
	arch -x86_64 $(CC) $(CFLAGS) -L./mlx -lmlx -framework OpenGL -framework AppKit $(OBJECTS) -I $(INC) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re