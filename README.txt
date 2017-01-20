Vision processing program

for use with a linux system, with the autosetup configured for debian based systems.
Utilizes OpenCV libraries for vision processing and the ntcore libraries for sending data over the FRC NetworkTables.
Written in C++.
Autoconfigures the program to run on reboot using cron.
The program is configured, and compiled by running sudo setup.sh
The program can be recompiled by running compile.sh

Settting up Raspberry pi: run setup.sh
then compile.sh
then it should autorun on startup

Setup and Configuration

autorun.sh is run when starting the program. In order to set the #defines,
run the python configuration files, and run WinSCP to copy over the files.
The TEAM_NUMBER #define should be set manually to the team number that was used in the RoboRIO configuration.
The TEAM_NUMBER #define should be the only #define edidted by the user
The SIDES #define should be set to the contour side number
The CONCAVITY #define should be set to true for concave shapes, and false for convex shapes