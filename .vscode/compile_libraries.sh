#!/usr/bin/env bash

for file in $1/*c; do
    if [ "$file" != "${2}" ]; then
        noExt=$(echo "$file" | cut -f 1 -d '.')
        echo Compiling $file
        gcc -o $noExt.o -c $file
    fi
done
