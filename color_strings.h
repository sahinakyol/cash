#ifndef CASH_COLOR_STRINGS_H
#define CASH_COLOR_STRINGS_H

#include "cash_map.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

CASH_MAP *CASH_MAP_INIT;

 char *colorized(const char *color) {

     if (CASH_MAP_INIT == NULL){
         CASH_MAP_INIT = cash_map_create();
     }

    cash_map_put(CASH_MAP_INIT, "red", ANSI_COLOR_RED);
    cash_map_put(CASH_MAP_INIT, "green", ANSI_COLOR_GREEN);
    cash_map_put(CASH_MAP_INIT, "yellow", ANSI_COLOR_YELLOW);
    cash_map_put(CASH_MAP_INIT, "blue", ANSI_COLOR_BLUE);
    cash_map_put(CASH_MAP_INIT, "magenta", ANSI_COLOR_MAGENTA);
    cash_map_put(CASH_MAP_INIT, "cyan", ANSI_COLOR_CYAN);
    cash_map_put(CASH_MAP_INIT, "reset", ANSI_COLOR_RESET);

    return cash_map_get(CASH_MAP_INIT, color);
}

#endif //CASH_COLOR_STRINGS_H
