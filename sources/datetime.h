#ifndef DATETIME
#define DATETIME

/*  Lista de Includes: */

#include <inttypes.h>  

typedef struct {
    uint16_t year;
    uint8_t month;
    uint8_t day;
} date;

typedef struct {
    uint8_t hour;
    uint8_t min;
    uint8_t sec;
} time;



#include "datetime.c"
#endif