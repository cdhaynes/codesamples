/**
 * @file wc.c
 *
 * @author Casey Haynes
 *
 * @date 05/1/2019
 *
 * Assignment: HW 3
 *
 * @brief duplicates wordcount
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

ssize_t read_all(int fd, void * const buf, size_t n);
int args_process(int argc, char ** argv);
char* print_type(int flag, int pagesize, int lines, int words, int characters, char* file);

int main(int argc, char **argv) {
        int pflag = 0;
        int hasfile = 0;
        int fd = -1;
        int lines = 0;
        int words = 0;
        int characters = 0;

        long pagesize = sysconf(_SC_PAGESIZE);
        if (pagesize == -1){
                err_sys("Sysconf Error:");
        }

        char * buf = malloc(pagesize * sizeof(char));

        pflag = args_process(argc, argv);

        int i = 0;
        while (i < argc){
                if (argv[i][0] != '-'){
                        hasfile = i;
                }
                i++;
        }

        if (hasfile != 0 || argc > 2){
                fd = open(argv[hasfile], S_IRUSR);
                if (fd == -1){
                        err_sys("Open Error");
                }
                int readret = 0;
                char * out = NULL;


                do {
                        i = 0;
                        for (int k = 0; k < pagesize; k++){
                                *(buf + k) = 0;
                        }
                        readret = read_all(fd, buf, pagesize);

                        while(*(buf + i) != 0 ){
                                if (*(buf + i) == '\n'){
                                        lines++;
                                }

                                if((isspace(*(buf + i)) && isalpha(*(buf + (i - 1)))) || (isspace(*(buf + i)) && isalpha(*(buf + (i + 1))))){
                                        words++;
                                }
                                characters = lseek(fd, 0,SEEK_CUR);
                                i++;
                        }
                } while(readret != 0);

                out = print_type(pflag, pagesize, lines, words, characters, argv[hasfile]);

                int werr = write(STDIN_FILENO, out, pagesize);
                if(werr == -1){
                        err_sys("Write Error");
                }




        } else {
                fd = STDIN_FILENO;
                if (fd == -1){
                        err_sys("Open Error");
                }
                int readret = 0;
                char * out = NULL;
                printf("%d\n", fd);


                do {
                        i = 0;
                        for (int k = 0; k < pagesize; k++){
                                *(buf + k) = 0;
                        }
                        readret = read_all(fd, buf, pagesize);

                        while(*(buf + i) != 0 ){
                                if (*(buf + i) == '\n'){
                                        lines++;
                                }

                                if((isspace(*(buf + i)) && isascii(*(buf + i - 1)) ) || (isspace(*(buf + i)) && isascii(*(buf + i + 1)))){
                                        words++;
                                }
                                characters++;
                                i++;
                        }
                } while(readret != 0);

                out = print_type(pflag, pagesize, lines, words, characters, argv[hasfile]);

                int werr = write(STDIN_FILENO, out, pagesize);
                if(werr == -1){
                        err_sys("Write Error");
                }

        }
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
                } else if (nread == 0)
                        break;
                nleft -= nread;
                p += nread;
        }

        return n - nleft;
}


int args_process(int argc, char ** argv){
        int flag = 0;
        int c = 0;

        while(( c = getopt( argc, argv, "cwlh" )) != -1 ){
            switch (c) {
                    case 'h':
                        printf("Usage: %s [-c -w -l] [file]\n", argv[0]);
                        printf("\nOptional arguments:\n" );
                        printf("-h Print help menu\n");
                        printf("-c prints the number of bytes in file \n");
                        printf("-w prints the number of words in file \n");
                        printf("-l prints the number of lines in file \n");
                        exit(0);
                        break;
                    case 'c':
                        flag += 1;
                        break;
                    case 'w':
                        flag += 2;
                        break;
                    case 'l':
                        flag += 4;
                        break;
            }
        }
        return flag;
}

char* print_type(int flag, int pagesize, int lines, int words, int characters, char* file){
        int err = 0;
        char *out = malloc(pagesize * sizeof(char));
        switch (flag) {
                case 1:
                        err = snprintf(out, pagesize, "%d\t%s\n", characters, file );
                        break;
                case 2:
                        err = snprintf(out, pagesize, "%d\t%s\n", words, file );
                        break;
                case 3:
                        err = snprintf(out, pagesize, "%d\t%d\t%s\n", words, characters, file );
                        break;
                case 4:
                        err = snprintf(out, pagesize, "%d\t%s\n", lines, file );
                        break;
                case 5:
                        err = snprintf(out, pagesize, "%d\t%d\t%s\n", lines, characters, file );
                        break;
                case 6:
                        err = snprintf(out, pagesize, "%d\t%d\t%s\n", lines, words, file );
                        break;
                case 0:
                case 7:
                        err = snprintf(out, pagesize, "%d\t%d\t%d\t%s\n", lines, words, characters, file );
                        break;
        }

        return out;

}
