#!/bin/sh

# Kernel image
KERNEL_IMAGE=root.img

# Map the partitions from the image file
kpartx -av ${KERNEL_IMAGE}

# sleep a sec, wait for kpartx to create the device nodes
sleep 1

# Make the mount-point
mkdir -p tmp/p1

# Mount the filesystem via loopback
mount /dev/mapper/loop0p1 tmp/p1

# Copy in the files from the staging directory
cp -fv bin/examour tmp/p1/boot/kernel.bin

# Unmount the loopback
umount tmp/p1

# Unmap the image
kpartx -d ${KERNEL_IMAGE}

qemu-system-i386 -m 32 -hda root.img
