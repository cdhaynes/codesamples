/**
 * @file life.h
 * @brief contains declaration of init_matrix function
 * @author Casey D. Haynes
 * @date December 8, 2017
 */
#ifndef LIFE_H_
#define LIFE_H_

struct sdl_info_t *sdl_info;
unsigned char **init_matrix(int rows, int cols);
/**
 * draw the game of life on screen
 * @param struct sdl_info_t sdl_info for SDL parameters
 * @param unsigned char **life the grid of alive or dead cells
 * @remarks Background is black. Make sure init_sdl_info()
 * is called BEFORE using the function
 */

#endif
