#!/bin/bash

[ ! -e "build_tools/fd.img" ] && cd build_tools && ./install.sh && cd 
..;

export MTOOLSRC=".mtoolsrc"
echo "drive a: file=\"build_tools/fd.img\" exclusive" > .mtoolsrc
/usr/bin/mdeltree a:examour
/usr/bin/mcopy ../BUILD-I386/ExAmour a:examour
echo "Launching Bochs..."
bochs -f build_tools/.bochsrc -q
#echo "Launching Qemu with 32mb."
#if [ "$1" == "debug" ]; then 
#qemu -s -S -fda build_tools/fd.img -boot a
#else
#qemu -m 32 -fda build_tools/fd.img -boot a
#fi
