#pragma once
#include "../passenger/passenger.h"

typedef struct s_flight{
    int id, nb;
    char departure[20],arrival[20];
    passenger passengers[500], passengers_saved[500];
} flight;