#pragma once
#include "flight.h"

int addPassport();
int addTicket();
int specificPlace(flight *vol1, int place);
int randomPlace(flight* vol1);
int hasVisa(flight *f, passenger *p);
flight* find(int id);
int searchID(int id);

void addFlight();
int saveFlights();
int getFlights();

void showFlights();
int sendFlight(flight *f);
void getPeriod(int ay, int month, int finalDay, int finalMonth);
int graphics(flight *f , int nbFlights);


flight *flights[500];
int nb_flights = 0;

/*============================================================*/

int addPassport(){
    int passport;

    printf("Veuillez indiquer le numéro du passeport du passager. \n");
    scanf("%d", &passport);
    while (passport < 1000){
        printf("Un passport doit être superieur a 1000 ! \n");
        printf("Veuillez indiquer le numéro du passeport du passager. \n");
        scanf("%d", &passport);
    }

    for(int i = 0; i < nb_flights; i++){
        for(int j = 0; j < flights[i]->nbPassengers; j++){

            if(flights[i]->passengers[j].passport_number == 0) continue;
            if(flights[i]->passengers[j].passport_number != passport) continue;

            return addPassport();
        }
    }

    return passport;
}

int addTicket(){
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

int hasVisa(flight *f, passenger *p){
    int visa = 0;
    if(f->visa == 1){
        printf("Atention, ce vol demande un visa ! \n");
        printf("Le passager a t-il un visa ? (1 = OUI, 0 = NON)\n");
        scanf("%d", &visa);
        if(visa != 1){
            printf("Le passager ne peut donc pas prendre ce vol. \n");
            free(p);
            return -1;
        }
        p->visa = 1;
        printf("Le passager  peut donc prendre ce vol. \n");

    }
    return 0;
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
    int id;
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
    outfile = fopen ("C:\\Users\\rayane\\Documents\\NF05\\Planes\\flights.dat", "w");


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
    infile = fopen ("C:\\Users\\rayane\\Documents\\NF05\\Planes\\flights.dat" , "r");
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
    printf("\n\nVoici la liste de tous les vols disponibles : \n\n");
    for(int i = 0; i<nb_flights;i++){
        printf("- id: %d --- depart: %s --- arrivee: %s ! \n Passengers : \n", flights[i]->id, flights[i]->departure, flights[i]->arrival);
        if(flights[i]->nbPassengers > 0){
            for (int j = 0; j < flights[i]->nbPassengers; ++j) {
                printf("Passager %d : %s , %s , %d\n", j +1 , flights[i]->passengers[j].surname,flights[i]->passengers[j].name, flights[i]->passengers[j].ticket );
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
        //OK
    }
    int bags = 0;
    for (int i=0; i < f->nbPassengersLoaded; i++) { bags = bags + f->passengersLoaded[i].nb_bags; }

    if(bags != f->nbBags){
        printf("Tous les bagages n'ont pas ete enregistres ! L'avion ne peut donc pas decoller. \n");
        return-1;
    }
    else{printf("Tous les bagages ont ete charges dans l'avion. \n");}

    if(f->visa){
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

    int **tab = NULL;

    tab = malloc(nbFlights * sizeof(int*));
    for(int i = 0; i < nbFlights; i++)
        tab[i] = malloc(2 * sizeof(int));

    int days = 0;

    for(int amount = 0; amount < nbFlights; amount++) {
        if(days == 0){
            tab[0][0] = f[0].date[0];
            tab[0][1] = f[0].date[1];
            days++;

            continue;
        }

        for (int k = 0; k < days; k++) {

            if(f[amount].date[0] == tab[k][0] && f[amount].date[1] == tab[k][1]) continue;
            tab[days][0] = f[amount].date[0];
            tab[days][1] = f[amount].date[1];
            days++;
            break;
        }

    }


    for(int t = 0; t < days; t++) {
        int nbVols = 0, kgBags = 0, priority = 0, totalBags = 0, totalPassenger = 0;
        for(int j = 0; j < nbFlights; j++) {

            if (f[j].date[0] == tab[t][0] && f[j].date[1] == tab[t][1]) {
                nbVols += 1;

                totalPassenger += f[j].nbPassengersLoaded;
                totalBags += f[j].nbBags;
                for (int k = 0; k < f[j].nbBags; k++) { kgBags += f[j].bagsLoaded[k].kg; }

                for (int k = 0; k < f[j].nbPassengersLoaded; ++k) {
                    if (f[j].passengersLoaded[k].priority == 1) {
                        priority += 1;
                    }
                }

            }
        }

        printf("Pour le Jour %d/%d, il y a  %d vols \n\n", tab[t][0], tab[t][1], nbVols);
        printf("---->  Il y a %d/%d passagers dans ce ou ces avion(s)  \n", totalPassenger, 500 * nbVols);

        float moyenne = 0;
        if(totalBags != 0){
            moyenne = (float) kgBags / totalBags;
            printf("---->  Il y a un poids moyen de %.2f kg sur un ensemble de %d bags parmis %d vols ! \n", moyenne, totalBags, nbVols);

        }else{
            printf("---->  Il n'y a aucun bags dnas ce ou ces avion(s)! \n");
        }

        if( totalPassenger == 0) continue;
        printf("---->  Il y a %d passagers prioritaire sur %d passagers au total! \n\n", priority , totalPassenger );


        /*dayPriority = (int) dayPriority / totalPassenger;
        for (int l = 0; l < 500; l++) {
            if (l == 499) {
                printf("|");
                break;
            }
            if (l >= dayPriority) {
                printf("_");
                continue;
            }
            printf(".");
        }
*/
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

        if (months <= flights[i]->date[1] && finalMonth >= flights[i]->date[1] ) {
            tab[nb] = i;
            nb++;

            continue;
        }

        if (flights[i]->date[1] == months && flights[i]->date[0] >= day) {
            tab[nb] = i;
            nb++;

            continue;
        }

        if (flights[i]->date[1] == finalMonth && flights[i]->date[0] <= finalDay) {
            tab[nb] = i;
            nb++;

            continue;
        }
    }

    if (nb == 0) {
        printf("Il n'y a aucun vols sur la periode que vous souhaitez ! \n");
        return;
    }

    int amount = 0;
    flight *f = malloc(sizeof(struct s_flight) * nb);
    for(int i = 0; i < nb_flights; i++){
        for (int j = 0; j < nb; j++) {
            if(i != tab[j]) continue;
            f[amount] = *flights[i];
            amount ++;
        }
    }
    graphics(f, nb);
}