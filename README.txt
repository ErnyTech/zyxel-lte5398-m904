ReadMe for LTE5398-M904 Generic V1.00(ABQV.4)C0


0. Introduction

  This file will show you how to build the  LTE5398-M904 linux system,
  please note, the download image will overwrite the original image existed in the flash memory of EV board.


1. Files list

   A. README					- This file

   B. GPL_LTE5398-M904_Generic_V1.00(ABQV.4)C0.tar.bz2	- Open Source Code of LTE5398-M904 and Open Source Code of Toolchain


2. Prepare the build OS.

   A. We suggest using the Linux distribution to setup your environment for reduce compatible issue.

	Install Ubuntu 12.04 Desktop 32bit

   B. Update system

       Use GUI interface to update system or use command to update system.

	$ sudo apt-get update
	
   *Note: If update failed, edit /etc/apt/sources.list as following link
	deb http://old-releases.ubuntu.com/ubuntu/ precise main
	deb-src http://old-releases.ubuntu.com/ubuntu/ precise main
	deb http://old-releases.ubuntu.com/ubuntu/ precise-updates main
	deb-src http://old-releases.ubuntu.com/ubuntu/ precise-updates main
	deb http://old-releases.ubuntu.com/ubuntu/ precise universe
	deb-src http://old-releases.ubuntu.com/ubuntu/ precise universe
	deb http://old-releases.ubuntu.com/ubuntu/ precise-updates universe
	deb-src http://old-releases.ubuntu.com/ubuntu/ precise-updates universe
	deb http://old-releases.ubuntu.com/ubuntu precise-security main
	deb-src http://old-releases.ubuntu.com/ubuntu precise-security main
	deb http://old-releases.ubuntu.com/ubuntu precise-security universe
	deb-src http://old-releases.ubuntu.com/ubuntu precise-security universe


   C. Change default /bin/sh link to /bin/bash

	$ sudo dpkg-reconfigure dash
	choice "no" and press enter.


3. Prepare the compiler environment

   Install the following necessary tools 

	$ sudo apt-get install -y g++ flex bison gawk make autoconf zlib1g-dev libncurses-dev git subversion gettext
	$ sudo apt-get install curl 
	$ curl -sL https://deb.nodesource.com/setup_6.x | sudo -E bash -
	$ sudo apt-get install -y nodejs


4. Extract the open source code

	$ tar jxf <FW tarbal File>


5. Build the firmware for Web-GUI upgrade using

   Change the directory into extrated directory

	$ cd <extrated directory>

	
   Clean and build the firmware

	$ make dirclean
	$ make


6. The image is in the images directory.

    The firmware image will locate at <extrated directory>/bin/ramips/zyxel/ras.bin
    You can use it update LTE5398-M904 by using the firmware update procedure.


