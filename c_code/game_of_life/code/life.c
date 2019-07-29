/**
 * @file life.c
 *
 * @brief contains functional logic for "init_matrix function"
 *
 * @details initializes a two-dimensional array of Ws * Hs
 *
 * @author Casey D. Haynes
 *
 * @date December 7, 2017
 *
 * @todo When revising for modularity, add more functions.
 *
 * @bug none
 *
 * @remark none
 */
#include "life.h"
#include <stdlib.h>

/**
 * @brief creates a two-dimensional array
 * @param int rows the number of rows to create the matrix with
 * @param int cols the number of columns to create the matrix with
 * @return a double pointer to the fabricated matrix
 */
unsigned char **init_matrix(int rows, int cols) {

        int i;
        int j;
        unsigned char **a;

        a = malloc(rows * sizeof(int *));
        if (!a)
                return NULL;
        for (i = 0; i < rows; i++) {
                a[i] = malloc(cols * sizeof(int));
                if (!a[i]) {
                        for (j = 0; j < i; j++)
                                free(a[j]);
                        free(a);
                        return NULL;
                }
        }
        return a;
}
