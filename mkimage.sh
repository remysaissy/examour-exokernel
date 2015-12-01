#!/bin/sh

# Kernel image
KERNEL_IMAGE=build/root.img

# Removing the previous image
rm -rf ${KERNEL_IMAGE}

# Create the actual disk image - 20MB
dd if=/dev/zero of=${KERNEL_IMAGE} count=20 bs=1048576

# Make the partition table, partition and set it bootable.
parted --script ${KERNEL_IMAGE} mklabel msdos mkpart p ext2 1 20 set 1 boot on

# Map the partitions from the image file
kpartx -av ${KERNEL_IMAGE}

# sleep a sec, wait for kpartx to create the device nodes
sleep 1

# Make an ext2 filesystem on the first partition.
mkfs.ext2 /dev/mapper/loop0p1

# Make the mount-point
mkdir -p build/tmp/p1

# Mount the filesystem via loopback
mount /dev/mapper/loop0p1 build/tmp/p1

# Copy in the files from the staging directory
#cp -r build/img/* build/tmp/p1
mkdir -p build/tmp/p1/boot/grub
cp grub.cfg build/tmp/p1/boot/grub/grub.cfg
cp build/bin/examour build/tmp/p1/boot/kernel.bin

# Create a device map for grub
echo "(hd0) /dev/loop0" > `pwd`/build/tmp/p1/boot/grub/device.map

# Use grub2-install to actually install Grub. The options are:
#   * No floppy polling.
#   * Use the device map we generated in the previous step.
#   * Include the basic set of modules we need in the Grub image.
#   * Install grub into the filesystem at our loopback mountpoint.
#   * Install the MBR to the loopback device itself.
grub-install --no-floppy \
--modules="biosdisk part_msdos ext2 configfile normal multiboot" \
--root-directory=`pwd`/build/tmp/p1 \
/dev/loop0

# Unmount the loopback
umount build/tmp/p1

# Unmap the image
kpartx -d ${KERNEL_IMAGE}

# hack to make everything owned by the original user, since it will currently be
# owned by root...
LOGNAME=`who am i | awk '{print $1}'`
LOGGROUP=`groups $LOGNAME | awk '{print $3}'`
chown $LOGNAME:$LOGGROUP -R build ${KERNEL_IMAGE}
