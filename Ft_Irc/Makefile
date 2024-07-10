NAME = ircserv.a
OUT = ircserv
CCX = c++
SRC_DIR = src/
SRC_NODIR = main.cpp Server.cpp UserManager.cpp User.cpp Command.cpp Utils.cpp Channel.cpp ChannelManager.cpp IRCMessage.cpp NumericReplies.cpp
SRC = $(addprefix $(SRC_DIR), $(SRC_NODIR))
OBJ = $(SRC:.cpp=.o)
ifdef valgrind
CXXFLAGS = -Wall -Wextra -Werror -g -std=c++98 -fvisibility=hidden
else
ifdef debug
CXXFLAGS = -g -Wall -Wextra -Werror -fsanitize=address -I./include -std=c++98 -pedantic -fvisibility=hidden
else
ifdef leaks
CXXFLAGS = -Wall -Wextra -Werror -I./include -pedantic -D DEBUG=1 -std=c++98 -fvisibility=hidden -g
else
CXXFLAGS = -Wall -Wextra -Werror -fvisibility=hidden
endif
endif
endif
.PHONY: all clean fclean re debug leaks valgrind
all : $(NAME)
$(NAME) : $(OBJ)
	@ar -rcs $@ $^
	@$(CCX) $(CXXFLAGS) $@ -o $(OUT)
docker:
	@docker build -t irc .
	@docker run -it -v $(CURDIR):/irc irc
	# @docker run -it -p 5000-5010:5000-5010 -v $(CURDIR):/irc irc
debug:
	@make fclean
	@make debug=1 all
leaks:
	@make fclean
	@make leaks=1 all
valgrind:
	@make fclean
	@make valgrind=1 all
clean:
	@rm -f $(OBJ) $(NAME)
fclean: clean
	@rm -f $(OUT)
re: fclean all