/**
 * @file main.c
 * @brief Interfaces with the "blackbox" Scott provided
 * @details Uses commandline args to choose what function to run, and times it
 * @author Casey Haynes
 * @date 31 March 2018
 * @bug None
 */
#include <stdio.h>
#include "blackbox.h"
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <string.h>
#include <unistd.h>

unsigned long * gen_list(unsigned long size);
unsigned long * gen_revlist(unsigned long size);
unsigned long random_number(void);
unsigned long * gen_randlist(unsigned long size);

int main(int argc, char *argv[])
{
        if (argc == 1) {
                printf("Usage: -f function -n size of test data -h HELP\n");
                return 1;
        }
        int c; /*switch on c*/
        int choice; /*Function Choice */
        unsigned long size;
        while((c = getopt(argc, argv, "::f:n:h:")) != -1) {
                switch (c) {
                case 'f':
                        choice = atoi(optarg);
                        break;
                case 'n':
                        size = atol(optarg);
                        break;
                case 'h':
                        printf("Usage: -f function -n size of test data -h HELP\n");
                        return 1;
                        break;
                }
        }

        int msec;
        clock_t time_elapsed;
        unsigned long *list = NULL;
        unsigned long *randlist = NULL;
        unsigned long *revlist = NULL;

        switch (choice) {
        case 1:
                time_elapsed = clock();
                function_1(size);
                time_elapsed = clock() - time_elapsed;
                msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

                printf("Time taken: %d.%03d seconds\n", msec / 1000, msec % 1000);
                printf("CPU-Time elapsed: %d ticks\n", (int) time_elapsed);

                break;
        case 2:
                time_elapsed = clock();
                function_2(size);
                time_elapsed = clock() - time_elapsed;
                msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

                printf("Time taken: %d.%03d seconds\n", msec / 1000, msec % 1000);
                printf("CPU-Time elapsed: %d ticks\n", (int) time_elapsed);

                break;
        case 3: /*Tests three times, calls all three list generators*/
                list = gen_list(size);
                assert (list != NULL);
                time_elapsed = clock();
                function_3(list, size);
                time_elapsed = clock() - time_elapsed;
                msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

                printf("Time taken SORTED: %d.%03d seconds\n", msec / 1000, msec % 1000);
                printf("CPU-Time elapsed SORTED: %d ticks\n", (int) time_elapsed);
                free(list);


                randlist = gen_randlist(size);
                assert (randlist != NULL);
                time_elapsed = clock();
                function_3(randlist, size);
                time_elapsed = clock() - time_elapsed;
                msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

                printf("Time taken RANDOM: %d.%03d seconds\n", msec / 1000, msec % 1000);
                printf("CPU-Time elapsed RANDOM: %d ticks\n", (int) time_elapsed);
                free(randlist);



                revlist = gen_revlist(size);
                assert (revlist != NULL);
                time_elapsed = clock();
                function_3(revlist, size);
                time_elapsed = clock() - time_elapsed;
                msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

                printf("Time taken REVERSE: %d.%03d seconds\n", msec / 1000, msec % 1000);
                printf("CPU-Time elapsed REVERSE: %d ticks\n", (int) time_elapsed);
                free(revlist);

                break;
        case 4:
                time_elapsed = clock();
                function_4(size);
                time_elapsed = clock() - time_elapsed;
                msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

                printf("Time taken: %d.%03d seconds\n", msec / 1000, msec % 1000);
                printf("CPU-Time elapsed: %d ticks\n", (int) time_elapsed);

                break;
        case 5:
                time_elapsed = clock();
                function_5(size);
                time_elapsed = clock() - time_elapsed;
                msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

                printf("Time taken: %d.%03d seconds\n", msec / 1000, msec % 1000);
                printf("CPU-Time elapsed: %d ticks\n", (int) time_elapsed);

                break;
        case 6: /*Tests three times, calls all three list generators*/
                list = gen_list(size);
                assert (list != NULL);
                time_elapsed = clock();
                function_6(list, size);
                time_elapsed = clock() - time_elapsed;
                msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

                printf("Time taken SORTED: %d.%03d seconds\n", msec / 1000, msec % 1000);
                printf("CPU-Time elapsed SORTED: %d ticks\n", (int) time_elapsed);
                free(list);


                randlist = gen_randlist(size);
                assert (randlist != NULL);
                time_elapsed = clock();
                function_6(randlist, size);
                time_elapsed = clock() - time_elapsed;
                msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

                printf("Time taken RANDOM: %d.%03d seconds\n", msec / 1000, msec % 1000);
                printf("CPU-Time elapsed RANDOM: %d ticks\n", (int) time_elapsed);
                free(randlist);


                revlist = NULL;
                revlist = gen_revlist(size);
                assert (revlist != NULL);
                time_elapsed = clock();
                function_6(revlist, size);
                time_elapsed = clock() - time_elapsed;
                msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

                printf("Time taken REVERSE: %d.%03d seconds\n", msec / 1000, msec % 1000);
                printf("CPU-Time elapsed REVERSE: %d ticks\n", (int) time_elapsed);
                free(revlist);

                break;
        case 7:
                time_elapsed = clock();
                function_7(size);
                time_elapsed = clock() - time_elapsed;
                msec = time_elapsed * 1000 / CLOCKS_PER_SEC;

                printf("Time taken: %d.%03d seconds\n", msec / 1000, msec % 1000);
                printf("CPU-Time elapsed: %d ticks\n", (int) time_elapsed);

                break;
        default:
                printf("That's not an option. Goodbye.\n");
                return 1;




        }

        return 0;
}
/**
 * Generates a dynamically allocated list of length size and populates it sequentially
 * @param size the number of elements to be in the list
 * @return a pointer to the generated list
 */
unsigned long * gen_list(unsigned long size)
{
        unsigned long i;
        unsigned long *list = malloc(size * sizeof(unsigned long));

        for (i = 0; i < size; i++) {
                *(list + i) = i;
        }

        return list;
}
/**
 * Generates a dynamically allocated list of length size and populates it randomly
 * @param size the number of elements to be in the list
 * @return a pointer to the generated list
 */
unsigned long * gen_randlist(unsigned long size)
{
        unsigned long i;
        unsigned long *list = malloc(size * sizeof(unsigned long));

        srandom(time(NULL));
        for (i = 0; i < size; i++) {
                *(list + i) = i;
        }

        for (i = size - 1; i > 0; i--) {
                unsigned long j = random_number() % (i + 1);
                unsigned long tmp = *(list + i);
                *(list + i) = *(list + j);
                *(list + j) = tmp;

        }

        return list;
}
/**
 * Generates a dynamically allocated list of length size and populates it with reverse order
 * @param size the number of elements to be in the list
 * @return a pointer to the generated list
 */
unsigned long * gen_revlist(unsigned long size)
{
        unsigned long i;
        unsigned long *list = malloc(size * sizeof(unsigned long));

        for (i = 0; i < size; i++) {
                *(list + i) = i;
        }
        /*Reverse array elements*/
        int j = size - 1;
        for (i = 0; i <= ((size - 1) / 2); i++) {
                unsigned long tmp = list[i];
                list[i] = list[j];
                list[j] = tmp;
                j--;

        }

        return list;
}
/**
 * Generates a random number --> Example given by Scott
 * @return a random number
 */
unsigned long random_number(void) {

        unsigned long n, p, r;
        int i;

        n = 0;
        for (i = 0, p = 1; i < 8; i++, p *= 256) {

                r = random() % 256;

                n += r * p;
        }

        return n;
}
