#!/bin/bash
shopt -s globstar
for file in ./**; do 
    if [[ -f "$file" ]]; then
        dirname="${file%/*}/"
        basename="${file:${#dirname}}"
        #echo mv "$file" "$dirname${basename%.*}$basename"
        echo mv "$file" "$dirname${i%.*}$basename"
    fi
done
