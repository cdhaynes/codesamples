/** @file server.c
 *  @author Casey Haynes / Scott Chadde (probably)
 *  @date 04/25/2019
 *  @brief modified version of server, child process does grunt work and sends data back to the server (parent)
 *  @bugs none
 *  @todo
 */
#include "fifo.h"

//runs as
//$ server&
//$ client
//enter a filename: /etc/passwd

int main(int argc, char **argv)
{
        int read_fifo;
        int write_fifo;
        int fd;
        int dummy_fd;

        char *ptr;
        char buf[LEN];
        char fifoname[LEN];

        pid_t pid;
        ssize_t n;
        int fdp[2];

        if (mkfifo(SERV_FIFO, FILE_MODE) < 0 && errno != EEXIST)
                err_sys("mkfifo");

        if ((read_fifo = open(SERV_FIFO, O_RDONLY)) == -1)
                err_sys("open SERV_FIFO");

        //dummy fd
        //If not opened for writing, each time a client terminates
        //the FIFO becomes empty and the servers read returns 0 indicating EOF.
        //Would have to close the FIFO and call open again.
        //opening a dummy fd prevents having to close the FIFO
        //read will never return 0 to indicate EOF when no clients exist
        //server will block in the call to read, waiting for the next client
        if ((dummy_fd = open(SERV_FIFO, O_WRONLY)) == -1)
                err_sys("open SERV_FIFO");

                /*begin*/
                if (pipe(fdp) < 0) {
                        err_sys("pipe");
                }
                pid_t pid0 = fork();
                if (pid0 < 0) {
                        err_sys("fork");
                } else if (pid0 == 0) { /*child process */
                        while ((n = read(read_fifo, buf, LEN)) > 0) {

                                //client will send
                                //PID pathname
                                //PID is used to create unique filenames
                                //i.e., you know who the client is and can communicate with
                                //the correct client
                                if (buf[n - 1] == '\n')
                                        n--;

                                buf[n] = '\0';

                                //simple check for a space
                                //separating PID and pathname
                                if ((ptr = strchr(buf, ' ')) == NULL) {
                                        err_msg("no space ignoring");
                                        continue;
                                }

                                *ptr++ = 0; //move ptr to the pathname; buf is the PID
                                pid = atol(buf); //get pid

                                //create filename
                                snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);

                                //the FIFO was opened by the client
                                if ((write_fifo = open(fifoname, O_WRONLY)) < 0) {
                                        err_msg("open write_fifo");
                                        continue;
                                }

                                //open the file
                                //send back the error or send the cont
                        if ((read_fifo = open(SERV_FIFO, O_RDONLY)) == -1)
                                err_sys("open SERV_FIFO");

                        //dummy fd
                        //If not opened for writing, each time a client terminates
                        //the FIFO becomes empty and the servers read returns 0 indicating EOF.
                        //Would have to close the FIFO and call open again.
                        //openents of the file
                                if ((fd = open(ptr, O_RDONLY)) < 0) {
                                        //tell client
                                        snprintf(buf + n, sizeof(buf) - n, ": can't open %s\n", strerror(errno));
                                        n = strlen(ptr);
                                        /*begin */
                                        int ct = close(fdp[0]);
                                        if (ct < 0) {
                                                err_sys("close");
                                        }

                                        if (write(fdp[1], ptr, n) != n)
                                                err_sys("write write_fifo");

                                        if (close(fdp[1]) == -1)
                                                err_sys("close");
                                        /*end*/
                                } else {
                                        while ((n = read(fd, buf, LEN)) > 0)
                                                if (write(fdp[1], buf, n) != n)
                                                        err_sys("write write_fifo");

                                        if (close(fd) == -1)
                                                err_sys("close");

                                        if (close(write_fifo) == -1)
                                                err_sys("close");
                                }
                        }
                        /*begin*/
                } else { /*parent process*/
                        n = read(fdp[0], buf, LEN);
                        write(STDOUT_FILENO, buf, LEN);
                        /*end*/
                }
                /*end*/



}
