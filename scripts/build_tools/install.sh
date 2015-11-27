#!/bin/sh

# Force a good PATH.
export PATH="/sbin:/usr/sbin:/usr/local/sbin:/bin:/usr/bin:/usr/local/bin"

# Detect configuration.

BXIMAGE="`which bximage`"
[ $? -eq 1 ] && echo "bximage is missing." && exit 1;
MKFS_VFAT="`which mkfs`"
[ $? -eq 1 ] && echo "mkfs is missing." && exit 1;    
GRUB="`which grub`"
[ $? -eq 1 ] && echo "grub is missing." && exit 1;    
MMD="`which mmd`"
[ $? -eq 1 ] && echo "mmd (mtools) is missing." && exit 1;    
MCOPY="`which mcopy`"
[ $? -eq 1 ] && echo "mcopy (mtools) is missing." && exit 1;    
CP="`which cp`"
[ $? -eq 1 ] && echo "cp is missing." && exit 1;    
RM="`which rm`"
[ $? -eq 1 ] && echo "rm is missing." && exit 1;    
SED="`which sed`"
[ $? -eq 1 ] && echo "sed is missing." && exit 1;    

# create the floppy image
$BXIMAGE -q -fd -size=1.44 fd.img

# create a vfat/dos file system

$MKFS_VFAT -t vfat fd.img

# to be able to use mtools

echo "drive a: file=\"fd.img\" exclusive" > .mtoolsrc

# I want to use the mtools.
export MTOOLSRC=".mtoolsrc"

# create and install the boot devices.
$MMD a:boot
$MMD a:boot/grub
$MCOPY bootfs/boot/grub/menu.lst a:boot/grub/menu.lst
$MCOPY bootfs/boot/grub/stage1 a:boot/grub/stage1
$MCOPY bootfs/boot/grub/stage2 a:boot/grub/stage2
$MCOPY bootfs/boot/grub/fat_stage1_5 a:boot/grub/fat_stage1_5

unset MTOOLSRC
$RM -f .mtoolsrc

# install the grub on the floppy image.
$GRUB --no-floppy --batch << EOF
device (fd0) fd.img
root (fd0)
setup (fd0)
quit
EOF
 
# cleanup the floppy directive...
$SED -e 's/^floppya.*//g' .bochsrc > .bochsrc.tmp
$CP .bochsrc.tmp .bochsrc
# and the boot drive too.
$SED -e 's/^boot.*//g' .bochsrc > .bochsrc.tmp
$CP .bochsrc.tmp .bochsrc

# install the good directives.
echo "boot: floppy" >> .bochsrc
echo "floppya: image=\"`basename \`pwd\``/fd.img\", status=inserted" >> .bochsrc

# ok now it is ready to be used.
