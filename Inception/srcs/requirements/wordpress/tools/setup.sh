#!/bin/bash 

if [ ! -e $WORDPRESS_PATH/index.php ]; then

    wp core download --allow-root --path=$WORDPRESS_PATH
    
    mv /var/www/html/wp-config.php $WORDPRESS_PATH/wp-config.php 

    sed -i "s/WORDPRESS_DB_NAME/$WORDPRESS_DB_NAME/" $WORDPRESS_PATH/wp-config.php
    sed -i "s/WORDPRESS_DB_USER/$WORDPRESS_DB_USER/" $WORDPRESS_PATH/wp-config.php
    sed -i "s/WORDPRESS_DB_PASSWORD/$WORDPRESS_DB_PASSWORD/" $WORDPRESS_PATH/wp-config.php
    sed -i "s/WORDPRESS_DB_HOST/$WORDPRESS_DB_HOST/" $WORDPRESS_PATH/wp-config.php
    
    sed -i "s/WORDPRESS_AUTH_KEY/$WORDPRESS_AUTH_KEY/" $WORDPRESS_PATH/wp-config.php
    sed -i "s/WORDPRESS_SECURE_AUTH_KEY/$WORDPRESS_SECURE_AUTH_KEY/" $WORDPRESS_PATH/wp-config.php
    sed -i "s/WORDPRESS_LOGGED_IN_KEY/$WORDPRESS_LOGGED_IN_KEY/" $WORDPRESS_PATH/wp-config.php
    sed -i "s/WORDPRESS_NONCE_KEY/$WORDPRESS_NONCE_KEY/" $WORDPRESS_PATH/wp-config.php
    sed -i "s/WORDPRESS_AUTH_SALT/$WORDPRESS_AUTH_SALT/" $WORDPRESS_PATH/wp-config.php
    sed -i "s/WORDPRESS_SECURE_AUTH_SALT/$WORDPRESS_SECURE_AUTH_SALT/" $WORDPRESS_PATH/wp-config.php
    sed -i "s/WORDPRESS_LOGGED_IN_SALT/$WORDPRESS_LOGGED_IN_SALT/" $WORDPRESS_PATH/wp-config.php
    sed -i "s/WORDPRESS_NONCE_SALT/$WORDPRESS_NONCE_SALT/" $WORDPRESS_PATH/wp-config.php 

    chown www-data: /var/www/html/ -R
    
    wp core install --url=$DOMAIN_NAME --title=$WORDPRESS_TITLE --admin_email=$WORDPRESS_ADMIN_EMAIL --admin_password=$WORDPRESS_DB_PASSWORD --admin_name=$WORDPRESS_DB_USER --allow-root --path=$WORDPRESS_PATH --skip-email
    wp user create author author@42.fr --user_pass=1234 --role=author --allow-root --path=$WORDPRESS_PATH
fi

/usr/sbin/php-fpm7.4 -F
