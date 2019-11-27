#pragma once
#include "flight.h"

int give_Specific_Place(flight *vol1, int place);
int give_place(flight* vol1);
void add_flight();
void load_passengers(flight* vol1);
void load_bags(flight* vol1);

flight *flights[500];
int nb_flights = 0;

/*============================================================*/

int give_Specific_Place(flight *vol1, int place) {

    if(vol1->nb == 1)
        return place;

    for(int i = 0 ; i<vol1->nb;i++){
        if(vol1->passengers[i].place != place) continue;
        return 0;
    }

    return place;
}

int give_place(flight* vol1){
    int random = 1 + (500-1) * ( (float) rand()) / RAND_MAX;

    if(vol1->nb == 1)
        return random;

    for(int i = 0 ; i<vol1->nb;i++){
        if(vol1->passengers[i].place != random) continue;
        give_place(vol1);
        return 0;
    }

    return random;
}

flight* find(int id){

    for(int i = 0; i<nb_flights;i++){
        if(flights[i]->id != id) continue;
        return flights[i];
    }
    return NULL;
}

void add_flight(){
    int id, boolean = 1;
    flight *flight1 = malloc(sizeof(flight));
    printf("Indiquez l'ID du vol ? \n");
    scanf("%d", &id);
    while(boolean == 1){
        boolean = 0;
        if(nb_flights == 0) break;
        for(int i = 0; i<nb_flights;i++){
            if(flights[i]->id == id) { boolean = 1; break;}
            boolean = 0;
        }
        printf("Cet id est deja utilise ! \n");
        printf("Indiquez l'ID du vol ? \n");
        scanf("%d", &id);
    }

    flight1->id = id;

    printf("Indiquez le pays de depart du vol (sans-espace) ? \n");
    scanf("%s", flight1->departure);
    printf("Indiquez le pays d'arrivee du vol (sans-espace) ? \n");
    scanf("%s", flight1->arrival);

    flight1->nb = 0;
    flight1->passengers_loaded = 0;

    flights[nb_flights] = flight1;
    nb_flights = nb_flights + 1;

    printf("le vol %d a ete ajoute avec succes ! \n \n", flight1->id);

    printf("==========================================\n");
    printf("Id: %d  -   passagers: %i \n", flight1->id, flight1->nb);
    printf("Depart: %s   -   Arrivee: %s \n", flight1->departure, flight1->arrival);
    printf("==========================================\n");
    printf("\n");
}

void load_passengers(flight* vol1){
    int tab[500], k = 0;
    for(int i =0; i<vol1->nb;i++){
        if(vol1->passengers[i].priority != 1) continue;
        printf("Embarcation de %s %s \n", vol1->passengers[i].surname, vol1->passengers[i].name );
        vol1->passengers_saved[k] = vol1->passengers[i];
        tab[k] = i;
        k++;
    }

    printf("Il y a au total %d  passagers prioritaire. Tous ont été embarqué !\n", k);
    for(int i = 0; i<vol1->nb; i++){
        for(int j = 0; j<k; j++)if(i==tab[j]) continue;

        printf("Embarcation de %s %s \n", vol1->passengers[i].surname, vol1->passengers[i].name);
        vol1->passengers_saved[k] = vol1->passengers[i];
        k++;

    }

    vol1->passengers_loaded = k;

    if(vol1->passengers_loaded != vol1->nb){ printf("Erreur, tous les passagers n'ont pas embarqué ! \n"); return; }
    printf("Tous les passagers ont  embarqué ! \n");
}


void load_bags(flight* vol1){

    int tab[500], k = 0;

    for(int i = 0; i<500;i++){

        if(vol1->passengers_saved[i].priority != 1) continue;
        for(int j = 0; j <vol1->passengers_saved[i].nb_bags;j++){
            printf("Bag prioritaire chargé et embarqué ! \n");
            vol1->bags_loaded[k] = vol1->passengers_saved[i].bag[j];
            tab[k] = i;
            k++;
        }
    }

    for(int i = 0; i<500;i++){
        for(int j = 0; j<k; j++) if(i == tab[j]) break;

        for(int l = 0; l<vol1->passengers_saved[i].nb_bags; l++){
            printf("Bag chargé et embarqué ! \n");
            vol1->bags_loaded[k] = vol1->passengers_saved[i].bag[l];
            tab[k] = i;
            k++;
        }
    }

}