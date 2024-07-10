FROM debian
RUN apt-get update -y && apt-get install build-essential inspircd irssi tcpflow vim netcat-traditional net-tools lsof git valgrind locales procps -y
RUN mkdir -p /var/run/inspircd
#COPY / /home
RUN sed -i '/en_US.UTF-8/s/^# //g' /etc/locale.gen && \
    locale-gen
ENV LANG en_US.UTF-8  
ENV LANGUAGE en_US:en  
ENV LC_ALL en_US.UTF-8 
