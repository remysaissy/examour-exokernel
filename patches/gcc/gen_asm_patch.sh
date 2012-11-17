#!/bin/sh
## Started on  Wed Sep 20 12:31:10 2006 
## Last update Tue Sep 26 16:26:26 2006 

ORIG_VERSION_PATH=gcc-4.1.0
MODIF_VERSION_PATH=gcc-4.1.0-patch-segreg

MODIFIED_FILES=$(cd ${MODIF_VERSION_PATH} && find . |grep '\~' | sed 's/\.*~.*$//g' |tr '\n' ' ')
#MODIFIED_FILES="gcc/config/i386/i386.c gcc/config/i386/i386.h gcc/config/i386/i386-protos.h gcc/config/i386/i386.md"

OUTPUT_DIR="segreg_asm"

echo "Generating patch for __asm__(<segreg>)"
[ ! -d $OUTPUT_DIR ] && mkdir $OUTPUT_DIR
for entry in $MODIFIED_FILES;
do
  the_diff=$(diff -c -p -d ${ORIG_VERSION_PATH}/$entry ${MODIF_VERSION_PATH}/$entry)
  if [ "$the_diff" != "" ]; then
      echo "diff -c -p -d ${ORIG_VERSION_PATH}/$entry ${MODIF_VERSION_PATH}/$entry > $OUTPUT_DIR/`basename $entry`.patch"
      echo "$the_diff" > $OUTPUT_DIR/`basename $entry`.patch
  fi
done
# diff -c -p -d gcc-4.1.0-patch-far/gcc/config/i386/i386.c gcc-4.1.0/gcc/config/i386/i386.c > far_attr/i386.c.patch
# diff -c -p -d gcc-4.1.0-patch-far/gcc/config/i386/i386-protos.h gcc-4.1.0/gcc/config/i386/i386-protos.h > far_attr/i386-protos.h.patch
echo "Patch generated."
