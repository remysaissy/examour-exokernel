			** How to setup the environnement **

Prerequisites:
	- tcc cvs version
	- gcc 4.xx
	- binutils 2.17
	- gnu make
	- bochs 2.2.6 or later
	- grub	0.95 or later
	- mtools
	- qemu
	- bximage

@Installing Tcc
Tcc is located http://fabrice.bellard.free.fr/tcc. The cvs version (at the time of the writing of this document, it is located on savannah) must be used. The 0.9.23 won't work since segment registers support is missing and few other stuffs.
A tcc binary, compiled on a gnu/linux x86-32 bits platform is available in the toolkit directory of the present sources. To use it, you can do the following:
#cp toolkit/tcc /usr/local/bin/tcc
#chown root.root /usr/local/bin/tcc
#chmod 755 /usr/local/bin/tcc

@ How to install the environment
Go in build_tools and type ./install.sh
Go back in the base directory.

@ How to compile the kernel and the init env.
Type make in the base directory

@ How to launch the kernel
	- with bochs
		./launch.sh
	- with qemu
		./launch.sh qemu

@ How to compile and create drivers
Go in the drivers directory and have a look at the Makefile,
it contains the available drivers and you have to add your entries
to take yours in account.

@How to compile a new init env
Change the value of the INIT variable in the .config file at the root of the repository. By default, it points to apps/eash.


Enjoy.


-- 
Remy SAISSY
December 18th, 2006
