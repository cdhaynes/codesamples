/** @file lsinode.c
 *  @author Casey Haynes
 *  @date 03/30/2019
 *  @brief Prints information about all files within a given directory. .
 *  @bugs Can't print the actual Symlinks, just whether or not they exist
 *  @todo De-Spaghettify, fix aforementioned bug.
 */
#include "print_stat.h"

int main (int argc, char *argv[]) {
        struct dirent **de;
        struct stat statbuf[sizeof(struct stat)];
        struct passwd *pw;
        struct group *grp;
        int num_files;
        int field_width = 10;
        if (argv[1] == NULL) {
                printf("No directory given\n");
                return -1;
        }

        num_files = scandir(argv[1], &de, NULL, alphasort);
        if (num_files == -1) {
                perror("Scanning Directory Failed");
        }


        int max_file_size = 0;
        for(int i = 0; i < num_files; i++) {
                lstat(de[i]->d_name, statbuf);
                int file_size = statbuf->st_size;
                int file_field_size = 0;

                while (file_size != 0) {
                        file_field_size++;
                        file_size = file_size / 10;
                }

                if (file_field_size > max_file_size) {
                        max_file_size = file_field_size;
                }

        }
        for (int i = 0; i < num_files; i++) {
                int max_links_len = 0;
                int links_len = 0;
                int max_inode_len = 0;
                int inode_len = 0;
                int s = statbuf->st_nlink;
                int inode = statbuf->st_ino;

                while (s != 0) {
                        links_len++;
                        s = s / 10;
                }
                if (links_len > max_links_len) {
                        max_links_len = links_len;
                }

                while (inode != 0) {
                        inode_len++;
                        inode = inode / 10;
                }
                if (inode_len > max_inode_len) {
                        max_inode_len = inode_len;
                }

                int usr_size = 0;
                int max_usr_size = 0;
                int grp_size = 0;
                int max_grp_size = 0;
                pw = getpwuid(statbuf->st_uid);
                grp = getgrgid(statbuf->st_gid);
                usr_size = strlen(pw->pw_name);
                grp_size = strlen(grp->gr_name);

                if (usr_size > max_usr_size) {
                        max_usr_size = usr_size;
                }

                if (grp_size > max_grp_size) {
                        max_grp_size = grp_size;
                }

                int newdir = chdir(argv[1]);
                if (newdir == -1) {
                        perror("Couldn't change directory");
                }
                lstat(de[i]->d_name, statbuf);
                char *symlink = NULL;
                if (de[i]->d_type == DT_LNK) {
                        symlink = "This is a symlink";
                }
                print_stat(statbuf, de[i]->d_name, symlink, field_width);

        }
        for (int i = 0; i < num_files; i++) {
                free(de[i]);
        }
        free(de);
        return 0;
}
