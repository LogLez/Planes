#pragma once
#include "../passenger/passenger.h"

typedef struct s_flight{
    int id, nb_passengers, passengers_loaded;
    char departure[20],arrival[20];
    passenger passengers[500], passengers_saved[500];
    bag bags_loaded[1000];
} flight;