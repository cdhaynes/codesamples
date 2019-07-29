#!/bin/bash

#************************************************
# filename: file.sh
# description: Displays file metadata
# author: Casey Haynes
# assignment: Hwk1 Q7
# assigned: Jan 28, 2019
# due: Feb 11, 2019
#*************************************************

name=''

usage() {
        printf 'Display metadata for a file\n'
        printf '\055f The file to get metadata on\n'
        printf '\055h display help message\n'
}

main () {
        stat --printf "File: %n\n" $name

        stat --printf 'File Type: %F\n' $name
        printf '\n'
        stat --printf 'Permissions: %a\n' $name
        stat $name -c %A | awk -v FIELDWIDTHS="1:3 3 3" '{printf"user: %s\ngroup: %s\nother %s\n", $1, $2, $3}'

        printf "Setuid: "
        if [ -u $name ]; then
                printf 'yes\n'
        else
                printf 'no\n'
        fi
        printf 'Setgid: '
        if [ -g $name ]; then
                printf 'yes\n'
        else
                printf 'no\n'
        fi
        printf 'Sticky Bit Set: '
        if [ -k $name ]; then
                printf 'yes\n'
        else
                printf 'no\n'
        fi

        stat --printf 'Owned By Effective User-ID: %u\n' $name
        stat --printf 'Owned By Effective Group-ID: %g\n' $name
        printf '\n'
        stat --printf 'Inode: %i\n' $name
        printf '\n'
        stat --printf 'Size bytes: %s\n' $name
        var= stat $name --printf %B
        var=$((var*512))
        stat --printf '512 Blocks: %B (%d)\n' $name
        printf '\n'
        stat --printf 'Links: %h\n' $name
        printf '\n'
        stat --printf 'Access: %x\n' $name
        stat --printf 'Modify: %y\n' $name
        stat --printf 'Change: %z\n' $name


}

while getopts "f:h" opt; do

        case $opt in
        h) usage
           exit
           ;;
        f) name=$OPTARG
           ;;
        esac

done

main

exit 0
