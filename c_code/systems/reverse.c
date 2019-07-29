/**
 * @file reverse.c
 *
 * @author Casey Haynes
 *
 * @date 05/1/2019
 *
 * Assignment: HW 3
 *
 * @brief Reverses a file to an output
 *
 * @bugs none
 *
 * @todo none
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
#include <string.h>

void print_help();
ssize_t read_all(int fd, void * const buf, size_t n);
char *strrev(char *str);

int main(int argc, char **argv)
{
        char * infile = NULL;
        char * outfile = NULL;
        int cflag = 0;
        int lflag = 0;
        int rflag = 0;
        int c = 0;

        long pagesize = sysconf(_SC_PAGESIZE);
        if (pagesize == -1){
                err_sys("sysconf");
        }

        char * buf = malloc(pagesize * sizeof(char));
        char * printbuf = malloc(pagesize * sizeof(char));

        while(( c = getopt( argc, argv, "i:o:clrh" )) != -1 ){
                switch (c) {
                        case 'h':
                                print_help();
                                break;
                        case 'i':
                                infile = optarg;
                                break;
                        case 'o':
                                outfile = optarg;
                                break;
                        case 'c':
                                cflag = 1;
                                break;
                        case 'l':
                                lflag = 1;
                                break;
                        case 'r':
                                rflag = 1;
                                break;
                }
        }
        if (infile == NULL){
                printf("wrong\n");
                printf("Reverses the input file is a series of ways\n");
                printf("Usage: ./reverse {-i [file] -o [file] -c -l -r -h}\n");
                printf("Required Arguments:\n");
                printf("-i [file] specify an input file\n");
                printf("Optional Arguments:\n");
                printf("-o [file] specify an output file\n");
                printf("-c reverses the characters of the file\n");
                printf("-l reverses the contents of lines \n");
                printf("-r reverses the lines of the file\n");
                printf("-h prints this help message\n");
        }
        int in_fd = 0;
        int out_fd = 0;
        int readret = 0;

        in_fd = open(infile, S_IRUSR);
        if (in_fd == -1){
                err_sys("open");
        }
        if(outfile != NULL){
                out_fd = open(outfile, O_CREAT|O_WRONLY|O_TRUNC, 0600);
                if (out_fd == -1){
                        err_sys("open");
                }
        } else {
                out_fd = dup(STDOUT_FILENO);
                if (out_fd == -1){
                        err_sys("dup");
                }
        }
        do{
                for (int k = 0; k < pagesize; k++){
                        *(buf + k) = 0;
                        *(printbuf + k) = 0;
                }
                readret = read_all(in_fd, buf, pagesize);

                if(cflag == 1){
                        char* p = buf;
                        char* q = buf;
                        q = memchr(p, 0, pagesize);
                        int i = 0;
                        while(q != p){
                                q--;
                                *(printbuf + i) = *q;
                                i++;
                        }
                        //printf("%s\n", printbuf);
                }

                if (lflag == 1){
                        char* p = buf;
                        char * q = buf;
                        int num = 0;

                        while(p != NULL ){
                                for (int k = 0; k < pagesize; k++){
                                        *(printbuf + k) = 0;
                                }
                                p = memchr(q, '\n', pagesize);
                                //printf("p: %p buf: %p\n", p, q);

                                num = p - q;
                                //printf("num: %d\n", num );


                                for(int i = 0; i < num; i++){
                                        *(printbuf + i) = *(q + i);
                                        //printf("%c\n", *(q + i));
                                        //printf("%d\n", i);
                                }
                                //printf("%p %p\n",p,q );
                                q = p+1;
                                //printf("%d\n", num);
                                //printf("%s\n",printbuf);
                                write(out_fd, strrev(printbuf), num);
                                write(out_fd, "\n", 1);

                        }

                }

        } while(readret != 0);


        //close(buf);
        //close(printbuf);
        return 0;
}

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
                } else if (nread == 0) //EOF
                        break;
                nleft -= nread;
                p += nread;
        }

        return n - nleft; //this should be zero
}

char *strrev(char *str)
{
    if (!str || ! *str)
        return str;

    int i = strlen(str) - 1, j = 0;

    char ch;
    while (i > j)
    {
        ch = str[i];
        str[i] = str[j];
        str[j] = ch;
        i--;
        j++;
    }
    return str;
}
