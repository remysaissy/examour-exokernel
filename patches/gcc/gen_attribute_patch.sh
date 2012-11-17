MODIFIED_FILES="gcc/config/i386/i386.c gcc/config/i386/i386.h gcc/config/i386/i386-protos.h gcc/config/i386/i386.md"

OUTPUT_DIR="far_attr"

echo "Generating patch for __attribute__((far()))"
[ ! -d $OUTPUT_DIR ] && mkdir $OUTPUT_DIR
for entry in $MODIFIED_FILES;
do
 diff -c -p -d gcc-4.1.0/$entry gcc-4.1.0-patch-far/$entry > $OUTPUT_DIR/`basename $entry`.patch
done
# diff -c -p -d gcc-4.1.0-patch-far/gcc/config/i386/i386.c gcc-4.1.0/gcc/config/i386/i386.c > far_attr/i386.c.patch
# diff -c -p -d gcc-4.1.0-patch-far/gcc/config/i386/i386-protos.h gcc-4.1.0/gcc/config/i386/i386-protos.h > far_attr/i386-protos.h.patch
echo "Patch generated."
