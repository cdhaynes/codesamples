/**
* @file kml.h
*
* @author Casey D. Haynes
*
* @date 1/27/2018
*
* Assignment: Lab 11
*
* @brief Header file
*
* @details
*
* @bugs none
*
* @todo none
*/
#ifndef KML_H_
#define KML_H_

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>

#define LEN 1024
#define MALLOCFAILED 1000



struct geo_city_t {
        char *city;
        char *state;
        char *country;
        float latitude;
        float longitude;
};
/**
 * @brief loads in city/territory data to the dynamically allocated array
 * @param a pointer to the array
 * @param city the string literal with city data
 * @param province the string literal with state/country data
 * @param index the index of the array to operate on
 * @return a pointer to the array
 */
struct geo_city_t* set_city_state_country(struct geo_city_t *a, char *city, char *province, int index);
/**
 * @brief loads in latitude data to the dynamically allocated array
 * @param a pointer to the array
 * @param latitude1 the DEGREE value of latitude
 * @param latitude2 the ARCMINUTE value of the latitude
 * @param latitude3 the DIRECTIONAL value of the latitude
 * @return a pointer to the array
 */
struct geo_city_t* set_latitude(struct geo_city_t *a, char *latitude1, char *latitude2, char *latitude3, int index);
/**
 * @brief loads in latitude data to the dynamically allocated array
 * @param a pointer to the array
 * @param longitude1 the DEGREE value of longitude
 * @param longitude2 the ARCMINUTE value of the longitude
 * @param longitude3 the DIRECTIONAL value of the longitude
 * @return a pointer to the array
 */
struct geo_city_t* set_longitude(struct geo_city_t *a, char *longitude1, char *longitude2, char *longitude3, int index);
/**
 * @brief starts authoring the KML file
 * @param *outkml the pointer to the outfile
 */
void kml_begin(FILE *outkml);
/**
 * @brief authors the middle of the KML file
 * @param *outkml the pointer to the outfile
 * @param a the structure to get data from
 */
void kml_placemark(FILE *outkml, struct geo_city_t a);
/**
 * @brief authors the end of the KML file
 * @param *outkml the pointer to the outfile
 */
void kml_end(FILE *outkml);
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
void logfile(FILE *outtxt, struct geo_city_t a, char *lat1, char *lat2, char *lat3, char *long1, char *long2, char *long3);

#endif /*KML_H*/
