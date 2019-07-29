/**
* @file lab11.c
*
* @author Casey D. Haynes
*
* @date 1/27/2018
*
* Assignment: Lab 11
*
* @brief Implements a dynamically allocated array and generates KML and text files with the data stored in the array.
*
* @details
*
* @bugs none
*
* @todo none
*/
#include "kml.h"


int main(void)
{

        FILE *in = fopen("locations.txt", "r");
        if (in == NULL) {
                printf("Memory allocation has failed. Better luck next time.\n");
                exit(MALLOCFAILED);
        }
        FILE *outkml = fopen("location.kml", "w");
        if (outkml == NULL) {
                printf("Memory allocation has failed. Better luck next time.\n");
                exit(MALLOCFAILED);
        }
        FILE *outtxt = fopen("location.out", "w");
        if (outtxt == NULL) {
                printf("Memory allocation has failed. Better luck next time.\n");
                exit(MALLOCFAILED);
        }
        char buf[LEN];
        char *string = NULL;
        char *city = NULL;
        char *province = NULL;
        char *latitude1 = NULL; /*holds DEG of lat data*/
        char *latitude2 = NULL; /*holds ARCMINUTES of lat data*/
        char *latitude3 = NULL; /*holds COMPASS DIRECTION of lat data*/
        char *longitude1 = NULL; /*holds DEG of long data*/
        char *longitude2 = NULL; /*holds ARCMINUTES of long data*/
        char *longitude3 = NULL; /*holds COMPASS DIRECTION of long data*/
        char *lat1 = malloc(3*sizeof(char)); /*the rest hold the above coordinate data for later*/
        if (lat1 == NULL) {
                printf("Memory allocation has failed. Better luck next time.\n");
                exit(MALLOCFAILED);
        }
        char *lat2 = malloc(3*sizeof(char));
        if (lat2 == NULL) {
                printf("Memory allocation has failed. Better luck next time.\n");
                exit(MALLOCFAILED);
        }
        char *lat3 = malloc(2*sizeof(char));
        if (lat3 == NULL) {
                printf("Memory allocation has failed. Better luck next time.\n");
                exit(MALLOCFAILED);
        }
        char *long1 = malloc(3*sizeof(char));
        if (long1 == NULL) {
                printf("Memory allocation has failed. Better luck next time.\n");
                exit(MALLOCFAILED);
        }
        char *long2 = malloc(3*sizeof(char));
        if (long2 == NULL) {
                printf("Memory allocation has failed. Better luck next time.\n");
                exit(MALLOCFAILED);
        }
        char *long3 = malloc(2*sizeof(char));
        if (long3 == NULL) {
                printf("Memory allocation has failed. Better luck next time.\n");
                exit(MALLOCFAILED);
        }

        struct geo_city_t *a = NULL;
        a = malloc(sizeof(struct geo_city_t));
        if (a == NULL) {
                printf("Memory allocation has failed. Better luck next time.\n");
                exit(MALLOCFAILED);
        }




/* First three fgets blocks eliminate informational first three lines
of infile from processing */
        fgets(buf, LEN, in);
        string = strtok(buf, "\n");


        fgets(buf, LEN, in);
        string = strtok(buf, "\n");


        fgets(buf, LEN, in);
        string = strtok(buf, "\n");
/*------------------------------------------------------------------*/

        int line = 1;

        int index = 0;
        int width = 0;

        kml_begin(outkml); /*Initializes authoring of KML file*/
        while(fgets(buf, LEN, in)) {
                if (line == 1) {
                        a = realloc(a, ++width * sizeof(struct geo_city_t)); /*++width grows the size of allocated memory with every iteration of while*/
                        if (a == NULL) {
                                printf("Memory allocation has failed. Better luck next time.\n");
                                exit(MALLOCFAILED);
                        }
                        string = strtok(buf, "\n");
                        city = strtok(string, ",");
                        char *tmp = city;
                        province = (strtok(NULL, "\n"));
                        province = (province + 1); /*eliminate whitespace from left*/
                        city = tmp;
                        a = set_city_state_country(a, city, province, index); /*Load data to array*/
                        line++; /*keeps track of what type of data is being processed*/


                } else if (line == 2) {
                        string = strtok(buf, "\n");
                        latitude1 = strtok(string, " ");
                        lat1 = strncpy(lat1, latitude1, (strlen(latitude1)) * sizeof(char) + 1);

                        latitude2 = strtok(NULL, " ");
                        lat2 = strncpy(lat2, latitude2, (strlen(latitude2)) * sizeof(char) + 1);

                        latitude3 = strtok(NULL, "");
                        lat3 = strncpy(lat3, latitude3, (strlen(latitude3)) * sizeof(char) + 1);
                        a = set_latitude(a, latitude1, latitude2, latitude3, index); /*load data to array*/
                        line++;
                } else if (line == 3) {
                        string = strtok(buf, "\n");
                        longitude1 = strtok(string, " ");
                        long1 = strncpy(long1, longitude1, (strlen(longitude1)) * sizeof(char) + 1);

                        longitude2 = strtok(NULL, " ");
                        long2 = strncpy(long2, longitude2, (strlen(longitude2)) * sizeof(char) + 1);

                        longitude3 = strtok(NULL, "");
                        long3 = strncpy(long3, longitude3, (strlen(longitude3)) * sizeof(char) + 1);
                        a = set_longitude(a, longitude1, longitude2, longitude3, index);
                        line = 1; /*sets line back to city/state/country field*/
                        kml_placemark(outkml, a[index]); /*add data to kml file*/
                        logfile(outtxt, a[index], lat1, lat2, lat3, long1, long2, long3); /*add data to log file*/
                        free(a[index].city); /*elimate memory leaks after use of heap memory*/
                        if (a[index].state != NULL) {
                                free(a[index].state);
                        }
                        if (strcmp(a[index].country, "United States") != 0) {
                                free(a[index].country);
                        }
                        index++; /*changes which index of the array is being operated on*/
                }



        }



        /*eliminate memory leaks from heap*/
        free(a);
        free(lat1);
        free(lat2);
        free(lat3);
        free(long1);
        free(long2);
        free(long3);

        kml_end(outkml); /*conclude kml file*/

        fclose(in); /*close loaded files*/
        fclose(outkml);
        fclose(outtxt);


        return 0;
}
