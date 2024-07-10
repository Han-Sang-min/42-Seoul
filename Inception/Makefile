NAME		= .inception
DOMAIN_NAME	= sangmiha.42.fr

all : $(NAME)

$(NAME)	:
	# @touch $(NAME)
	@if ! grep -e '^127.0.0.1\s\+$(DOMAIN_NAME)' /etc/hosts; then \
		sudo sh -c 'echo "127.0.0.1    $(DOMAIN_NAME)" >>  /etc/hosts'; \
	fi
	
	mkdir -p /Users/hansangmin/testwp
	mkdir -p /Users/hansangmin/testdb

	docker-compose -f srcs/docker-compose.yml up --build -d

down : 
	cd ./srcs && docker-compose down
	@rm -rf $(NAME)

clean :
	make down
	docker system prune -a

fclean :
	make clean
	docker volume rm -f srcs_db srcs_wp
	sudo rm -rf /home/sangmiha/data/wp/*
	sudo rm -rf /home/sangmiha/data/db/*

re :
	make fclean
	make all

.PHONY	: all down clean fclean re
