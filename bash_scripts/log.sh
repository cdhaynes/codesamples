#!/bin/bash

#************************************************
# filename: log.sh
# description: Displays login information
# author: Casey Haynes
# assignment: Hwk1 Q6
# assigned: Jan 28, 2019
# due: Feb 11, 2019
#*************************************************


incognito_flag=0 #tell whether or not -n has been invoked

usage () {
        printf 'Display login information for users on this machine\n'
        printf '\055n print users who have never logged in\n'
        printf '\055h print this statement\n'
}

print_nevers () {
        printf 'Users who have never logged in:\n'
        printf 'uname (UID)\n'
        lastlog | grep "**Never logged in**" | awk '{printf("%s\n",$1)}' | {
                while read -d $'\n'; do
                        grep "$REPLY" /etc/passwd | awk -F : '{printf("%s (%s)\n"), $1, $3}'
                done
        }
}

print_regs () {
        who | awk -F \t '{printf("%s\n", $1)}' | {
                while read -d $'\n'; do
                        grep "$REPLY" /etc/passwd | awk -F : '{printf("%s (%s) shell: %s\n", $1, $3, $7)}'
                        sleep 0.001 #put a delay between printing separate lines
                        lastlog | grep "$REPLY" | awk '{printf("last login from %s on %s %s %s %s %s %s\n", $1, $3, $4, $5, $6, $7, $8)}'
                done
        }
}


main () {
        if [ $incognito_flag == 1 ]; then
                print_nevers
                exit 0
        else
                print_regs
                exit 0
        fi
}

while getopts "nh" opt; do
        case $opt in
        n) incognito_flag=1
           ;;
        h) usage
           exit 0
           ;;
        esac
done

main

exit 0
