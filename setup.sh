#!/bin/bash

sudo apt update
sudo apt install git cmake libsdl2-dev libglew-dev -y

wget https://raw.githubusercontent.com/nothings/stb/master/stb_image.h
sudo mv stb_image.h /usr/local/include
wget https://raw.githubusercontent.com/nothings/stb/master/stb_ds.h
sudo mv stb_ds.h /usr/local/include

git clone https://github.com/recp/cglm
cd cglm
mkdir build && cd build
cmake ..
make
sudo make install

cd ../..
rm -rf cglm
mkdir build && cd build
cmake ..
make
