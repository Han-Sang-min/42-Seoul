# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/03 15:07:14 by hansangmin        #+#    #+#              #
#    Updated: 2022/11/22 01:08:53 by hansangmin       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
NAME 		= pipex
SRC			= ./src
LIBFT_PATH	= ./libft
INC			= ./include
MAN_SRCS	= $(SRC)/main.c  $(SRC)/parsing.c $(SRC)/extra.c $(SRC)/execute.c
M_OBJS	 	= $(MAN_SRCS:.c=.o)

BNS_SRCS	= $(SRC)/main_bonus.c $(SRC)/parsing_bonus.c $(SRC)/extra_bonus.c $(SRC)/execute_bonus.c
B_OBJS	 	= $(BNS_SRCS:.c=.o)

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

ifdef BONUS
	OBJECTS = $(B_OBJS)
else
	OBJECTS = $(M_OBJS)
endif

all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_PATH)/libftprintf.a -I $(INC) -o $(NAME)
	@echo "$(GREEN)=================================================$(DEF_COLOR)"
	@echo "$(GREEN)|       pipex compile finished. 		|$(DEF_COLOR)"
	@echo "$(GREEN)=================================================$(DEF_COLOR)"

bonus:
	@echo "$(GREEN)======================bonus======================$(DEF_COLOR)"
	@make BONUS=1 clean all

clean:
	@rm -f $(M_OBJS) $(B_OBJS)
	@make clean -C $(LIBFT_PATH)
	@echo "$(YELLOW)=================================================$(DEF_COLOR)"
	@echo "$(YELLOW)|    pipex obj files has been deleted. 		|$(DEF_COLOR)"
	@echo "$(YELLOW)=================================================$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "$(YELLOW)=================================================$(DEF_COLOR)"
	@echo "$(YELLOW)|   pipex executable files has been deleted.    |$(DEF_COLOR)"
	@echo "$(YELLOW)=================================================$(DEF_COLOR)"

re: fclean all

.PHONY: all bonus clean fclean re