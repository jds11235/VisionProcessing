#!/bin/sh

# Sets up a debian linux machine for the machine vision program, and compiles the machine vision program
#    Copyright (C) 2017  John Selfors
#
#    This program is free software: you can redistribute it and/or modify
#    it under the terms of the GNU General Public License as published by
#    the Free Software Foundation, either version 3 of the License, or
#    (at your option) any later version.
#
#    This program is distributed in the hope that it will be useful,
#    but WITHOUT ANY WARRANTY; without even the implied warranty of
#    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#    GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see <http://www.gnu.org/licenses/>.

apt-get update
apt-get install build-essential
apt-get install libopencv-dev
apt-get install cmake
apt-get install v4l-utils
apt-get install git
modprobe bcm2835-v4l2
cd ~
git clone https://github.com/wpilibsuite/ntcore
cd ntcore
cmake . -DWITHOUT_JAVA=true
make
make install
LD_LIBRARY_PATH=/usr/local/lib
export LD_LIBRARY_PATH
ldconfig
cd ~
git clone https://github.com/jds11235/VisionProcessing
cd VisionProcessing
chmod +x VisionServer
chmod +x autorun.sh
chmod +x compile.sh
(crontab -l; echo "@reboot ~/VisionProcessing/autorun.sh" ) | crontab -