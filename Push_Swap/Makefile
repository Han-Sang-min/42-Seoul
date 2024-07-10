# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sangmiha <sangmiha@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/03 15:07:14 by hansangmin        #+#    #+#              #
#    Updated: 2022/11/16 16:31:44 by sangmiha         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC 			= cc
CFLAGS 		= -Wall -Wextra -Werror
NAME 		= push_swap
SRC			= ./source
LIBFT_PATH	= ./libft

SOURCES 	= $(SRC)/main.c $(SRC)/init_stack.c $(SRC)/cmd_set.c $(SRC)/tool.c \
			  $(SRC)/cmd_detail.c $(SRC)/find_pivot.c $(SRC)/sort_stack.c $(SRC)/a_sort.c\
 			  $(SRC)/b_sort.c $(SRC)/err_check.c $(SRC)/b_sort2.c $(SRC)/a_sort2.c
OBJECTS 	= $(SOURCES:.c=.o)
INC			= ./include

#bonus
BNS_NAME	= checker
BNS			= ./bonus
BNS_SRCS	=  $(BNS)/main_bonus.c $(BNS)/cmd_detail_bonus.c $(BNS)/cmd_set_bonus.c \
			   $(BNS)/err_check_bonus.c \
			   $(BNS)/get_next_line_bonus.c $(BNS)/get_next_line_utils_bonus.c \
			   $(BNS)/init_stack_bonus.c $(BNS)/receive_cmd_bonus.c \
			   $(BNS)/result_bonus.c $(BNS)/tool_bonus.c
BNS_OBJS 	=  $(BNS_SRCS:.c=.o)

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
	OBJ_FILES = $(BNS_OBJS)
	E_NAME	= $(BNS_NAME)
else
	OBJ_FILES = $(OBJECTS)
	E_NAME	= $(NAME)
endif

all : $(E_NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I $(INC)


$(E_NAME): $(OBJ_FILES)
	@make -C $(LIBFT_PATH)
	@$(CC) $(CFLAGS) $(OBJ_FILES) $(LIBFT_PATH)/libftprintf.a -I $(INC) -o $(E_NAME)
	@echo "$(GREEN)=================================================$(DEF_COLOR)"
	@echo "$(GREEN)|       push_swap compile finished.             |$(DEF_COLOR)"
	@echo "$(GREEN)=================================================$(DEF_COLOR)"

bonus:
	@echo "$(GREEN)======================bonus======================$(DEF_COLOR)"
	@make BONUS=1 all

clean:
	@rm -f $(BNS_OBJS) $(OBJECTS)
	@make clean -C $(LIBFT_PATH)
	@echo "$(YELLOW)=================================================$(DEF_COLOR)"
	@echo "$(YELLOW)|    push_swap obj files has been deleted.      |$(DEF_COLOR)"
	@echo "$(YELLOW)=================================================$(DEF_COLOR)"

fclean: clean
	@rm -f $(NAME) $(BNS_NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "$(YELLOW)=================================================$(DEF_COLOR)"
	@echo "$(YELLOW)|   push_swap executable files has been deleted.|$(DEF_COLOR)"
	@echo "$(YELLOW)=================================================$(DEF_COLOR)"

re: fclean all

.PHONY: all bonus clean fclean re