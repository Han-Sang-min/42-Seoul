FROM	debian:bullseye

RUN 	apt-get -y update

RUN		apt-get -y install mariadb-server mariadb-client \
		&& mkdir /run/mysqld \
		&& chmod 777 /run/mysqld \
		&& chmod 777 /var/lib/mysql \
		&& rm -rf /var/lib/mysql/aria_log_control

COPY	conf/50-server.cnf /etc/mysql/mariadb.conf.d/50-server.cnf
COPY	tools/setup.sh .

RUN		chmod 777 ./setup.sh

CMD		["./setup.sh"]
