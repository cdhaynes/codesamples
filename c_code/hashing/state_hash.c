/**
 * @file state_hash.c
 * @brief Implements a hash table of data with quadratic probing
 * @details Uses Bernstein's hash
 * @author Casey Haynes
 * @date April 2018
 * @bug none
 * @todo
 */

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define LEN 4096

struct postal_t {
        char *abrv; /*two digit abbreviation, capitalized */
        char *name; /*name in start case */
};


/**
 * @brief Converts a string to lowercase using tolower
 * @param the string to pass in
 */
void tolowercase(char *s)
{
        int i = 0;
        while (s[i] != '\0') {
                s[i] = tolower(s[i]);
                i++;
        }
}

/**
 * @brief Strips whitespace from a string using isspace
 * @param a the string to pass in
 */
void rstrip(char *s)
{
        int i = 0;
        while(s[i] != '\0') {
                if (isspace(s[i]) != 0) {
                        s[i] = '\0';
                }
                i++;
        }
}

/**
 * @brief Implements Bernstein's Hash
 * @param s the string to turn into a key
 * @return the key
 */
int bernstein_hash(char *s)
{
        int h = 0;

        while(*s) {
                h = 33 * h + *s;
                s++;
        }

        return h;
}

int main(int argc, char *argv[])
{
        char buf[LEN];
        struct postal_t *postal = malloc(200 * sizeof(struct postal_t));

        for (int i = 0; i < 200; i++) {
                struct postal_t tmp;
                tmp.abrv = NULL;
                tmp.name = NULL;
                postal[i] = tmp;
        }

	FILE *fp = fopen("postal", "r");
	assert(fp);

	while(fgets(buf, LEN, fp)) {
                int n = 31;
                char * a = malloc((n + 1) * sizeof(char));
                memcpy(a, buf, n);

                char * b = malloc((n + 1) * sizeof(char));
                memcpy(b, buf + n + 1, n); /*n + 1 shift one to the right */

                rstrip(b);

                int mark = 0; /*Convert String to Start Case*/
                int i = 0;
                while(a[i] != '\0') {
                        if (mark != 0) {
                                a[i] = tolower(a[i]);
                        } else {
                                mark = 1;
                        }
                        if(a[i] == ' ' || a[i] == '.') {
                                mark = 0;
                        }
                        i++;
                }




                int key = bernstein_hash(b); /*hash the code, not the name*/
                int hash = key % 200;



                if (postal[hash].abrv != NULL) {
                        int i = 1;
                        while (postal[hash].abrv != NULL) {
                                hash = (hash + (i^2)) % 200;
                                i++;
                        }
                }

                postal[hash].abrv = b;
                postal[hash].name = a;




        }

        while(1) {
                printf("1: Find Territory:\n");
                printf("2: Debug\n");
                printf("3: Exit Program\n");
                printf("Choose(1, 2, or 3): ");
                fgets(buf, LEN, stdin);
                rstrip(buf);
                int c = atoi(buf);

                switch(c) {
                case 1:
                        printf("Enter a two-digit state abbreviation (q to quit): ");
                        fgets(buf, LEN, stdin);
                        rstrip(buf);
                        if (strcmp(buf, "q") == 0) {
                                break;
                        }
                        int key = bernstein_hash(buf);
                        int hash = key % 200;

                        if (postal[hash].abrv == NULL) {
                                printf("State not found\n");
                        }
                        else if (strcmp(postal[hash].abrv, buf) == 0) {
                                printf("%s\n", postal[hash].name);
                        } else {
                                int i = 1;
                                while (strcmp(postal[hash].abrv, buf) != 0) {
                                        hash = (hash + (i^2)) % 200;
                                        i++;
                                }
                                if (strcmp(postal[hash].abrv, buf) == 0) {
                                printf("%s\n", postal[hash].name);
                                } else {
                                        printf("State not found\n");

                                }

                        }
                        break;
                case 2:
                        for (int i = 0; i < 200; i++) {
                                if (postal[i].abrv == NULL) {
                                        i++;
                                } else {
                                        printf("i = %d\n", i);
                                        printf("%s\t%s\n\n", postal[i].abrv, postal[i].name);
                                }
                        }
                        break;
                case 3:
                        for (int i = 0; i < 200; i++) {
                                free(postal[i].abrv);
                                free(postal[i].name);
                        }
                        free(postal);
                        fclose(fp);
                        return 0;
                }
        }





        return 0;
}
