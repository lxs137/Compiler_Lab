FROM debian:latest

RUN echo "deb http://mirrors.163.com/debian/ jessie main non-free contrib\ndeb http://mirrors.163.com/debian/ jessie-updates main non-free contrib\ndeb http://mirrors.163.com/debian/ jessie-backports main non-free contrib\ndeb-src http://mirrors.163.com/debian/ jessie main non-free contrib\ndeb-src http://mirrors.163.com/debian/ jessie-updates main non-free contrib\ndeb-src http://mirrors.163.com/debian/ jessie-backports main non-free contrib\ndeb http://mirrors.163.com/debian-security/ jessie/updates main non-free contrib\ndeb-src http://mirrors.163.com/debian-security/ jessie/updates main non-free contrib" >> sources.list
RUN mv sources.list /etc/apt/sources.list
RUN apt-get update

RUN apt-get install --assume-yes flex bison make valgrind

RUN apt-get install --assume-yes git
RUN echo "[user]\n	email = 837940593@qq.com\n	name = demons\n[credential]\n    helper = store" >> ~/.gitconfig

RUN apt-get install --assume-yes curl
RUN apt-get install --assume-yes zsh
# sh -c "$(curl -fsSL https://raw.githubusercontent.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"

RUN apt-get install --assume-yes vim
RUN git clone https://github.com/amix/vimrc.git ~/.vim_runtime
RUN sh ~/.vim_runtime/install_awesome_vimrc.sh

RUN cd /home && git clone https://github.com/Clcanny/Compiler_Lab.git

RUN apt-get upgrade --assume-yes
