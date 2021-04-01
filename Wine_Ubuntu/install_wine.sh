#!/bin/bash

# Written by A.Tachibana, 2021/4/1

# Objective
## To install wine in Ubuntu 18

# Reference
## https://www.kkaneko.jp/tools/server/wine.html

############ To execute ############
# execute after install FAudio
# chmod 755 install_wine.sh
# ./install_wine.sh
####################################


# Require password
printf "password: "
read -s password

# Update and Upgrade
echo "$password" | sudo -S apt update && sudo -S apt -y upgrade

# Install wine
## Install packages
sudo -S apt install net-tools wget gnupg libcurses-dev
## Move dir
cd /tmp
## Key
wget -nc https://dl.winehq.org/wine-builds/winehq.key
sudo -S apt-key add winehq.key
## Add Repository
sudo -S apt-add-repository 'deb https://dl.winehq.org/wine-builds/ubuntu/ bionic main'
## Update and Upgrade
sudo -S apt update && sudo -S apt -y upgrade
## Install
sudo -S apt install --install-recommends winehq-stable
sudo -S apt -yV install playonlinux q4wine