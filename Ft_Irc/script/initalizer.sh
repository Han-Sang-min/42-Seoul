#!/bin/bash
IP=$(hostname -I | awk '{print $1}')
PORT=4242
PASSWORD=1234

IRC_PATH="/irc"

echo "Server IP: $IP"
echo "Port: $PORT"
echo "Password: $PASSWORD"

if [ ! -f "$IRC_PATH/ircserv" ]; then
	echo "Building ircserv..."
	make all
fi
"$IRC_PATH/ircserv" $PORT $PASSWORD
