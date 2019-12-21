/**
 * \file passenger.h
 * \brief Programme des struture passagers.
 * \author Rayane.M & Lorène.B
 * \version 0.1
 * \date 26 octobre 2019
 *
 * Programme des strutures pour l'objet de gestion des passagers relatifs aux vols.
 *
 */

#pragma once
#include "../bag/bag.h"

/**
 * \struct passenger
 * \brief Objet passenger d'un vol de l'aéroport.
 *
 * passenger est un objet de gestion de passager d'un vol d'un aéroport.
 * Toutes les informations du passagers sont contenus dedans
 * nom, prénom, destination, age, priority, date de naissance, visa
 * passport, place dans l'avion nombre de bagages, billet, et tous ses bagages
 */

typedef struct s_passenger{
    char surname[20], name[20], destination[20];
    int age, priority, birthday[3], visa;
    int passport_number, place, nb_bags, isRegistered;
    unsigned int ticket;
    bag bag[2];
    handbag handbag;
}passenger;

