/** @file pipe.c
 *  @author Casey Haynes
 *  @date 04/25/2019
 *  @brief emulates an ncal piped into grep, using parent/child processes connected via pipe
 *  @bugs none
 *  @todo
 */
#include "fd.h"

int main (int argc, char *argv[]) {
        int fd[2];
        pid_t pid0, pid1;
        char line[MAXLINE];
        int year = 0;
        char *pattern = NULL;

        int c;
        while((c = getopt(argc, argv, ":y:d:")) != -1) {
                 switch (c) {
                         case 'y':
                                year = atoi(optarg);
                                break;
                        case 'd':
                                pattern = optarg;
                                break;
                        default:
                                printf("usage: -y year -d pattern to search for\n");
                                exit(1);
                                break;
                 }
         }

        if (pipe(fd) < 0) {
                err_sys("pipe error");
        }
        pid0 = fork();
        if (pid0 < 0) {
                err_sys("fork error");
        } else if (pid0 == 0) { /* Child 0 */
                int ct = close(fd[0]); /*Close pipe output*/
                if (ct < 0) {
                        err_sys("close failed\n");
                }
                int dt = dup2(fd[1], 1); /* fd[1] is also stdout as well as input to pipe */
                close(fd[1]);
                if (dt < 0) {
                        err_sys("dup failed\n");
                }
                char buf[24];
                sprintf(buf, "%d", year);
                int et = execlp("ncal", "ncal", buf, NULL);
                if (et < 0) {
                        err_sys("exec failed\n");
                }
                //write(fd[1], "c'est une pipe", 14); /*write to the pipe */
        }
        pid1 = fork();
        if (pid1 < 0) {
                err_sys("fork error");
        } else if (pid1 == 0) { /* Child 1 */
                int close_test = close(fd[1]); /*Close pipe input*/
                if (close_test < 0) {
                        err_sys("close failed\n");
                }

                dup2(fd[0], 0);
                close(fd[0]);
                char bug[24];
                sprintf(bug, "%s", pattern);
                int tst = execlp("grep", "grep", bug, NULL);
                if (tst < 0) {
                        err_sys("exec failed\n");
                }
                fflush(stdout);
                /*int wt = write(STDOUT_FILENO, line, 1024); /*write to stdout*/
                /* if (wt < 0) {
                        err_sys("write failed\n");
                } */

        }

        close(fd[0]);
        close(fd[1]);
        waitpid(pid0, NULL, 0);
        waitpid(pid1, NULL, 0);

        exit(0);
}
