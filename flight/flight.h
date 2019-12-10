#pragma once
#include "../passenger/passenger.h"

typedef struct s_flight{
    int id, nbPassengers, nbPassengersLoaded, nbBags;
    char departure[20],arrival[20];
    passenger passengers[500], passengersLoaded[500];
    bag bagsLoaded[1000];
} flight;