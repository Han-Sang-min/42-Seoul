# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hansangmin <hansangmin@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/03 15:07:14 by hansangmin        #+#    #+#              #
#    Updated: 2023/01/21 08:54:38 by hansangmin       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror

NAME 		= minishell
SRC			= ./src
LIBFT_PATH	= ./libft
INC			= ./include

MAN_SRCS	= $(SRC)/main.c \
			  $(SRC)/tools.c \
			  $(SRC)/tools_2.c \
			  $(SRC)/init.c \
			  $(SRC)/check_error.c \
			  $(SRC)/check_error2.c \
			  $(SRC)/exec/parse_exec_path.c \
			  $(SRC)/exec/set_redir.c \
			  $(SRC)/exec/exec_cmd.c \
			  $(SRC)/exec/exec_part.c \
			  $(SRC)/builtin/builtin.c \
			  $(SRC)/builtin/cd.c \
			  $(SRC)/builtin/echo.c \
			  $(SRC)/builtin/env.c \
			  $(SRC)/builtin/exit.c \
			  $(SRC)/builtin/pwd.c \
			  $(SRC)/builtin/unset.c \
			  $(SRC)/builtin/export.c \
   			  $(SRC)/parser/check_input.c \
 			  $(SRC)/parser/parser_line.c \
			  $(SRC)/parser/parser_cmd.c \
			  $(SRC)/parser/init_info.c \
			  $(SRC)/parser/info_utils.c \
			  $(SRC)/parser/split_info.c \
			  $(SRC)/parser/expand_env.c \
			  $(SRC)/signals/signals.c
M_OBJS	 	= $(MAN_SRCS:.c=.o)

# For Cluster Mac
READLINE_LIB 	= -lreadline -L /Users/$(USER)/.brew/opt/readline/lib
READLINE_INC	= -I /Users/$(USER)/.brew/opt/readline/include

# M1 Mac
# READLINE_LIB 	= -lreadline -L/opt/homebrew/opt/readline/lib
# READLINE_INC	= -I/opt/homebrew/opt/readline/include

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

OBJECTS = $(M_OBJS)


all : $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC) $(READLINE_INC)

$(NAME): $(OBJECTS)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJECTS) $(LIBFT_PATH)/libftprintf.a -I $(INC) -o $(NAME) $(READLINE_INC) $(READLINE_LIB)
	@echo "$(GREEN)minishell compile finished.$(DEF_COLOR)"

clean:
	@rm -f $(M_OBJS)
	@make clean -C $(LIBFT_PATH)
	@echo "$(YELLOW)minishell object files has been deleted.$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "$(YELLOW)minishell executable files has been deleted.$(DEF_COLOR)"

re: fclean all

.PHONY: all bonus clean fclean re
