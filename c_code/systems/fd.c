/** @file fd.c
 *  @author Casey Haynes
 *  @date 04/13/2019
 *  @brief Defines functions used in most problems of HW5
 *  @bugs none
 *  @todo Implement Conditional Compilation
 */
#include "fd.h"

int *get_open_fd(void) {
        char buf[1024];
        sprintf(buf, "/proc/%d/fd", getpid());
        //printf("/proc/%d/fd", getpid());
        DIR *path = opendir(buf);
        int *info_list = calloc(1, sizeof(int));
        int grow = 1;
        int i = 0;
        struct dirent *f;
        while ((f = readdir(path)) != NULL) {
                if ((strcmp(f->d_name, ".") == 0) || (strcmp(f->d_name, "..") == 0) || (strcmp(f->d_name, "0") == 0) || (strcmp(f->d_name, "1") == 0) || (strcmp(f->d_name, "2") == 0)) {

                } else {
                        int info = atoi(f->d_name);
                        info_list[i] = info;
                        info_list = realloc(info_list, ++grow * sizeof(int));
                        i++;
                }
        }
        return info_list;
}

void cleanup_fd(void) {
        int *fd_array = get_open_fd();
        int i = 0;
        while(fd_array[i] != '\0') {
                printf("closing %d\n", fd_array[i]);
                int close_test = close(fd_array[i]);
                if (close_test < 0) {
                        perror("close failed\n");
                        exit(EXIT_FAILURE);
                }
                i++;
        }
        printf("cleanup done!\n");
}
