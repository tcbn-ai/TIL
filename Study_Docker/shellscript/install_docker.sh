#!/bin/bash

# Written by A.Tachibana, 2021/3/19

# Objective
## To install docker in Ubuntu 18

# Reference
## https://www.kkaneko.jp/tools/docker/ubuntu_docker.html

############ To execute ############
# chmod 755 install_docker.sh
# ./install_docker.sh
####################################


# Require password
printf "password: "
read -s password

# Update and Upgrade
echo "$password" | sudo -S apt update && sudo -S apt -y upgrade

# Install Docker
## Delete old version (if exists)
sudo -S apt -y remove docker docker-engine docker.io containerd docker-ce docker-ce-cli
sudo -S apt -y autoremove
## Install required software
sudo -S apt update
sudo -S apt -y install apt-transport-https ca-certificates curl software-properties-common
sudo -S apt -y install linux-image-generic
## Set docker repository
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
apt-key fingerprint 0EBFCD88
sudo -S add-apt-repository \
    "deb [arch=amd64] https://download.docker.com/linux/ubuntu \
    $(lsb_release -sc) \
    stable"
sudo -S apt update
## Install docker.io
sudo -S apt -y install docker.io containerd docker-compose
## Add authority
sudo -S usermod -aG docker $USER
## Set autostart
sudo -S systemctl unmask docker.service
sudo -S systemctl enable docker
sudo -S systemctl is-enabled docker
## let user ubuntu use docker
sudo gpasswd -a $USER docker
