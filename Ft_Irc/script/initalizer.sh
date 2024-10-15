#!/bin/bash
IP=$(hostname -I | awk '{print $1}')
PORT=4242
PASSWORD=1234

IRC_PATH="/irc"

cd $IRC_PATH
if [ ! -f "ircserv" ]; then
	echo "Building ircserv..."
	make all
fi

echo "Server IP: $IP"
echo "Port: $PORT"
echo "Password: $PASSWORD"

./ircserv $PORT $PASSWORD
