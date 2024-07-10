FROM	debian:bullseye

RUN 	apt-get -y update

RUN		apt-get -y install php7.4 php7.4-fpm php7.4-mysql curl \
		&& mkdir /run/php \
		&& chmod 777 /run/php \
		&& curl -o /usr/local/bin/wp -sL https://raw.githubusercontent.com/wp-cli/builds/gh-pages/phar/wp-cli.phar \
		&& chmod 777 /usr/local/bin/wp \
		&& mkdir -p /var/www/html/wordpress/

COPY	conf/wp-config.php /var/www/html/wordpress/wp-config.php
COPY	conf/www.conf /etc/php/7.4/fpm/pool.d/www.conf
COPY	tools/setup.sh .

RUN		chmod 777 setup.sh

CMD ["./setup.sh"]
