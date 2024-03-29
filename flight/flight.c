/**
 * \file flight.c
 * \brief Programme répertoriant les fonctions relatifs aux vols (flights).
 * \author Rayane.M & Lorène.B
 * \version 0.1
 * \date 26 octobre 2019
 *
 * Programme de vols pour l'objet de gestion des vols de l'aéroport.
 *
 */

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

/**
 * \fn int addPassport()
 * \brief Fonction de création d'un numero de passeport a un passager
 *        vérifie si le numero entré est supérieur à 1000
 *        vérifie si le numéro entré n'a pas déjà été entré par quelqu'un d'autre
 * \return addPassport() si le numero a déjà été rentrer auparavant
 *         passport un entier représentant le numéro du passport si celui-ci est valable.
 */

int addPassport(){
    int passport;

    printf("Veuillez indiquer le num%cro du passeport du passager. \n", 130);
    scanf("%d", &passport);
    while (passport < 1000){
        printf("Un passport doit être sup%crieur a 1000 ! \n" ,130);
        printf("Veuillez indiquer le num%cro du passeport du passager. \n", 130);
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

/**
 * \fn int addTicket()
 * \brief Fonction d'attribution d'un numero de billet aléatoire à un passager
 *        si ce numero a deja ete attribue, il genere un autre numero
 * \return  ticket un entier représentant le billet du passager.
 */

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

/**
 * \fn int specificPlace(flight *vol1, int place)
 * \brief Fonction d'attribution d'une place demandée par le passager
 *        verifie si la place specifique demandee par le passager est comprise entre 0 et 500
 *        verifie si la place demandee a deja ete attribuee
 * \param  vol1 un pointeur sur le vol dont le passager est inscrit, ne peut être NULL.
 * \param  place un entier représentant le numéro du siège voulu, ne peut être NULL.
 * \return place si la place est disponible, 0 si cas contraire.
 */

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
/**
 * \fn int randomPlace(flight *vol1)
 * \brief Fonction d'attribution d'une place aléatoire à un passager
 *        attribue une place aléatoire au passager entre 1 et 500
 *        si la place attribuée a déjà été attribuée, en génère une autre
 * \param  vol1 un pointeur sur le vol dont passager est inscrit, ne peut être NULL.
 * \return random un entier repésentant le numéo du siège si réussi, 0 si échec.
 */

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

/**
 * \fn hasVisa(flight *f, passenger *p)
 * \brief  Fonction de vérification de possession du visa
 *         demande au passager si il possède un visa
 * \param  f flight sur lequel le passager est inscrit, ne peut être NULL.
 * \param  p passenger concerné par le visa, ne peut être NULL.
 * \return -1 si il ne l'a pas, 0 si il l'a
 */

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

/**
 * \fn flight* find(int id)
 * \brief  Fonction d'accès aux informations d'un vol grâce à son ID
 * \param  id un entier représentant l'id d'un vol, ne peut être NULL.
 * \return flight[i] un pointeur sur un vol si réussi,  NULL s'il n'a pas été trouvé
 */

flight* find(int id){

    for(int i = 0; i<nb_flights;i++){
        if(flights[i]->id != id) continue;
        return flights[i];
    }
    return NULL;
}

/**
 * \fn searchID(int id)
 * \brief  Fonction de recherche d'ID
 *         vérifie si l'ID entré n'est pas déjà utilisé pour un autre avion
 * \param  id un entier représentant l'id d'un vol, ne peut être NULL.
 * \return 0 si échec, 1 si réussi.
 */

int searchID(int id){
    for(int i =0 ; i<nb_flights;i++){
        if(flights[i]->id == id){
            return 1;
        }
    }
    return 0;
}

/**
 * \fn void addFlight(){
 * \brief Fonction de création d'un avion
 *        récupération des informations le concernant
 *        affichage des informations
 * \return void
 */

void addFlight(){
    int id;
    flight *flight1 = malloc(sizeof(flight));

    printf("Indiquez l'ID du vol ? \n");
    scanf("%d", &id);

    while(searchID(id) == 1){
        printf("Cet id est d%cj%c utilis%c ! \nIndiquez un autre ID. \n", 130, 133 ,130);
        scanf("%d", &id);
    }

    flight1->id = id;

    printf("Indiquez le pays de d%cpart du vol (sans-espace) ? \n", 130);
    scanf("%s", flight1->departure);
    printf("Indiquez le pays d'arriv%ce du vol (sans-espace) ? \n", 130);
    scanf("%s", flight1->arrival);
    printf("Indiquez le jour de d%cpart  du vol  ? \n", 130);
    scanf("%d", &flight1->date[0]);
    printf("Indiquez le mois de d%cpart  du vol  ? \n", 130);
    scanf("%d", &flight1->date[1]);
    printf("Ce voyage n%ccessite un visa (1 = OUI, 0 = NON) ? \n", 130);
    scanf("%d", &flight1->visa);
    flight1->nbPassengers = 0;
    flight1->nbPassengersLoaded = 0;
    flight1->nbBags = 0;


    flights[nb_flights] = flight1;
    nb_flights = nb_flights + 1;

    printf("le vol %d a ete ajout%c avec succ%cs ! \n \n", flight1->id, 130, 130);

    printf("==========================================\n");
    printf("Id: %d  -   passagers: %i \n", flight1->id, flight1->nbPassengers);
    printf("D%cpart: %s   -   Arriv%ce: %s \n", 130, flight1->departure, 130, flight1->arrival);
    printf("==========================================\n");
    printf("\n");
}

/**
 * \fn saveFlights()
 * \brief  Fonction de sauvegarde d'un avion dans un fichier
 *         récupère les informations concernant un avion et les sauvegarde dans un fichier
 * \return 0 si reussit ou -1 cas contraire.
 */

int saveFlights(){
    FILE *outfile;

    // open file for writing
    outfile = fopen ("C:\\Users\\rayane\\Documents\\NF05\\Planes\\flights.dat", "w");
    if (outfile == NULL){
        fprintf(stderr, "\nLe fichier n'existe pas ! V%crifiez le nom du repertoire \n", 130);
        return -1;
    }
    fwrite(&nb_flights, sizeof(int), 1, outfile);

    // write struct to file
    for(int i = 0; i <nb_flights;i++){
        fwrite (flights[i], sizeof(struct s_flight), 1, outfile);
    }

    if(fwrite != 0)
        printf("%d vols ont %ct%c sauvegard%cs dans le fichier\n", nb_flights, 130, 130, 130);
    else
        printf("Erreur dans l'%ccriture du fichier !\n", 130);

    // close file
    fclose (outfile);

    return 0;
}

/**
 * \fn getFlights
 * \brief  Fonction de récupération des avions dans un fichier
 *         charge les informations concernant les avions depuis un fichier
 * \return 0 si reussit ou -1 cas contraire.
 */

int getFlights(){

    FILE *infile;

    // Open person.dat for reading
    infile = fopen ("C:\\Users\\rayane\\Documents\\NF05\\Planes\\flights.dat" , "r");
    if (infile == NULL){
        fprintf(stderr, "\nLe fichier n'existe pas ! Il sera cr%ce %c la fin du programme.\n", 130, 133);
        return -1;
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
        printf("%d vols ont %ct%c r%ccup%cr%cs depuis le fichier !\n", nb_flights, 130 ,130 ,130, 130, 130);
    else
        printf("Erreur dans la lecture du fichier !\n");
    fclose (infile);

    return 0;
}

/**
 * \fn showFlights
 * \brief  Fonction d'affichage des vols disponibles
 *         affichage des informations et des passagers des vols disponibles
 * \return void
 */

void showFlights(){
    printf("\n\nVoici la liste de tous les vols disponibles : \n\n");
    for(int i = 0; i<nb_flights;i++){
        printf("- id: %d --- d%cpart: %s --- arriv%ce: %s ! \n Passengers : \n", flights[i]->id, 130,flights[i]->departure, 130, flights[i]->arrival);
        if(flights[i]->nbPassengers > 0){
            for (int j = 0; j < flights[i]->nbPassengers; ++j) {
                printf("Passager %d : %s , %s , %d\n", j +1 , flights[i]->passengers[j].surname,flights[i]->passengers[j].name, flights[i]->passengers[j].ticket );
            }
        }
        printf("\n");

    }
    printf("=========================================\n");
}

/**
 * \fn sendFlight(flight *f)
 * \brief  Fonction d'envoi du vol
 *         vérifie si tous les passagers enregistrés ont embarqué
 *         vérifie que les bagages ont été chargés
 * \param  f flight sur lequel le passager est inscrit, ne peut être NULL.
 * \return -1 si échec, 0 si réussit
 */

int sendFlight(flight *f){
    if(f->nbPassengers != f->nbPassengersLoaded){
        printf("Tous les passagers enregistr%cs n'ont pas embarqu%c !\n", 130);
        return -1;
        //OK
    }
    int bags = 0;
    for (int i=0; i < f->nbPassengersLoaded; i++) { bags = bags + f->passengersLoaded[i].nb_bags; }

    if(bags != f->nbBags){
        printf("Tous les bagages n'ont pas %ct%c enregistr%cs ! L'avion ne peut donc pas d%ccoller. \n", 130 , 130 , 130 , 130 );
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

/**
 * \fn graphics(flight *f , int nbFlights)
 * \brief  Fonction de calcul de statistiques
 *         calcule et affiche le taux de remplissage des avions sur une periode
 *         calcule et affiche le poids moyen des bagages des avions sur une periode
 *         calcule et affiche le rapport de passagers prioritaires des avions sur une periode
 * \param  f un pointeur sur flight sur lequel le passager est inscrit, ne peut être NULL.
 * \param  nbFlights un entier indiquant le nombre de vols de la période, ne peut être NULL.
 * \return 0
 */

int graphics(flight *f , int nbFlights){

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
        int nbVols = 0, kgBags = 0, priority = 0, totalBags = 0, totalPassenger = 0, already = 0;

        for (int i = 0; i < t; i++) {
            if(tab[i][0] == tab[t][0] && tab[i][1] == tab[t][1] ) already = 1;
        }

        if(already == 1) continue;

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


        /* Code ancien quand on s'est trompé de sujet
         dayPriority = (int) dayPriority / totalPassenger;
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

/**
 * \fn getPeriod(int day, int months, int finalDay, int finalMonth)
 * \brief  Fonction de récupération d'une période.
 *
 * \param  day un entier indiquant le jour de départ, ne peut être NULL.
 * \param  months un entier indiquant le mois de départ, ne peut être NULL.
 * \param  finalDay un entier indiquant le jour d'arrivée, ne peut être NULL.
 * \param  finalMonth un entier indiquant le mois d'arrivée, ne peut être NULL.
 * \return
 */

void getPeriod(int day, int month, int finalDay, int finalMonth){

    int nb = 0, tab[500];
    for (int i = 0; i < nb_flights; i++) {

        if (month <= flights[i]->date[1] && finalMonth >= flights[i]->date[1] ) {
            tab[nb] = i;
            nb++;

            continue;
        }

        if (flights[i]->date[1] == month && flights[i]->date[0] >= day) {
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