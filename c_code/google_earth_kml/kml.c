/**
* @file kml.c
*
* @author Casey D. Haynes
*
* @date 1/27/2018
*
* Assignment: Lab 11
*
* @brief Provides functional logic for lab11.c.
*
* @details
*
* @bugs none
*
* @todo none
*/
#include "kml.h"


/**
 * @brief loads in city/territory data to the dynamically allocated array
 * @param a pointer to the array
 * @param city the string literal with city data
 * @param province the string literal with state/country data
 * @param index the index of the array to operate on
 * @return a pointer to the array
 */
struct geo_city_t* set_city_state_country(struct geo_city_t *a, char *city, char *province, int index)
{

        int length = strnlen(city, LEN);
        char *string = NULL;
        string = malloc(length * sizeof(char) + 1);
        if (string == NULL) {
                printf("Memory allocation has failed. Better luck next time.\n");
                exit(MALLOCFAILED);
        }
        strncpy(string, city, (length+1));

        a[index].city = string;

        if ((strnlen(province, LEN)) == 2) {
                length = strnlen(province, LEN);
                char *s = NULL;
                s = malloc((length + 1) * sizeof(char));
                if (s == NULL) {
                        printf("Memory allocation has failed. Better luck next time.\n");
                        exit(MALLOCFAILED);
                }
                strncpy(s, province, (length+1));
                a[index].state = s;
                a[index].country = "United States";
        } else if ((strnlen(province, LEN)) == 4) {
                length = strnlen(province, LEN);
                char *s = NULL;
                s = malloc((length+1) * sizeof(char));
                if (s == NULL) {
                        printf("Memory allocation has failed. Better luck next time.\n");
                        exit(MALLOCFAILED);
                }
                strncpy(s, province, (length+1));
                a[index].state = s;
                a[index].country = "United States";
        } else if ((strncmp(province, "Puerto Rico", LEN)) == 0) {
                length = strnlen(province, LEN);
                char *s = NULL;
                s = malloc((length+1) * sizeof(char));
                if (s == NULL) {
                        printf("Memory allocation has failed. Better luck next time.\n");
                        exit(MALLOCFAILED);
                }
                strncpy(s, province, (length+1));
                a[index].state = s;
                a[index].country = "United States";
        } else {
                a[index].state = NULL;
                length = strnlen(province, LEN);
                char *s = NULL;
                s = malloc((length+1) * sizeof(char));
                if (s == NULL) {
                        printf("Memory allocation has failed. Better luck next time.\n");
                        exit(MALLOCFAILED);
                }
                strncpy(s, province, (length+1));
                a[index].country = s;

        }
        return a;

}

/**
 * @brief loads in latitude data to the dynamically allocated array
 * @param a pointer to the array
 * @param latitude1 the DEGREE value of latitude
 * @param latitude2 the ARCMINUTE value of the latitude
 * @param latitude3 the DIRECTIONAL value of the latitude
 * @return a pointer to the array
 */
struct geo_city_t* set_latitude(struct geo_city_t *a, char *latitude1, char *latitude2, char *latitude3, int index)
{
        struct geo_city_t *preserve = a;
        float mag1 = atof(latitude1);
        float mag2 = atof(latitude2);
        float magtot = mag1 + (mag2/60.0);

        if ((strncmp(latitude3, "S", LEN)) == 0) {
                magtot = -magtot;
        }

        a[index].latitude = magtot;
        a = preserve;
        return a;
}

/**
 * @brief loads in latitude data to the dynamically allocated array
 * @param a pointer to the array
 * @param longitude1 the DEGREE value of longitude
 * @param longitude2 the ARCMINUTE value of the longitude
 * @param longitude3 the DIRECTIONAL value of the longitude
 * @return a pointer to the array
 */
struct geo_city_t* set_longitude(struct geo_city_t *a, char *longitude1, char *longitude2, char *longitude3, int index)
{
        struct geo_city_t *preserve = a;
        float mag1 = atof(longitude1);
        float mag2 = atof(longitude2);
        float magtot = mag1+(mag2/60.0);

        if ((strncmp(longitude3, "W", LEN)) == 0) {
                magtot = -magtot;
        }

        a[index].longitude = magtot;

        a = preserve;
        return a;
}

/**
 * @brief starts authoring the KML file
 * @param *outkml the pointer to the outfile
 */
void kml_begin(FILE *outkml)
{

        char *line1 = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
        char *line2 = "<kml xmlns=\"http://earth.google.com/kml/2.1\">\n";
        char *line3 = "<Document>\n";
        char *line4 = "    <name>Mystery Locations</name>\n";



        fprintf(outkml, "%s%s%s%s", line1, line2, line3, line4);




}
/**
 * @brief authors the middle of the KML file
 * @param *outkml the pointer to the outfile
 * @param a the structure to get data from
 */
void kml_placemark(FILE *outkml, struct geo_city_t a)
{
        char *begin = "    <Placemark>\n";
        char *namebegin = "        <name>";
        char *nameend = "</name>\n";
        char *beginp = "        <Point>\n";
        char *begincoo = "            <coordinates>";
        char *endcoo = "</coordinates>\n";
        char *endp = "        </Point>\n";
        char *end = "    </Placemark>\n";



        if (a.state == NULL) {
                fprintf(outkml, "%s%s%s, %s%s%s%s%f,%f,0%s%s%s", begin, namebegin, a.city, a.country, nameend, beginp, begincoo, a.longitude, a.latitude, endcoo, endp, end);
        } else {
                fprintf(outkml, "%s%s%s, %s, %s%s%s%s%f,%f,0%s%s%s", begin, namebegin, a.city, a.state, a.country, nameend, beginp, begincoo, a.longitude, a.latitude, endcoo, endp, end);
        }
}



/**
 * @brief authors the end of the KML file
 * @param *outkml the pointer to the outfile
 */
void kml_end(FILE *outkml)
{
        char *penultimate = "</Document>\n";
        char *ultimate = "</kml>\n";



        fprintf(outkml, "%s%s", penultimate, ultimate);


}
/**
 * @brief authors the log text file
 * @param *outtxt the pointer to the outfile
 * @param a the structure to get data from
 * @param lat1 latitude data DEG
 * @param lat2 latitude data ARCMIN
 * @param lat3 latitude data DIRECTION
 * @param long1 longitude data DEG
 * @param long2 longitude data ARCMIN
 * @param long3 longitude data DIRECTION
 */
void logfile(FILE *outtxt, struct geo_city_t a, char *lat1, char *lat2, char *lat3, char *long1, char *long2, char *long3)
{
        if (a.state == NULL) {
                fprintf(outtxt, "%s|%s|Latitude %s %s %s|Longitude %s %s %s\n", a.city, a.country, lat1, lat2, lat3, long1, long2, long3);
        } else {
                fprintf(outtxt, "%s|%s|United States|Latitude %s %s %s|Longitude %s %s %s\n", a.city, a.state, lat1, lat2, lat3, long1, long2, long3);
        }
}
