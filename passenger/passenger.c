#pragma once
#include "passenger.h"

#include "stdio.h"
#include "../flight/flight.h"
#include "../flight/flight.c"
#include "../bag/bag.c"

int save_passenger(int id);
int add_passenger(int id);

/*============================================================*/

int add_passenger(int id){

    flight* f = find(id) ;
    if(! f) return -1 ;


    passenger *passenger1 = malloc(sizeof(passenger));
    passenger1->nb_bags = 0;

    printf("\n \n");
    printf("Le vol choisi : depart-> %s  arrivee -> %s \n \n", f->departure, f->arrival);
    printf("--------------------------------\n \n");

    printf("Est-ce un passager prioritaire ? \n");
    scanf("%d", &passenger1->priority);

    printf("Veuillez entrez le nom de famille du passager ! \n");
    scanf("%s", passenger1->surname);
    printf("Veuillez entrez le prenom du passager !\n");
    scanf("%s", passenger1->name);
    printf("Veuillez entrez l'age du passager !\n");
    scanf("%d", &passenger1->age);
    printf("Veuillez entrez la date de naissance du passager du passager !\n");
    printf("Veuillez indiquer le jour de naissance.\n");
    scanf("%d", &passenger1->birthday[0]);
    while (passenger1->birthday[0] < 0 || passenger1->birthday[0] > 31){
        printf("Jour incorrect ! Veuillez indiquer le jour de naissance.\n");
        scanf("%d", &passenger1->birthday[0]);
    }
    printf("Veuillez indiquer le mois de naissance !\n");
    scanf("%d", &passenger1->birthday[1]);
    while (0 > passenger1->birthday[1] || passenger1->birthday[1] > 12){
        printf("Mois incorrect ! Veuillez indiquer le mois de naissance.\n");
        scanf("%d", &passenger1->birthday[1]);
    }

    printf("Veuillez indiquer l'année de naissance !\n");
    scanf("%d", &passenger1->birthday[2]);
    while  (passenger1->birthday[2] < 1900 || passenger1->birthday[2] > 2019){
        printf("Année incorrect ! Veuillez indiquer  l'annee de naissance.\n");
        scanf("%d", &passenger1->birthday[2]);
    }

    printf("Veuillez indiquer le numéro du passport du passager. \n");
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
    printf("Nombre de bagagges:  %d \n", passenger1->nb_bags);

    printf("===============================================\n");

    f->passengers[f->nb] = *passenger1;
    f->nb = f->nb + 1;

    printf("\n \n");

    return 0;

}


int save_passenger(int id){

    flight* f = find(id) ;
    if(! f) return -1 ;

    int ticket, i, choice;
    passenger passenger1;

    printf("Indiquez le numéro du billet !\n");
    scanf("%i", &ticket);

    for(i = 0; i < f->nb; i++){
        if(f->passengers[i].ticket != ticket) continue;


        passenger1 = f->passengers[i];

        printf("Le passager souhaite il avoir une place spécifique  ?");
        scanf("%d", &choice);

        if(choice == 1){
            printf("Ecrire la place souhaitez  < 0 et > 501!");
            scanf("%d", &choice);
            int response = give_Specific_Place(f, choice);

            while(response == 0){
                printf("Cette place n'est pas disponible");
                scanf("%d", &choice);
                response = give_Specific_Place(f, choice);
            }

            passenger1.place = response;

        }else{
            passenger1.place = give_place(f);

        }
        printf(" \n \n");
        printf("==============Bording_Pass================\n");
        printf("Nom: %s   -   Prenom: %s \n", passenger1.surname, passenger1.name);
        printf("Place: %d  -   Billet: %i \n", passenger1.place, passenger1.ticket);
        printf("Depart: %s   -   Arrivee: %s \n", f->departure, f->arrival);
        printf("==========================================\n");
        printf("\n");

        ticket_bag(f, passenger1);
        return 0;
    }

    printf(" \n");
    printf("Aucun passager avec ce numero de billet est inscrit ! \n");
    printf("\n \n");
    return -1;

}