/**
 * \file flight.h
 * \brief Programme des struture vols.
 * \author Rayane.M & Lorène.B
 * \version 0.1
 * \date 26 octobre 2019
 *
 * Programme des structures pour l'objet de gestion des vols.
 *
 */

#pragma once
#include "../passenger/passenger.h"

/**
 * \struct flight
 * \brief Objet flight, vol de l'aéroport.
 *
 * flight est un objet de gestion de vols d'un aéroport.
 * Toutes les informations tel que le id, les passagers, le pays de départ et l'arrivée, les bagages
 * la date de départ etc... sont contenus dedans !
 */

typedef struct s_flight{
    int id, nbPassengers, nbPassengersLoaded, nbBags, visa;
    int date[2];
    char departure[20],arrival[20];
    passenger passengers[500], passengersLoaded[500];
    bag bagsLoaded[1000];
} flight;