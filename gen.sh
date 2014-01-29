#!/bin/bash

FILE=keys.h

# create translation table based on /usr/include/linux/input.h
cp file-header.h $FILE
echo "/* generated from /usr/include/linux/input.h by gen.sh" >> $FILE
echo " * Don't modifiy this file!" >> $FILE
echo " */" >> $FILE
echo "#ifndef _KEYS_H_" >> $FILE
echo "#define _KEYS_H_" >> $FILE
echo "" >> $FILE
echo "#include <linux/input.h>" >> $FILE
echo "" >> $FILE
echo "char *keycodes[KEY_MAX + 1] = {" >> $FILE

grep "#define KEY_" /usr/include/linux/input.h | grep -v "\(KEY_MAX\|KEY_CNT\)" | sed "s/#define KEY_\([A-Za-z0-9_]*\).*/    [KEY_\1] = \"\1\",/g" >> $FILE

echo "    [KEY_MAX] = \"\"" >> $FILE
echo "};" >> $FILE
echo "#endif /* KEYS_H_ */" >> $FILE

