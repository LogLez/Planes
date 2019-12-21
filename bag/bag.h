/**
 * \file bag.h
 * \brief Programme des struture bagages.
 * \author Rayane.M & Lorène.B
 * \version 0.1
 * \date 26 octobre 2019
 *
 * Programme principal pour l'objet de gestion des différents menus.
 *
 */

#pragma once

/**
 * \struct bag
 * \brief Objet bagages d'un passager.
 *
 * bag est un petit objet de gestion de bagage d'un passager.
 * Toutes les informations du bagages sont contenus dedans
 * bagages prioritaire, le poids, le nombre d'objets ainsi que tous les objets
 * max objets = 20
 */

typedef struct s_bag{
    int priority, kg, nbItems;
    char items[20][30];
} bag;

/**
 * \struct handbag
 * \brief Objet handbag d'un passager.
 *
 * handbag est un petit objet de gestion de sac à dos ( ou sac à main) d'un passager.
 * Toutes les informations du handBag sont contenus dedans
 * Le nombre d'objets ainsi que les objets eux-même
 * max item = 20
 */
typedef struct s_handbag{
    int nbItems;
    char items[20][30];
} handbag;
