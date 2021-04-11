#!/bin/bash

# Written by A.Tachibana, 2021/4/11

# Objective
## To install UxPlay (Mirroring iPad)

# Reference
## https://slash-mochi.net/?p=4068

############ To execute ############
# chmod 755 mirroring.sh
# ./mirroring.sh
####################################


# Require password
printf "password: "
read -s password

# Update and Upgrade
echo "$password" | sudo -S apt update && sudo -S apt -y upgrade

# Install Software
sudo -S apt install -y cmake libssl-dev libavahi-compat-libdnssd-dev libgstreamer1.0-dev libgstreamer-plugins-base1.0-dev gstreamer1.0-libav libgstreamer1.0-0 gstreamer1.0-plugins-base gstreamer1.0-plugins-good gstreamer1.0-plugins-bad gstreamer1.0-plugins-ugly gstreamer1.0-doc gstreamer1.0-tools gstreamer1.0-x gstreamer1.0-alsa gstreamer1.0-gl gstreamer1.0-gtk3 gstreamer1.0-qt5 gstreamer1.0-pulseaudio
# Setting graphic (for Intel CPU)
sudo -S apt install -y gstreamer1.0-vaapi

# Clone UxPlay under home directory
git clone https://github.com/antimof/UxPlay.git ~/UxPlay
cd ~/UxPlay

# Build source file
master
mkdir build
cd build
cmake ..
make