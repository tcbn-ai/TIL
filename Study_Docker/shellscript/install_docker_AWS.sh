#!/bin/bash

# Written by A.Tachibana, 2021/3/28

# Objective
## To install docker in Ubuntu 18

# Reference
## 大澤文孝，浅居尚，さわって学ぶクラウドインフラ docker 基礎からのコンテナ構築，日経BP，2020.
## https://docs.docker.com/engine/install/ubuntu/

############ To execute ############
# chmod 755 install_docker_AWS.sh
# ./install_docker_AWS.sh
####################################

# Update
sudo apt-get update

# Install Docker
## Install required packages
sudo apt-get -y install apt-transport-https ca-certificates curl gnupg-agent software-properties-common
## add GPG key
curl -fsSL https://download.docker.com/linux/ubuntu/gpg | sudo apt-key add -
## set docker repository
sudo add-apt-repository \
	"deb [arch=amd64] https://download.docker.com/linux/ubuntu \
	$(lsb_release -sc) \
       	stable"
## Update packages
sudo apt-get update
## Install Docker Engine
sudo apt-get install -y docker-ce docker-ce-cli containerd.io
## let user ubuntu use docker
sudo gpasswd -a $USER docker

