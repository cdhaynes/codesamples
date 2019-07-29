/**
 * @file tee.c
 *
 * @author Casey Haynes
 *
 * @date 05/1/2019
 *
 * Assignment: HW 3
 *
 * @brief duplicates tee
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


ssize_t read_all(int fd, void * const buf, size_t n);
int args_process(int argc, char ** argv);

int main(int argc, char **argv){
        int i = 1;
        int j = 0;
        int fd = -1;
        int aflag = 0;
        if(argc > 1){
                aflag = args_process(argc, argv);
        } else {
                printf("Wrong input\n");
                exit(0);
        }

        /*get the page size*/
        long pagesize = sysconf(_SC_PAGESIZE);
        if (pagesize == -1){
                err_sys("sysconf");
        }


        char *buf = malloc(pagesize * sizeof(char));
        assert(buf);
        int * files = malloc(argc * sizeof(int));
        assert(files);

        while (i < argc){
                if (argv[i][0] != '-'){
                        char * outfile = argv[i];
                        if (aflag == 1){
                                fd = open(outfile, O_CREAT|O_WRONLY|O_APPEND, 0666 );
                                if (fd == -1){
                                        printf("%s\n", argv[i]);
                                        err_sys("open");
                                }
                        } else {
                                fd = open(outfile, O_CREAT|O_WRONLY|O_TRUNC, 0666 );
                                if (fd == -1){
                                        printf("%s\n", argv[i]);
                                        err_sys("open");
                                }
                        }
                        if(fd != 0){
                                printf("%d\n", fd);
                                files[j] = fd;
                                j++;
                                fd = 0;
                        }
                }
                i++;
        }
        read_all(STDIN_FILENO, buf, pagesize);
        printf("%s", buf);

        i = 0;
        while (i < j){
                int werr = write(files[i], buf, pagesize);
                if (werr == -1){
                        printf("%d\t%d\n", files[i], i);
                        err_sys("write");
                }
                i++;
                close(files[i]);
        }

        free(buf);
        free(files);
        return 0;

}


//read n bytes from fd
ssize_t read_all(int fd, void * const buf, size_t n)
{
        size_t nleft = n;
        ssize_t nread;
        char *p = buf;

        while (nleft > 0 ) {
                if ((nread = read(fd, p, nleft)) == -1) {
                        if (errno == EINTR)
                                nread = 0;
                        else
                                return -1;
                } else if (nread == 0)
                        break;
                nleft -= nread;
                p += nread;
        }

        return n - nleft;
}

int args_process(int argc, char ** argv){
        int aflag = 0;
        char c;

        while(( c = getopt( argc, argv, "a:h" )) != -1 ){
            switch (c) {
                    case 'h':
                        printf("Usage: %s -a [file]\n", argv[0]);
                        printf("\nOptional arguments:\n" );
                        printf("-h Print help menu\n");
                        printf("-a Append output to file\n");
                        exit(0);
                        break;
                    case 'a':
                        aflag = 1;
                        break;
            }
        }
        return aflag;
}
