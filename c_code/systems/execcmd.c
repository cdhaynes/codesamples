/** @file execcmd.c
 *  @author Casey Haynes
 *  @date 04/13/2019
 *  @brief Executes a program passed in from command line
 *  @bugs none
 *  @todo 
 */

#include "fd.h"

int main (int argc, char **argv) {
	int pid = fork();
        char *command = argv[1];
        argv = argv + 1;
        switch(pid) {
                case 0:
                        execvp(command, argv);
                        break;
                case -1:
                        perror("fork failed, child process not created");
                        exit(EXIT_FAILURE);
        }

	/* Put the parent to sleep, let the child finish executing */
        //int *wstatus = WEXITSTATUS;
	wait(&pid);
        printf("child fini\n");
        int exit_status = WIFEXITED(pid) && WEXITSTATUS(pid);
        printf("normal exit status = %d\n", exit_status);
        exit(EXIT_SUCCESS);
}
