#pragma once
#include "passenger.h"

#include "stdio.h"
#include "../flight/flight.h"
#include "../flight/flight.c"
#include "../bag/bag.c"

void showBillet(flight *f, passenger *p);
int addPassenger(flight *f );
int crossBorder(flight *f);
int savePassenger(flight *f);
int loadPassengerBag(flight *f , passenger p);
int checkBeforeLoading(flight *f);
int loadPassenger(flight *f );

/*============================================================*/
void showBillet(flight *f, passenger *p){
    printf(" \n \n");
    printf("===============================================\n");
    printf("Nom: %s            -   Prenom: %s \n", p->surname, p->name);
    printf("Age: %d                -   Date de naissance : %d/%d/%d\n", p->age, p->birthday[0], p->birthday[1],  p->birthday[2]);
    printf("Passeport: %d        -   Billet: %d \n", p->passport_number, p->ticket);
    printf("Depart: %s           -   Arrivee: %s \n", f->departure, f->arrival);
    printf("Nombre de bagages:  %d \n", p->nb_bags);
    if(p->priority == 1){
        printf("Passager prioritaire \n");
    }else{
        printf("Passager non prioritaire \n");
    }

    printf("===============================================\n");
}

int addPassenger(flight *f ){
    printf("Bienvenue dans la categorie : Ajouter un passager !\n");

    passenger *p = malloc(sizeof(passenger));
    p->nb_bags = 0;
    p->isRegistered = 0;
    p->visa = 0;

    printf("\n \n");
    printf("Rappel: Vol  : depart-> %s  arrivee -> %s \n \n", f->departure, f->arrival);
    printf("-------------------------------- \n");

    if(hasVisa(f, p) == -1) return -1;
    strcpy(p->destination,f->arrival);

    printf("Est-ce un passager prioritaire ? (1 = OUI, 0 = NON)\n");
    scanf("%d", &p->priority);

    printf("Veuillez entrer le nom de famille du passager ! \n");
    scanf("%s", p->surname);
    printf("Veuillez entrer le prenom du passager !\n");
    scanf("%s", p->name);
    printf("Veuillez entrer l'age du passager !\n");
    scanf("%d", &p->age);
    printf("Veuillez entrer la date de naissance du passager !\n");
    printf("Veuillez indiquer le jour de naissance.\n");
    scanf("%d", &p->birthday[0]);
    while (p->birthday[0] <= 0 || p->birthday[0] > 31){
        printf("Jour incorrect ! Veuillez indiquer le jour de naissance.\n");
        scanf("%d", &p->birthday[0]);
    }
    printf("Veuillez indiquer le mois de naissance !\n");
    scanf("%d", &p->birthday[1]);
    while (p->birthday[1] <=  0 || p->birthday[1] > 12){
        printf("Mois incorrect ! Veuillez indiquer le mois de naissance.\n");
        scanf("%d", &p->birthday[1]);
    }

    printf("Veuillez indiquer l'année de naissance !\n");
    scanf("%d", &p->birthday[2]);
    while  (p->birthday[2] < 1900 || p->birthday[2] >= 2019){
        printf("Année incorrect ! Veuillez indiquer  l'annee de naissance.\n");
        scanf("%d", &p->birthday[2]);
    }

    p->passport_number = addPassport();
    p->ticket = addTicket();

    addBag(p);
    addHandBag(p);

    f->passengers[f->nbPassengers] = *p;
    f->nbPassengers = f->nbPassengers + 1;

    showBillet(f, p);

    free(p);
    showFlights();

    return 0;

}
int crossBorder(flight *f){
    int ticket;

    printf("Veuillez entrez le numero du billet du passager ! \n");
    scanf("%d", &ticket);
    for (int i = 0; i < f->nbPassengers; i++) {

        if (f->passengers[i].ticket != ticket) continue;

        printf("Le passager %s %s veut se rendre en %s !\n", f->passengers[i].surname, f->passengers[i].name, f->arrival);
        if(f->visa == 1){
            printf("Ce vol demande un visa au passager !\n");
            if(f->passengers[i].visa == 1){
                printf("et %s %s possede bien un visa \n", f->passengers[i].surname
                        , f->passengers[i].name);
            }else{
                printf("et %s %s ne possede pas de visa \n", f->passengers[i].surname
                        , f->passengers[i].name);
                return -1;
            }
        }else{
            printf("Ce vol ne demande pas de visa \n");
        }
    }
    return 0;
}


int savePassenger(flight *f){

    int ticket, i, choice, response;

    printf("Indiquez le numéro du billet du passager !\n");
    scanf("%i", &ticket);

    for(i = 0; i < f->nbPassengers; i++){
        if(f->passengers[i].ticket != ticket) continue;

        if(f->passengers[i].isRegistered == 1){
            printf("Ce passager a deja ete enregistre, il faurait l'embarquer maintenant ! \n");
            return -1;
        }


        printf("Le passager souhaite il avoir une place spécifique  ? (1 = OUI, 0 = NON)\n");
        scanf("%d", &choice);

        if(choice == 1){

                printf("Ecrire la place souhaitee  > 0 et < 501! \n");
                scanf("%d", &choice);
                response = specificPlace(f, choice);

            while(response == 0){
                printf("Cette place n'est pas disponible, saisir une nouvelle place. \n");
                scanf("%d", &choice);
                response = specificPlace(f, choice);
            }

            f->passengers[i].place= response;

        }else{ f->passengers[i].place = randomPlace(f); }

        if(crossBorder(f) != 0) printf("Une erreur est survenue avec le visa du passager ! \n");

        printf(" \n \n");
        printf("==============Boarding_Pass================\n");
        printf("Nom: %s   -   Prenom: %s \n", f->passengers[i].surname, f->passengers[i].name);
        printf("Place: %d  -   Billet: %d \n", f->passengers[i].place, f->passengers[i].ticket);
        printf("Depart: %s   -   Arrivee: %s \n", f->departure, f->arrival);
        if(f->passengers[i].priority==1){printf("Passager prioritaire. \n");}
        else{printf("Passager non prioritaire. \n");}
        printf("==========================================\n");
        printf("\n");

        f->passengers[i].isRegistered = 1;

        ticketBag(f, f->passengers[i]);

        return 0;
    }

    printf("\nAucun passager avec ce numero de billet n'est inscrit ! \n\n");
    return -1;
}

int loadPassengerBag(flight *f , passenger p){
    for (int k = 0; k < p.nb_bags; k++) {
        f->bagsLoaded[f->nbBags] = p.bag[k];
        f->nbBags++;
    }
}

int checkBeforeLoading(flight *f){
    int nbPriority = 0;
    for (int i = 0; i < f->nbPassengers; i++) {
        if (f->passengers[i].priority == 1) {
            nbPriority++;
        }
    }

    if (f->nbPassengersLoaded < nbPriority) {
        printf("Tous les prioritaires doivent embarquer avant !\n");
        return -1;
    }

    return 0;
}

int loadPassenger(flight *f ){
    int ticket;

    printf("Veuillez entrez le numero du billet du passager !\n");
    scanf("%d", &ticket);

    for (int j = 0; j < f->nbPassengers; j++) {
        if (f->passengers[j].ticket != ticket) continue;

        if (!(f->passengers[j].isRegistered)) {
            printf("Ce passager n'a pas ete enregistre, il faurait l'enregistrer avant de l'embarquer ! \n");
            return -1;
        }


        if(!(f->passengers[j].priority)){

            checkBeforeLoading(f);
            loadPassengerBag(f, f->passengers[j]);
            checkHandBag(&f->passengers[j]);

            printf("Le passager %s %s a embarque sur le vol %d \n", f->passengers[j].surname, f->passengers[j].name, f->id);
            f->passengersLoaded[f->nbPassengersLoaded] = f->passengers[j];
            f->nbPassengersLoaded++;

            return 0;

        }

        loadPassengerBag(f, f->passengers[j]);
        checkHandBag(&f->passengers[j]);

        printf("Le passager %s %s a embarque sur le vol %d \n", f->passengers[j].surname, f->passengers[j].name,
               f->id);
        f->passengersLoaded[f->nbPassengersLoaded] = f->passengers[j];
        f->nbPassengersLoaded++;

        return 0;

    }

    printf("Aucun passager avec ce billet n'a ete trouve ! \n");
    return -1;

}