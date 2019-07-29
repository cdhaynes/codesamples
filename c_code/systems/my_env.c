/** @file my_env.c
 *  @author Casey Haynes
 *  @date 02/23/2019
 *  @brief Implements a custom version of "env"
 *  @bugs none
 *  @todo Patch up memory leaks
 */
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>
#include "./apue.3e/include/apue.h"

void clear_env(char **argv, int argc);
void nameval(char *arg);

int main(int argc, char **argv, char **envp) {
    char *instruction = NULL;
    if (argc < 2) { /*Handle case for which no arguments are given */
        int i = 0;
        while (envp[i] != NULL) {
            if (envp[i + 1] != NULL) {
                printf("[%s] :: ", envp[i++]);
            } else {
                printf("[%s]\n", envp[i++]);
            }
        }
    } else {
        int i = 0;
        int incr = 0;
        int i_flag = 0;
        while (argc - ++i > 0) {
            if ((strcmp(argv[i], "-i") == 0 || strcmp(argv[1], "-") == 0) && i_flag == 0) {
                clear_env(argv, argc);
                i_flag++;
            } else if (strcmp(argv[i], "-v") == 0) {
                printf("MyEnv, by Casey Haynes. Modeled after GNU version, not POSIX. Live Free or Die!\n");
                exit(EXIT_SUCCESS);
            } else if ((strstr(argv[i], "=") != NULL && incr == 0) && i_flag == 0) {
                nameval(argv[i]);
            } else if (strcmp(argv[i], "-h") == 0) {
                printf("./my_env [options] [name=value] [instruction [arg]...]\n");
                exit(EXIT_SUCCESS);
            } else if ((i < argc) != 0) {
                char *a = NULL;

                if (instruction != NULL) {
                    a = malloc(sizeof(char) * (strlen(argv[i]) + 1 + strlen(instruction)));
                    assert(a);
                    a = strcpy(a, instruction);
                } else {
                    a = malloc(sizeof(char) * (strlen(argv[i]) + 1));
                    assert(a);
                }
                if (incr == 0) {
                    instruction = argv[i];
                    incr = 1;
                } else {
                    a = strcat(a, " ");
                    a = strcat(a, argv[i]);
                    instruction = a;
                }
            }
        }
        if (instruction != NULL) {
            int e_status = system(instruction);
            if (e_status != 0) {
                err_sys("Error.\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    return 0;
}
/** Checks for = in string to determine name/value pair
* @param in the string to check
*/
void nameval(char *in) {
    char *args = malloc(sizeof(char) * strlen(in));
    args = strcpy(args, in);
    char *delta = strtok(args, "=");
    int status = setenv(delta, strtok(NULL, " "), 1);
    if (status != 0) {
        err_sys("sh: 0: Invalid option -\n");
        free(args);
        exit(EXIT_FAILURE);
    }
}
/** Wipes the current environment and sets it with specified parameters
* @param argv the given arguments
* @param argc the number of arguments
*/
void clear_env(char **argv, int argc) {
    int *slots = malloc(sizeof(int));
    int modulations = 0;
    int offset = 0;
    int i = 0;
    while (i < argc) {
        if (strstr(argv[i], "=") != NULL && offset == 0) {
            slots[modulations++] = i;
            slots = realloc(slots, sizeof(int) * (modulations + 1));
        } else if (i > 1) {
            offset++;
        }
        i++;
    }
    char **s = malloc(sizeof(char *) * modulations);
    assert(s);
    i = 0;
    while (i < modulations) {
        s[i] = argv[slots[i]];
        i++;
    }
    free(slots);
    slots = NULL;
    for (int i = 0; i < modulations; i++) {
        nameval(s[i]);
    }
    free(s);
    s = NULL;
}
