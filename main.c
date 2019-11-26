#pragma once
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "passenger/passenger.c"

int main()
{
    long int u;
    time(&u);
    srand(u);

    flight vol1;
    vol1.id = 1;
    vol1.nb = 0;
    strcpy(vol1.arrival,  "Antique");
    strcpy(vol1.departure,  "France");

    add_passenger(&vol1);
    save_passenger(&vol1);

    return 0;
}
