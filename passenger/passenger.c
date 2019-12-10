#pragma once
#include "passenger.h"

#include "stdio.h"
#include "../flight/flight.h"
#include "../flight/flight.c"
#include "../bag/bag.c"

int savePassenger(flight *f);
int addPassenger(flight *f );
int loadPassenger(flight *f );

/*============================================================*/

int addPassenger(flight *f ){
    printf("Bienvenue dans la categorie : Ajouter un passager !\n");

    passenger *passenger1 = malloc(sizeof(passenger));
    passenger1->nb_bags = 0;
    passenger1->isRegistered = 0;

    printf("\n \n");
    printf("Rappel: Vol  : depart-> %s  arrivee -> %s \n \n", f->departure, f->arrival);
    printf("-------------------------------- \n");

    printf("Est-ce un passager prioritaire ? \n");
    scanf("%d", &passenger1->priority);

    printf("Veuillez entrer le nom de famille du passager ! \n");
    scanf("%s", passenger1->surname);
    printf("Veuillez entrer le prenom du passager !\n");
    scanf("%s", passenger1->name);
    printf("Veuillez entrer l'age du passager !\n");
    scanf("%d", &passenger1->age);
    printf("Veuillez entrer la date de naissance du passager !\n");
    printf("Veuillez indiquer le jour de naissance.\n");
    scanf("%d", &passenger1->birthday[0]);
    while (passenger1->birthday[0] <= 0 || passenger1->birthday[0] > 31){
        printf("Jour incorrect ! Veuillez indiquer le jour de naissance.\n");
        scanf("%d", &passenger1->birthday[0]);
    }
    printf("Veuillez indiquer le mois de naissance !\n");
    scanf("%d", &passenger1->birthday[1]);
    while (passenger1->birthday[1] <=  0 || passenger1->birthday[1] > 12){
        printf("Mois incorrect ! Veuillez indiquer le mois de naissance.\n");
        scanf("%d", &passenger1->birthday[1]);
    }

    printf("Veuillez indiquer l'année de naissance !\n");
    scanf("%d", &passenger1->birthday[2]);
    while  (passenger1->birthday[2] < 1900 || passenger1->birthday[2] >= 2019){
        printf("Année incorrect ! Veuillez indiquer  l'annee de naissance.\n");
        scanf("%d", &passenger1->birthday[2]);
    }

    printf("Veuillez indiquer le numéro du passeport du passager. \n");
    scanf("%d", &passenger1->passport_number);

    add_bag(passenger1);

    strcpy(passenger1->destination,f->arrival);
    passenger1->ticket = 100000000 + (999999990-100000000) * ( (float) rand()) / RAND_MAX;

    printf(" \n \n");
    printf("===============================================\n");
    printf("Nom: %s            -   Prenom: %s \n", passenger1->surname, passenger1->name);
    printf("Age: %d                -   Date de naissance : %d/%d/%d\n", passenger1->age, passenger1->birthday[0], passenger1->birthday[1],  passenger1->birthday[2]);
    printf("Passeport: %d        -   Billet: %d \n", passenger1->passport_number, passenger1->ticket);
    printf("Depart: %s           -   Arrivee: %s \n", f->departure, f->arrival);
    printf("Nombre de bagages:  %d \n", passenger1->nb_bags);
    if(passenger1->priority == 1){
        printf("Passager prioritaire \n");
    }else{
        printf("Passager non prioritaire \n");
    }

    printf("===============================================\n");

    f->passengers[f->nbPassengers] = *passenger1;
    f->nbPassengers = f->nbPassengers + 1;

    printf("\n \n");

    for (int i = 0; i < nb_flights; ++i){
        printf("%d %s %s \n", flights[i]->id, flights[i]->departure, flights[i]->arrival);

    }
    showFlights();

    return 0;

}


int savePassenger(flight *f){

    int ticket, i, choice;

    printf("Indiquez le numéro du billet du passager !\n");
    scanf("%i", &ticket);

    for(i = 0; i < f->nbPassengers; i++){
        if(f->passengers[i].ticket != ticket) continue;

        if(f->passengers[i].isRegistered == 1){
            printf("Ce passager a deja ete enregistrer, il faurait l'embarquer maintenant ! \n");
            return -1;
        }


        printf("Le passager souhaite il avoir une place spécifique  ?");
        scanf("%d", &choice);

        if(choice == 1){
            printf("Ecrire la place souhaitee  > 0 et < 501!");
            scanf("%d", &choice);
            int response = specificPlace(f, choice);

            while(response == 0){
                printf("Cette place n'est pas disponible");
                scanf("%d", &choice);
                response = specificPlace(f, choice);
            }

            f->passengers[i].place= response;

        }else{
            f->passengers[i].place = randomPlace(f);

        }
        printf(" \n \n");
        printf("==============Bording_Pass================\n");
        printf("Nom: %s   -   Prenom: %s \n", f->passengers[i].surname, f->passengers[i].name);
        printf("Place: %d  -   Billet: %d \n", f->passengers[i].place, f->passengers[i].ticket);
        printf("Depart: %s   -   Arrivee: %s \n", f->departure, f->arrival);
        if(f->passengers[i].priority==1){printf("Passager prioritaire. \n");}
        else{printf("Passager non prioritaire. \n");}
        printf("==========================================\n");
        printf("\n");

        f->passengers[i].isRegistered = 1;

        ticket_bag(f, f->passengers[i]);

        return 0;
    }

    printf("\nAucun passager avec ce numero de billet est inscrit ! \n\n");
    return -1;
}

int loadPassenger(flight *f ){
    passenger p;
    int ticket;

    printf("Veuillez entrez le numero du billet du passager !");
    scanf("%d", &ticket);


    for (int j = 0; j < f->nbPassengers; j++) {
        if (f->passengers[j].ticket != ticket) continue;

        if (f->passengers[j].isRegistered == 0) {
            printf("Ce passager n'a pas ete enregistrer, il faurait l'enregistrer avant de l'embarquer ! \n");
            return -1;
        }

        if(f->passengers[j].priority == 0){


            int nbPriority = 0;
            for (int i = 0; i < f->nbPassengers; ++i) {
                if (f->passengers[i].priority == 1) {
                    nbPriority++;
                }
            }

//VERIFICATION PASSAGER PRIORITAIRE
            passenger *tab = malloc(sizeof(struct s_passenger) * nbPriority);
            nbPriority = 0;
            for (int i = 0; i < f->nbPassengers; ++i) {
                if (f->passengers[i].priority == 1) {
                    tab[nbPriority] = f->passengers[i];
                    nbPriority++;
                }
            }


            printf("Prioritaire : %d \n", nbPriority);
            printf("Loaded : %d \n", f->nbPassengersLoaded);


//SI IL Y A MOINS DE PASSAGER RENREGISTRER QUE DE PRIORITAIRE
            if (f->nbPassengersLoaded < nbPriority) {
                printf("Tous les prioritaires doivent embarquer avant !");
                return -1;
            }

            for (int k = 0; k < p.nb_bags; ++k) {
                f->bagsLoaded[f->nbBags] = p.bag[k];
                f->nbBags++;
            }

            printf("Le passager %s %s a embarque sur le vol %d", f->passengers[j].surname, f->passengers[j].name,
                   f->id);
            f->passengersLoaded[f->nbPassengersLoaded] = f->passengers[j];
            f->nbPassengers--;
            f->nbPassengersLoaded++;

            return 0;

            //SINON

            /*int verif = 0;
            for (int i = 0; i < nbPriority; i++) {
                for (int j = 0; j < f->nbPassengersLoaded; j++) {
                    printf("tab : %s \n", tab[i].surname);
                    printf("f  : %s \n", f->passengersLoaded[j].surname);
                    if (tab[i].ticket != f->passengersLoaded[j].ticket) continue;
                    verif++;
                }
            }

            printf("verif ; %d \n");

            free(tab);
            if (verif != nbPriority) {
                printf("Tous les prioritaires doivent embarquer avant !");
                return -1;
            } else {
                printf("Le passager %s %s a embarque sur le vol %d", f->passengers[j].surname, f->passengers[j].name,
                       f->id);
                f->passengersLoaded[f->nbPassengersLoaded] = f->passengers[j];
                f->nbPassengers--;
                f->nbPassengersLoaded++;
            }*/

        }

        for (int k = 0; k < p.nb_bags; ++k) {
            f->bagsLoaded[f->nbBags] = p.bag[k];
            f->nbBags++;
        }

        printf("Le passager %s %s a embarque sur le vol %d", f->passengers[j].surname, f->passengers[j].name,
               f->id);
        f->passengersLoaded[f->nbPassengersLoaded] = f->passengers[j];
        //f->nbPassengers--;
        f->nbPassengersLoaded++;

        return 0;

    }

    printf("Aucun passager avec ce billet n'a ete trouve ! \n");
    return -1;

}
