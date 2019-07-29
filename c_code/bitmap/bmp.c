/**
* @file bmp.c
*
* @author Casey D. Haynes
*
* @date 4/09/2019
*
* Assignment: Bitmap Project
*
* @brief Reads and manipulates 8 bpp and 24 bpp bitmaps
*
* @details
*
* @bugs doesn't properly display the size in bytes of bitmaps (-i -d)
*
* @todo fix that bug, de-spaghettify (REALLY de-spaghettify), implement more robust form of pagesize.
*/
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include <assert.h>
#include "./apue/include/apue.h"


ssize_t read_all(int fd, void * const buf, size_t n);

struct header { /* Header is 54 bytes wide for 8 bpp and 24bpp bitmaps */
        /* BMP data start */
        char type[2]; /* 0x42 0x4D */
        int size_bmp;
        short reserved_0;
        short reserved_1;
        int offset;
        /* DIB data start */
        int size_dib_header;
        int bmp_width;
        int bmp_height;
        short color_planes; /* Should be 1 */
        short bpp; /* (Color Depth) */
        int compression_method;
        int image_size;
        int horiz_resolution;
        int vert_resolution;
        int no_colors; /* number of colors */
        int no_important_colors; /* number of important colors */
};

int main (int argc, char **argv) {
        struct header BMP_header;
        int c;
        if (argc < 2) {
                printf("Usage:\n");
                printf("**NOTE**, the input file MUST be the first argument!\n");
                printf("bmp FILE [-o FILE] [-i] [-d] [-R] [-r N] [-g N] [-b N] -h\n");
                printf("FILE = input file\n");
                printf("[-o FILE] = the output file\n");
                printf("[-i] = display bitmap header and DIB header info\n");
                printf("[-d] = a dump of all headers, color table (if present), and all pixel values\n");
                printf("[-R] = reverse the image of a 8 bpp bmp\n");
                printf("[-r N] = change all reds in a 24 bpp bmp to N\n");
                printf("[-g N] = change all greens in a 24 bpp bmp to N\n");
                printf("[-b N] = change all blues in a 24 bpp bmp to N\n");
                printf("-h = display this message\n");
                return 1;

        }
        int color_table_flag = 0;
        int dump_flag = 0;
        int reverse_flag = 0;
        int red_flag = 0;
        char *set_red_to = NULL;
        int green_flag = 0;
        char *set_green_to = NULL;
        int blue_flag = 0;
        char *set_blue_to = NULL;
        int fd1;
        char *outfile = NULL;
        struct iovec iov[1];
        /* used for writev */
        while ((c = getopt(argc, argv, ":o:idRr:g:b:h")) != -1) {
                switch (c) {
                        case 'o':
                                outfile = optarg;
                                fd1 = open(outfile, O_CREAT | O_RDWR | O_TRUNC, 00644);
                                if (fd1 < 0) {
                                        err_sys("open failed\n");
                                }
                                break;
                        case 'i':
                                printf("\nheader: %s\n", BMP_header.type);
                                printf("size of bitmap (bytes): %d\n", BMP_header.size_bmp);
                                printf("offset (start of image data): %d\n", BMP_header.offset);
                                printf("\nsize of dib: %d\n", BMP_header.size_dib_header);
                                printf("bitmap width in pixels: %d\n", BMP_header.bmp_width);
                                printf("bitmap height in pixels: %d\n", BMP_header.bmp_height);
                                printf("number of color planes: %d\n", BMP_header.color_planes);
                                printf("number of bits per pixel: %d\n", BMP_header.bpp);
                                printf("compression method: %d\n", BMP_header.compression_method);
                                printf("image size: %d\n", BMP_header.image_size);
                                printf("horizontal resolution (pixel per meter): %d\n", BMP_header.horiz_resolution);
                                printf("vertical resolution (pixel per meter): %d\n", BMP_header.vert_resolution);
                                printf("number of colors: %d\n", BMP_header.no_colors);
                                printf("number of important colors: %d\n", BMP_header.no_important_colors);
                                break;
                        case 'd':
                                /* dump of all headers and a color table and pixel values of ea cell */
                                dump_flag = 1;
                                break;
                        case 'R':
                                reverse_flag = 1;
                                break;
                        case 'r':
                                red_flag = 1;
                                set_red_to = optarg;
                                break;
                        case 'g':
                                green_flag = 1;
                                set_green_to = optarg;
                                break;
                        case 'b':
                                blue_flag = 1;
                                set_blue_to = optarg;
                                break;
                        case 'h':
                                printf("Usage:\n");
                                printf("**NOTE**, the input file MUST be the first argument!\n");
                                printf("bmp FILE [-o FILE] [-i] [-d] [-R] [-r N] [-g N] [-b N] -h\n");
                                printf("FILE = input file\n");
                                printf("[-o FILE] = the output file\n");
                                printf("[-i] = display bitmap header and DIB header info\n");
                                printf("[-d] = a dump of all headers, color table (if present), and all pixel values\n");
                                printf("[-R] = reverse the image of a 8 bpp bmp\n");
                                printf("[-r N] = change all reds in a 24 bpp bmp to N\n");
                                printf("[-g N] = change all greens in a 24 bpp bmp to N\n");
                                printf("[-b N] = change all blues in a 24 bpp bmp to N\n");
                                printf("-h = display this message\n");
                                return 1;
                                break;
                        default:
                                printf("Usage:\n");
                                printf("**NOTE**, the input file MUST be the first argument!\n");
                                printf("bmp FILE [-o FILE] [-i] [-d] [-R] [-r N] [-g N] [-b N] -h\n");
                                printf("FILE = input file\n");
                                printf("[-o FILE] = the output file\n");
                                printf("[-i] = display bitmap header and DIB header info\n");
                                printf("[-d] = a dump of all headers, color table (if present), and all pixel values\n");
                                printf("[-R] = reverse the image of a 8 bpp bmp\n");
                                printf("[-r N] = change all reds in a 24 bpp bmp to N\n");
                                printf("[-g N] = change all greens in a 24 bpp bmp to N\n");
                                printf("[-b N] = change all blues in a 24 bpp bmp to N\n");
                                printf("-h = display this message\n");
                                return 1;
                                break;
                }
        }
        char *infile = argv[argc - 1];
        long pagesize = 7000000;
        char buf[pagesize];

        int fd0 = open(infile, O_RDONLY);
        if (fd0 < 0) {
                err_sys("open failed\n");
        }
        int rd0 = read_all(fd0, buf, 54);
        if (rd0 < 0) {
                err_sys("read failed\n");
        }

        /*** Get stuff into the structure ***/
        memcpy(&BMP_header.type, buf, 2);
        memcpy(&BMP_header.size_bmp, (buf + 2), 4);
        memcpy(&BMP_header.reserved_0, (buf + 6), 2);
        memcpy(&BMP_header.reserved_1, (buf + 8), 2);
        memcpy(&BMP_header.offset, (buf + 10), 4);
        memcpy(&BMP_header.size_dib_header, (buf + 14), 4);
        memcpy(&BMP_header.bmp_width, (buf + 18), 4);
        memcpy(&BMP_header.bmp_height, (buf + 22), 4);
        memcpy(&BMP_header.color_planes, (buf + 26), 2);
        memcpy(&BMP_header.bpp, (buf + 28), 2);
        memcpy(&BMP_header.compression_method, (buf + 30), 4);
        memcpy(&BMP_header.image_size, (buf + 34), 4);
        memcpy(&BMP_header.horiz_resolution, (buf + 38), 4);
        memcpy(&BMP_header.vert_resolution, (buf + 42), 4);
        memcpy(&BMP_header.no_colors, (buf + 46), 4);
        memcpy(&BMP_header.no_important_colors, (buf + 50), 4);
        /*** ***/


        /**** Dump Code ****/
        if (dump_flag != 0) {
                printf("\nheader: %s\n", BMP_header.type);
                printf("size of bitmap (bytes): %d\n", BMP_header.size_bmp);
                printf("offset (start of image data): %d\n", BMP_header.offset);
                printf("\nsize of dib: %d\n", BMP_header.size_dib_header);
                printf("bitmap width in pixels: %d\n", BMP_header.bmp_width);
                printf("bitmap height in pixels: %d\n", BMP_header.bmp_height);
                printf("number of color planes: %d\n", BMP_header.color_planes);
                printf("number of bits per pixel: %d\n", BMP_header.bpp);
                printf("compression method: %d\n", BMP_header.compression_method);
                printf("image size: %d\n", BMP_header.image_size);
                printf("horizontal resolution (pixel per meter): %d\n", BMP_header.horiz_resolution);
                printf("vertical resolution (pixel per meter): %d\n", BMP_header.vert_resolution);
                printf("number of colors: %d\n", BMP_header.no_colors);
                printf("number of important colors: %d\n", BMP_header.no_important_colors);
                printf("\n");

                if (BMP_header.offset == 54) {
                        printf("no color table\n\n"); /* 24 bpp */
                } else {
                        color_table_flag = 1; /* 8 bpp */
                }
                if (color_table_flag != 0) {
                        int rd1 = read_all(fd0, buf, (BMP_header.offset - 54));
                        if (rd1 < 0) {
                                err_sys("read_all failed");
                        }
                        printf("Color Table\n");
                        printf("index   red   green   blue   alpha\n");
                        printf("------------------------------------------------------\n");
                        int index = 0;
                        /* print color table */
                        for (int i = 0; i < rd1; i += 4, index++) {
                                printf("%d   %u   %u   %u   %u\n", index, (unsigned char) buf[i + 2], (unsigned char) buf[i + 1], (unsigned char) buf[i], (unsigned char) buf[i + 3]);
                        }
                        printf("\n");
                        /********************/

                        /* print pixel data */
                        printf("Pixel Data\n");
                        printf("(row, col)   index\n");
                        printf("----------------------------------------------------\n");
                        //while (rd_pixel != 0) {

                                int rd_pixel = read_all(fd0, buf, pagesize);
                                if (rd_pixel < 0) {
                                        err_sys("read_all failed\n");
                                }
                                /* Put all pixels into a 2D array */
                                int row = 0;
                                int column = 0;
                                unsigned char map[BMP_header.bmp_width][BMP_header.bmp_height];
                                for (int i = 0; i < rd_pixel; i++) {
                                        map[row][column] = buf[i];
                                        column++;
                                        if (column % BMP_header.bmp_height == 0) {
                                                column = 0;
                                                row++;
                                                if (BMP_header.bmp_width % 4 != 0) {
                                                        i = i + (4 - (BMP_header.bmp_width % 4));
                                                }
                                        }
                                }

                                /* Print all pixels */

                                for(int i = 0; i < BMP_header.bmp_height; i++) {
                                        for (int j = 0; j < BMP_header.bmp_width; j++) {
                                                printf("(%d, %d)   %d\n", i, j, map[i][j]);
                                        }
                                }
                        //}
                } else { /*No color table is present --- 24 bpp*/
                        int rd_pixel;
                        //while (rd_pixel != 0) {
                                rd_pixel = read_all(fd0, buf, pagesize);
                                if (rd_pixel < 0) {
                                        err_sys("read_all failed\n");
                                }
                                int row = 0;
                                int column = 0;
                                printf("(row, col)\tred\tgreen\tblue\n");
                                printf("-------------------------------------------\n");
                                for (int i = 0; i < rd_pixel; i += 3) {
                                        printf("(%d, %d)   %u   %u   %u\n", row, column, (unsigned char) buf[i + 2], (unsigned char) buf[i + 1], (unsigned char) buf[i]);
                                        column++;
                                        if (column % BMP_header.bmp_height == 0) {
                                                if (BMP_header.bmp_width % 4 != 0) {
                                                        i = i + (4 - (BMP_header.bmp_width % 4));
                                                }
                                                column = 0;
                                                row++;
                                        }
                                }
                        //}

                }
        }
        /*** End Dump Code ***/

        if (reverse_flag != 0 || red_flag != 0 || green_flag != 0 || blue_flag != 0) {
                if (reverse_flag != 0) {
                        if (BMP_header.offset == 54) {
                                err_quit("You can't reverse a 24 bpp image\n");
                        } else {
                                char *output_buf = malloc(pagesize * sizeof(char));
                                assert(output_buf);
                                memcpy(output_buf, &BMP_header.type, 2);
                                memcpy((output_buf + 2), &BMP_header.size_bmp, 4);
                                memcpy((output_buf + 6), &BMP_header.reserved_0, 2);
                                memcpy((output_buf + 8), &BMP_header.reserved_1, 2);
                                memcpy((output_buf + 10), &BMP_header.offset, 4);
                                memcpy((output_buf + 14), &BMP_header.size_dib_header, 4);
                                memcpy((output_buf + 18), &BMP_header.bmp_width, 4);
                                memcpy((output_buf + 22), &BMP_header.bmp_height, 4);
                                memcpy((output_buf + 26), &BMP_header.color_planes, 2);
                                memcpy((output_buf + 28), &BMP_header.bpp, 2);
                                memcpy((output_buf + 30), &BMP_header.compression_method, 4);
                                memcpy((output_buf + 34), &BMP_header.image_size, 4);
                                memcpy((output_buf + 38), &BMP_header.horiz_resolution, 4);
                                memcpy((output_buf + 42), &BMP_header.vert_resolution, 4);
                                memcpy((output_buf + 46), &BMP_header.no_colors, 4);
                                memcpy((output_buf + 50), &BMP_header.no_important_colors, 4);
                                int fd_reset = lseek(fd0, 54, 0);
                                if (fd_reset < 0) {
                                        err_sys("lseek failed\n");
                                }
                                int rd1 = read_all(fd0, buf, (BMP_header.offset - 54));
                                if (rd1 < 0) {
                                        err_sys("read_all failed\n");
                                }
                                for (int i = 0; i < rd1; i++) {
                                        int j = i + 54; /* offset to jump over header data */
                                        output_buf[j] = 255 - buf[i];
                                }
                                rd1 = read_all(fd0, buf, pagesize);
                                if (rd1 < 0) {
                                        err_sys("read_all failed\n");
                                }
                                for (int i = 0; i < rd1; i++) {
                                        int j = i + BMP_header.offset;
                                        output_buf[j] = buf[i];
                                }
                                iov[0].iov_base = output_buf;
                                iov[0].iov_len = pagesize;

                                int write_test = writev(fd1, iov, 1);
                                if (write_test < 0) {
                                        err_sys("writev failed\n");
                                }
                                free(output_buf);
                        }
                }
                char *output_buf = malloc(pagesize * sizeof(char));
                assert(output_buf);
                memcpy(output_buf, &BMP_header.type, 2);
                memcpy((output_buf + 2), &BMP_header.size_bmp, 4);
                memcpy((output_buf + 6), &BMP_header.reserved_0, 2);
                memcpy((output_buf + 8), &BMP_header.reserved_1, 2);
                memcpy((output_buf + 10), &BMP_header.offset, 4);
                memcpy((output_buf + 14), &BMP_header.size_dib_header, 4);
                memcpy((output_buf + 18), &BMP_header.bmp_width, 4);
                memcpy((output_buf + 22), &BMP_header.bmp_height, 4);
                memcpy((output_buf + 26), &BMP_header.color_planes, 2);
                memcpy((output_buf + 28), &BMP_header.bpp, 2);
                memcpy((output_buf + 30), &BMP_header.compression_method, 4);
                memcpy((output_buf + 34), &BMP_header.image_size, 4);
                memcpy((output_buf + 38), &BMP_header.horiz_resolution, 4);
                memcpy((output_buf + 42), &BMP_header.vert_resolution, 4);
                memcpy((output_buf + 46), &BMP_header.no_colors, 4);
                memcpy((output_buf + 50), &BMP_header.no_important_colors, 4);
                int fd_reset = lseek(fd0, 54, 0);
                if (fd_reset < 0) {
                        err_sys("lseek failed\n");
                }
                int rd1 = read_all(fd0, buf, (BMP_header.offset - 54));
                if (rd1 < 0) {
                        err_sys("read_all failed\n");
                }
                for (int i = 0; i < rd1; i++) {
                        int j = i + 54; /* offset to jump over header data */
                        output_buf[j] = buf[i];
                }
                rd1 = read_all(fd0, buf, pagesize);
                if (rd1 < 0) {
                        err_sys("read_all failed");
                }
                for (int i = 0; i < rd1; i++) {
                        int j = i + BMP_header.offset;
                        output_buf[j] = buf[i];
                }


                if (red_flag != 0) {
                        if (BMP_header.offset != 54) {
                                err_quit("You can't alter R of an 8 bpp bmp\n");
                        }
                        for (int i = BMP_header.offset + 2; i < pagesize; i += 3) {
                                output_buf[i] = atoi(set_red_to);
                        }
                }
                if (green_flag != 0) {
                        if (BMP_header.offset != 54) {
                                err_quit("You can't alter G of an 8 bpp bmp\n");
                        }
                        for (int i = BMP_header.offset + 1; i < pagesize; i += 3) {
                                output_buf[i] = atoi(set_green_to);
                        }
                }
                if (blue_flag != 0) {
                        if (BMP_header.offset != 54) {
                                err_quit("You can't alter B of an 8bpp bmp\n");
                        }
                        for (int i = BMP_header.offset; i < pagesize; i += 3) {
                                output_buf[i] = atoi(set_blue_to);
                        }
                }
                iov[0].iov_base = output_buf;
                iov[0].iov_len = pagesize;

                int write_test = writev(fd1, iov, 1);
                if (write_test < 0) {
                        err_sys("writev failed");
                }
                free(output_buf);
        }



        return 0;
}
/**
 * @brief form of syscall "read" which is more robust, provided by Scott.
 * @param fd the file descriptor to operate on
 * @param buf the buffer to write to
 * @param n the size in bytes in which to read
 */
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
