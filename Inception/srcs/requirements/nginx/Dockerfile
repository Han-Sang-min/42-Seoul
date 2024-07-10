FROM debian:bullseye

RUN apt-get update \
	&& apt-get install -y nginx \
    && rm -rf /var/lib/apt/lists/* \
	&& mkdir -p /var/log/nginx/

COPY conf/nginx.conf /etc/nginx/nginx.conf
COPY tools/nginx.crt /etc/nginx/ssl/nginx.crt
COPY tools/nginx.pem /etc/nginx/ssl/nginx.pem

CMD ["nginx", "-g", "daemon off;"]
