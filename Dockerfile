FROM debian:latest

RUN echo "deb http://mirrors.163.com/debian/ jessie main non-free contrib\ndeb http://mirrors.163.com/debian/ jessie-updates main non-free contrib\ndeb http://mirrors.163.com/debian/ jessie-backports main non-free contrib\ndeb-src http://mirrors.163.com/debian/ jessie main non-free contrib\ndeb-src http://mirrors.163.com/debian/ jessie-updates main non-free contrib\ndeb-src http://mirrors.163.com/debian/ jessie-backports main non-free contrib\ndeb http://mirrors.163.com/debian-security/ jessie/updates main non-free contrib\ndeb-src http://mirrors.163.com/debian-security/ jessie/updates main non-free contrib" >> sources.list
RUN mv sources.list /etc/apt/sources.list
RUN apt-get update

RUN apt-get install --assume-yes flex bison make valgrind

RUN apt-get install --assume-yes git curl
RUN apt-get install --assume-yes zsh
# RUN git clone https://github.com/robbyrussell/oh-my-zsh.git /root/.oh-my-zsh

RUN apt-get upgrade --assume-yes
