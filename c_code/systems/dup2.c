/**
 * @file dup2.c
 *
 * @author Casey Haynes
 *
 * @date 05/1/2019
 *
 * Assignment: HW 3
 *
 * @brief recreates dup2
 *
 *
 * @bugs
 *
 * @todo
 */
#include <stdio.h>
#include "./apue/include/apue.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <errno.h>
#include <assert.h>
#include <ctype.h>

int mydup2(int old_fd, int new_fd);

int main(int argc, char const *argv[]) {
        int fd = 0;
        int err = 0;
        char buf[4098];
        fd = open("test", S_IRUSR);
        fd = mydup2(fd, 10);
        if (fd == -1){
                printf("fd's not right\n");
        }
        printf("fd: %d\n", fd);
        err = read(fd, buf, sizeof(buf));
        if (err == -1){
                err_sys("read error");
        }
        printf("%s\n ", buf);
        printf("File Descriptor: %d\n", fd );
        close(fd);

        return 0;
}

int mydup2(int old_fd, int new_fd){
        int temp_fd = old_fd;
        int err = 0;
        /*duplicates the fd into all of the fd's between the target and the original*/
        while (temp_fd < new_fd){
                temp_fd = dup(old_fd);
                if (temp_fd == -1){
                        return -1;
                }
        }
        /*closes all of the uneccisary fd's*/
        while(temp_fd > old_fd){
                temp_fd--;
                //printf("CLOSED: %d\n", temp_fd);
                err = close(temp_fd);
                if (err == -1){
                        return -1;
                }
        }
        return new_fd;
}
