#pragma once
#include "flight.h"

int specificPlace(flight *vol1, int place);
int randomPlace(flight* vol1);
int searchID(int id);
int saveFlights();
int getFlights();
void add_flight();
void load_bags(flight* vol1);
void showFlights();
flight* find(int id);

flight *flights[500];
int nb_flights = 0;

/*============================================================*/

int specificPlace(flight *vol1, int place) {

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


void add_flight(){
    int id, boolean;
    flight *flight1 = malloc(sizeof(flight));

    printf("Indiquez l'ID du vol ? \n");
    scanf("%d", &id);
    boolean = searchID(id);

    while(boolean == 1){
        printf("Cet id est deja utilise ! \nIndiquez l'ID du vol ? \n");
        scanf("%d", &id);
        boolean = searchID(id);
    }

    flight1->id = id;

    printf("Indiquez le pays de depart du vol (sans-espace) ? \n");
    scanf("%s", flight1->departure);
    printf("Indiquez le pays d'arrivee du vol (sans-espace) ? \n");
    scanf("%s", flight1->arrival);

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
        printf("%d vols ont ete sauvegarder dans le fichier\n", nb_flights);
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
        fprintf(stderr, "\nLe fichie n'existe pas ! Il sera creer à la fin du programme.\n");
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
        printf("%d vols ont ete recupere depuis le fichier !\n", nb_flights);
    else
        printf("error reading file !\n");
    fclose (infile);

    return 0;
}

void showFlights(){
    printf("Voici la liste de tous les vols disponible: \n\n");
    for(int i = 0; i<nb_flights;i++){
        printf("- id: %d --- depart: %s --- arrivee: %s ! \n Passengers : ", flights[i]->id, flights[i]->departure, flights[i]->arrival);
        if(flights[i]->nbPassengers > 0){
            for (int j = 0; j < flights[i]->nbPassengers; ++j) {
                printf("     Pasager %d: %s , %s , %d\n", j +1 , flights[i]->passengers[j].surname,flights[i]->passengers[j].name, flights[i]->passengers[j].ticket );
            }
        }
        printf("\n");

    }
    printf("=========================================\n");
}

//BONUS

int graphics(flight *f , int nbFlights){

    //TODO FINIR

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
    }

}