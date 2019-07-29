#!/bin/bash

#************************************************
# filename: tar.sh
# description: Tars files
# author: Casey Haynes
# assignment: Hwk1 Q5
# assigned: Jan 28, 2019
# due: Feb 11, 2019
#*************************************************

dir='./'
name=''

usage() {
        printf 'tar some files\n'
        printf '\055n desired name of tarball (include .tar.gz)\n'
        printf '\055d directory in which to navigate to and fabricate the tarball (must be absolute path)\n'
        printf '\055c perform make clean before tarring\n'
        printf '\055h display this help message\n'
}

make_verify() {
        if [ ! -f "Makefile" ]; then
                printf 'No Makefile Found. Goodbye\n'
                exit
	fi
}

make_clean() {
        make clean
}

main() {
	cd $dir
        make_verify
        tar -czvf $name *.c *.h Makefile
}

while getopts "n:d:ch" opt; do

        case $opt in
        h) usage
           exit
           ;;
        c) make_clean
           main
	   ;;
        d) dir=$OPTARG
           ;;
        n) name=$OPTARG
           ;;
        esac

done

main

exit 0
