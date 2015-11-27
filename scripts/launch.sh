#!/bin/bash
## This file is part of exAmour

## Copyright (C) Remy Saissy <remy.saissy@epitech.net>
## exAmour is free software; you can redistribute it and/or modify
## it under the terms of the GNU General Public License as published by
## the Free Software Foundation; either version 2 of the License, or
## (at your option) any later version.

## exAmour is distributed in the hope that it will be useful,
## but WITHOUT ANY WARRANTY; without even the implied warranty of
## MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
## GNU General Public License for more details.

## You should have received a copy of the GNU General Public License
## along with this program; if not, write to the Free Software
## Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
##

# The purpose of this script is to launch the kernel using qemu


[ ! -r .config ] && echo "Error, no .config file." && exit 1

source .config

krnl_image="examour/arch/current/kernel_image"
init_image="$INIT/`basename $INIT`"

MCOPY="`which mcopy`"
[ $? -eq 1 ] && echo "mcopy (mtools) is missing." && exit 1;
MDELTREE="`which mdeltree`"
[ $? -eq 1 ] && echo "mdel (mtools) is missing." && exit 1;
RM="`which rm`"
[ $? -eq 1 ] && echo "rm is missing." && exit 1;


[ ! -e $krnl_image ] && echo "Error, no kernel image found." && exit 2

[ ! -e $init_image ] && echo "Error, no init image found." && exit 3

if [ ! -e "build_tools/fd.img" ];
    then
    echo "No floppy image, building one..."
    cd build_tools
    ./install.sh
    [ $? -eq 1 ] && echo "Can't create floppy image. ExAmour launch aborted..." && exit 1;
    cd -
fi

cp_krnl()
{
 echo "drive a: file=\"build_tools/fd.img\" exclusive" > .mtoolsrc
 export MTOOLSRC=".mtoolsrc"
 echo "Installing the kernel..."
 $MDELTREE a:examour
 $MCOPY $krnl_image a:examour
 echo "Installing the init env..."
 $MDELTREE a:init
 $MCOPY $init_image a:init
 echo "done."
 unset MTOOLSRC
 $RM -f .mtoolsrc
}

case "$1"
    in
    "qemu")
	QEMU="`which qemu`"
	[ $? -eq 1 ] && echo "qemu is missing." && exit 1;
	cp_krnl
	echo "Launching qemu with 32mb of ram..."
	$QEMU -m 32 -fda build_tools/fd.img
	echo "end.";;
    *)
	BOCHS="`which bochs`"
	[ $? -eq 1 ] && echo "bochs is missing." && exit 1;
	cp_krnl
	echo "Launching bochs..."
	echo "Please notice that qemu is available too."
	$BOCHS -q -f build_tools/.bochsrc
	echo "end.";;
esac
