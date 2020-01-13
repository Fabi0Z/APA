#!/usr/bin/env bash

cfile="${1}/${2}.c"
headerfile="${1}/${2}.h"
defCheck=$(echo "$2" | tr [a-z] [A-Z])_H

rm $headerfile
makeheaders $cfile

echo "#ifndef ${defCheck}" >temp
echo "#define ${defCheck}" >>temp
echo >>temp
echo >>temp
echo >>temp
tail -n +2 $headerfile >>temp
echo >>temp
echo "#endif // ! ${defCheck}" >>temp
mv temp $headerfile
