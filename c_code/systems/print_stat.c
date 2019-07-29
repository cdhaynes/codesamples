/** @file print_stat.c
 *  @author Casey Haynes
 *  @date 03/30/2019
 *  @brief Library which lsinode uses. .
 *  @bugs none
 *  @todo 
 */
#include "print_stat.h"

void print_stat (struct stat *statbuf, char* de, char* symlink, int field_width) {
        struct passwd *pw;
        struct group *grp;
        char buf[1024];
        DIR *dr = opendir(".");

        if (dr == NULL) {
                printf("Specified directory doesn't exist.");
        }


                printf( (S_ISDIR(statbuf->st_mode)) ? "d" : "-");
                printf( (statbuf->st_mode & S_IRUSR) ? "r" : "-");
                printf( (statbuf->st_mode & S_IWUSR) ? "w" : "-");
                printf( (statbuf->st_mode & S_IXUSR) ? "x" : "-");
                printf( (statbuf->st_mode & S_IRGRP) ? "r" : "-");
                printf( (statbuf->st_mode & S_IWGRP) ? "w" : "-");
                printf( (statbuf->st_mode & S_IXGRP) ? "x" : "-");
                printf( (statbuf->st_mode & S_IROTH) ? "r" : "-");
                printf( (statbuf->st_mode & S_IWOTH) ? "w" : "-");
                printf( (statbuf->st_mode & S_IXOTH) ? "x " : "- ");
                printf("%*ld ", field_width, statbuf->st_nlink);
                printf("%*ld ", field_width, statbuf->st_ino);
                pw = getpwuid(statbuf->st_uid);
                grp = getgrgid(statbuf->st_gid);
                printf("%*s ", field_width, pw->pw_name);
                printf("%*s ", field_width, grp->gr_name);
                printf("%*ld ", field_width, statbuf->st_size);
                struct tm epoch;
                memcpy(&epoch, localtime(&statbuf->st_mtime), sizeof(struct tm));
                strftime(buf, 1024, "%b %d %T", &epoch);
                printf("%s ", buf);
                printf("%s", de);
                if (symlink != NULL) {
                        printf(" -> %s", symlink);
                }
                printf("\n");

}
