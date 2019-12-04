#pragma once
#include "../bag/bag.h"
/* Test*/

typedef struct s_passenger{
    char surname[20], name[20], destination[20];
    int age, priority, birthday[3];
    int passport_number, place, nb_bags;
    long int ticket;
    bag bag[2];
}passenger;