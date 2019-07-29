/** @file client.c
 *  @author Casey Haynes / Scott Chadde (probably)
 *  @date 04/25/2019
 *  @brief The provided version of client. Prints out file data.
 *  @bugs none
 *  @todo
 */
#include "fifo.h"

int main(int argc, char **argv)
{
        int read_fifo;
        int write_fifo;
        size_t len;

        char *ptr;
        char buf[LEN];
        char fifoname[LEN];
 
        pid_t pid = getpid();
        ssize_t n;

        snprintf(fifoname, sizeof(fifoname), "/tmp/fifo.%ld", (long)pid);
       
        //create FIF0 with name of fifo.PID
        //the server will open this FIFO
        if (mkfifo(fifoname, FILE_MODE) < 0 && errno != EEXIST) 
                err_sys("mkfifo");

        if (write(STDOUT_FILENO, "enter a filename: ", strlen("enter a filename: ")) == -1)
              err_sys("write failed");

        //build string "PID filename" to send to server
        
        //get pid
        snprintf(buf, sizeof(buf), "%ld ", (long)pid);
        len = strlen(buf);
        ptr = buf + len;
        //append filename
        if (fgets(ptr, LEN - len, stdin) == NULL)
                err_sys("fgets");
        len = strlen(buf);

        //server created this FIFO
        if ((write_fifo = open(SERV_FIFO, O_WRONLY)) == -1)
                err_sys("open SERV_FIFO");

        if (write(write_fifo, buf, len) != len)
                err_sys("write write_fifo");

        //this blocks until server FIFO opens for writing
        if ((read_fifo = open(fifoname, O_RDONLY)) == -1)
                err_sys("open fifoname");

        while ((n = read(read_fifo, buf, LEN)) > 0) {
                if (write(STDOUT_FILENO, buf, n) != n)
                      err_sys("write stdout");
        }

        if (close(read_fifo) == -1)
                err_sys("close");

        if (unlink(fifoname) == -1)
                err_sys("unlink");

        exit(0);
} 
