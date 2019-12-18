#pragma once
#include "flight.h"

int getPassport(int passport);
int getTicket();
int specificPlace(flight *vol1, int place);
int randomPlace(flight* vol1);
int searchID(int id);
int saveFlights();
int getFlights();
void addFlight();
void loadBags(flight* vol1);
void showFlights();
int sendFlight(flight *f);
flight* find(int id);
void getPeriod(int ay, int month, int finalDay, int finalMonth);
int graphics(flight *f , int nbFlights);


flight *flights[500];
int nb_flights = 0;

/*============================================================*/

int getPassport(int passport){
    for(int i = 0; i < nb_flights; i++){

        for(int j = 0; j < flights[i]->nbPassengers; j++){

            if(flights[i]->passengers[j].passport_number == 0) continue;
            if(flights[i]->passengers[j].passport_number != passport) continue;

            return 0;
        }
    }
    return passport;
}

int getTicket(){
    int result = 0;
    int ticket = 100000000 + (999999990-100000000) * ( (float) rand()) / RAND_MAX;
    while (result == 0){
        result = 1;
        for(int i = 0; i < nb_flights; i++){

            for(int j = 0; j < flights[i]->nbPassengers; j++){

                if(flights[i]->passengers[j].ticket == 0) continue;
                if(flights[i]->passengers[j].ticket != ticket) continue;

                result = 0;
            }
        }
    }
    return ticket;
}

int specificPlace(flight *vol1, int place) {
    while(1>place || place>501) {
        printf("Saisir une nouvelle place. \n");
        scanf("%d", &place);
    }
    if(vol1->nbPassengers == 1)
        return place;

    for(int i = 0 ; i<vol1->nbPassengers;i++){
        if(vol1->passengers[i].place != place) continue;
        return 0;
    }

    return place;
}

int randomPlace(flight* vol1){
    int random = 1 + (500-1) * ( (float) rand()) / RAND_MAX;

    if(vol1->nbPassengers == 1)
        return random;

    for(int i = 0 ; i<vol1->nbPassengers;i++){
        if(vol1->passengers[i].place != random) continue;
        randomPlace(vol1);
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
int searchID(int id){
    for(int i =0 ; i<nb_flights;i++){
        if(flights[i]->id == id){
            return 1;
        }
    }
    return 0;
}

void addFlight(){
    int id, boolean;
    flight *flight1 = malloc(sizeof(flight));

    printf("Indiquez l'ID du vol ? \n");
    scanf("%d", &id);

    while(searchID(id) == 1){
        printf("Cet id est deja utilise ! \nIndiquez l'ID du vol. \n");
        scanf("%d", &id);
    }

    flight1->id = id;

    printf("Indiquez le pays de depart du vol (sans-espace) ? \n");
    scanf("%s", flight1->departure);
    printf("Indiquez le pays d'arrivee du vol (sans-espace) ? \n");
    scanf("%s", flight1->arrival);
    printf("Indiquez le jour de départ  du vol  ? \n");
    scanf("%d", &flight1->date[0]);
    printf("Indiquez le mois de départ  du vol  ? \n");
    scanf("%d", &flight1->date[1]);
    printf("Ce voyage necessite un visa (1 = OUI, 0 = NON) ? \n");
    scanf("%d", &flight1->visa);
    flight1->nbPassengers = 0;
    flight1->nbPassengersLoaded = 0;
    flight1->nbBags = 0;


    flights[nb_flights] = flight1;
    nb_flights = nb_flights + 1;

    printf("le vol %d a ete ajoute avec succes ! \n \n", flight1->id);

    printf("==========================================\n");
    printf("Id: %d  -   passagers: %i \n", flight1->id, flight1->nbPassengers);
    printf("Depart: %s   -   Arrivee: %s \n", flight1->departure, flight1->arrival);
    printf("==========================================\n");
    printf("\n");
}

int saveFlights(){
    FILE *outfile;

    // open file for writing
    outfile = fopen ("C:\\Users\\Rayane\\CLionProjects\\NF05\\Planes\\flights.dat", "w");


    fwrite(&nb_flights, sizeof(int), 1, outfile);

    // write struct to file
    for(int i = 0; i <nb_flights;i++){
        fwrite (flights[i], sizeof(struct s_flight), 1, outfile);
    }

    if(fwrite != 0)
        printf("%d vols ont ete sauvegardes dans le fichier\n", nb_flights);
    else
        printf("error writing file !\n");

    // close file
    fclose (outfile);

    return 0;
}

int getFlights(){

    FILE *infile;

    // Open person.dat for reading
    infile = fopen ("C:\\Users\\Rayane\\CLionProjects\\NF05\\Planes\\flights.dat" , "r");
    if (infile == NULL){
        fprintf(stderr, "\nLe fichier n'existe pas ! Il sera cree à la fin du programme.\n");
        return 0;
    }

    fread(&nb_flights, sizeof(int), 1, infile);

    flight *tab = malloc(sizeof(struct s_flight) * nb_flights);
    fread(tab, sizeof(struct s_flight), nb_flights, infile);


    for(int i = 0; i<nb_flights;i++){
        struct s_flight *input = malloc(sizeof(flight));
        *input = tab[i];
        flights[i] = input;
    }

    free(tab);
    // close file

    if(fread != 0)
        printf("%d vols ont ete recuperes depuis le fichier !\n", nb_flights);
    else
        printf("error reading file !\n");
    fclose (infile);

    return 0;
}

void showFlights(){
    printf("Voici la liste de tous les vols disponibles : \n\n");
    for(int i = 0; i<nb_flights;i++){
        printf("- id: %d --- depart: %s --- arrivee: %s ! \n Passengers : ", flights[i]->id, flights[i]->departure, flights[i]->arrival);
        if(flights[i]->nbPassengers > 0){
            for (int j = 0; j < flights[i]->nbPassengers; ++j) {
                printf("     Passager %d: %s , %s , %d\n", j +1 , flights[i]->passengers[j].surname,flights[i]->passengers[j].name, flights[i]->passengers[j].ticket );
            }
        }
        printf("\n");

    }
    printf("=========================================\n");
}

int sendFlight(flight *f){
    if(f->nbPassengers != f->nbPassengersLoaded){
        printf("Tous les passagers enregistres n'ont pas embarque !\n");
        return -1;
    }
    int bags = 0;
    for (int i = 0; i < f->nbPassengersLoaded; i++) {
        for(int j = 0; j < f->passengersLoaded[i].nb_bags; j++){
            bags++;
        }
    }

    if(bags != f->nbBags){
        printf("Tous les bagages n'ont pas ete enregistres ! L'avion ne peut donc pas decoller. \n");
        return-1;
    }

    if(f->visa == 1){
        for (int i = 0; i < f->nbPassengersLoaded; i++) {
            if(f->passengersLoaded[i].visa == 1) continue;

            printf("Le passager %s ne possede pas de visa, il ne peut donc pas prendre ce vol !\n", f->passengersLoaded[i].name);
            return -1;
        }
    }
    printf("Le vol %d a destination de %s vient de partir de %s \n", f->id, f->arrival, f->departure);
    return 0;

}

/////////////////////BONUS///////////////////////

int graphics(flight *f , int nbFlights){

    //TODO FINIR

    int **tab = (int**) malloc(sizeof(int*) * nbFlights);
    int days = 0;

    for(int i = 0; i < nbFlights; i++) {
        for (int j = 0; j < days; j++) {
            for (int k = 0; k < days; k++) {
                if (f[i].date[0] != *tab[j] && f[i].date[i] != tab[j][k]) {
                    *tab[days] = f[i].date[0];
                    tab[days][days] = f[i].date[1];
                    days++;
                }
            }
        }

    }
    for(int i = 0; i < days; i++) {
        int flight = 0, dayKgBags = 0, dayPriority = 0, totalBags =0, totalPassenger = 0;
        for (int j = 0; j < nbFlights; j++) {
            if(f[j].date[0] == *tab[i] && f[j].date[1] == tab[i][i]){
                flight += 1;

                totalPassenger += f[j].nbPassengersLoaded;
                totalBags += f[j].nbBags;
                for (int k = 0; k < f[j].nbBags; ++k) {
                    dayKgBags += f[j].bagsLoaded[k].kg;
                }

                for (int k = 0; k < f[j].nbPassengersLoaded; ++k) {
                    if(f[j].passengersLoaded[k].priority == 1){
                        dayPriority += 1;
                    }
                }

            }
        }

        printf("Jour %d/%d", *tab[i], tab[i][i]);
        printf("Il y a un poids moyen de %d sur %d bags sur un ensemble de %d vols ! \n", dayKgBags, totalBags, flight);
        dayPriority = (int) dayPriority / totalPassenger;

        for (int l = 0; l < 500; l++) {
            if(l == 499) { printf("|"); break; }
            if(l >= dayPriority){
                printf("_");
                continue;
            }
            printf(".");
        }

    }
/*
    int priority = 0, totalPassager = 0;
    int kgBags = 0, totalBags = 0;
    for (int i = 0; i < nbFlights; i++) {
        totalPassager += f[i].nbPassengersLoaded;
        totalBags += f[i].nbBags;

        for (int k = 0; k < f[i].nbPassengersLoaded; k++) {

            if(f[i].passengersLoaded[k].priority == 1){
                priority += f[i].nbPassengersLoaded;
            }
        }

        for (int j = 0; j < f[i].nbBags; j++) {
            kgBags += f[i].bagsLoaded[j].kg;
        }
    }*/
    return 0;
}

void getPeriod(int day, int months, int finalDay, int finalMonth){

    int nb = 0, tab[500];
    for (int i = 0; i < nb_flights; i++) {

        if(months < flights[i]->date[1] < finalMonth){
            tab[nb] = i;
            nb++;
            continue;
        }

        if(flights[i]->date[1] == months && flights[i]->date[0] >= day){
            tab[nb] = i;
            nb++;
            continue;
        }

        if(flights[i]->date[1] == finalMonth && flights[i]->date[0] <= finalDay){
            tab[nb] = i;
            nb++;
            continue;
        }


    }
    flight *f = malloc(sizeof(struct s_flight) * nb);
    for(int i = 0; i < nb_flights; i++){
        for (int j = 0; j < nb; j++) {
            if(i != j) continue;
            f[nb] = *flights[i];
        }
    }

    if(nb == 0){
        printf("Il n'y a aucun vols sur la periode que vous souhaitez ! \n");
        return;
    }

    graphics(f, nb);
}