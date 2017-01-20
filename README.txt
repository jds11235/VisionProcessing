Vision processing program

for use with a linux system, with the autosetup configured for debian based systems.
Utilizes OpenCV libraries for vision processing and the ntcore libraries for sending data over the FRC NetworkTables.
Can also be configured to send data over UART.
Written in C++.
Autoconfigures the program to run on reboot using cron.
The program is configured, and compiled by running sudo setup.sh
The program can be recompiled by running compile.sh

Setting up a Raspberry Pi environment for Vision Processing with Windows 10 (the network configuration is mildly different for other versions of Windows):
1.	Download the Raspbian Lite image from https://www.raspberrypi.org/downloads/raspbian/
2.	Download the Win32DiskImager from https://sourceforge.net/projects/win32diskimager/
3.	Download Putty from http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html
4.	Download WinSCP from https://winscp.net/eng/download.php
5.	Extract the Raspian image from the .zip file
6.	Plug the SD card from the Raspberry Pi into the computer
7.	Open Win32DiskImager, and select the Raspian ISO, and the SD card for the Raspberry Pi
8.	Start the imaging process
9.	Connect the Raspberry Pi to your network, using an ethernet cable
10.	Follow the instructions at http://www.instructables.com/id/Use-ssh-to-talk-with-your-Raspberry-Pi/ to setup the ssh connection
11. 	Open Putty and type pi@raspberrypi.local for the host name
12.	The username will be pi and the password will be raspberry
13.	Run sudo apt-get update
14.	Run sudo apt-get upgrade
15.	Run sudo apt-get install raspi-config
16.	Run sudo apt-get install git
17.	Run sudo raspi-config and enable the camera (if using the internal camera)
18.	Also enable the serial connection, if using serial communications
19.	Set the memory divider so the GPU has 512 MB of RAM
20.	Disable the WiFi and Bluetooth
21.	Run git clone https://github.com/jds11235/VisionProcessing.git
22.	Run cd VisionProcessing
23.	Run sudo ./setup.sh
Coppying the .h files from the configuration programs and recompile:
1.	Open WinSCP
2.	Connect using the Host name of raspberrypi.local, username of pi, and password of raspberry
3.	Open the VisionProcessing on the raspberry pi side, and on the host side, the folder containing the .h files
4.	Drag the .h files from the host side to the raspberry pi side
5.	Close the program
6.	Open Putty and connect to the raspberry pi
7.	Run cd VisionProcessing
6.	Run ./compile.sh

Setup and Configuration

autorun.sh is run when starting the program. In order to set the #defines,
run the python configuration files, and run WinSCP to copy over the files.
The TEAM_NUMBER #define should be set manually to the team number that was used in the RoboRIO configuration.
The TEAM_NUMBER #define should be the only #define edidted by the user