#pragma once
#include "bag.h"

void add_bag(passenger* passenger1);
void ticket_bag(flight* vol1, passenger passenger1);


/*============================================================*/


void add_bag(passenger* passenger1){
    int choice;

    if(passenger1->priority == 1){
        printf("Souhaitez-vous enregistrer un bagage prioritaire ?\n");
        scanf("%i", &choice);
        if(choice == 1){
            bag bag1;
            bag1.priority = 1;

            printf("Veuillez indiquez le poids du baggage ? \n");
            scanf("%d", &bag1.kg);
            printf("Combien d'items comportera votre baggage ? \n");
            scanf("%d", &bag1.nb_items);

            for(int i = 0; i<bag1.nb_items; i++){
                printf("Indiquez votre %d item ? \n", i + 1);
                scanf("%s", bag1.items[i]);
            }

            printf("Vous avez enregistrer un bagage prioritaire ! \n");

            passenger1->bag[0] = bag1;
            passenger1->nb_bags = passenger1->nb_bags + 1;
        }
    }

    printf("Souhaitez-vouis enregistrer un baggae non-prioritaire ? \n");
    scanf("%i", &choice);
    if(choice == 1){
        bag bag1;

        printf("Veuillez indiquez le poids du baggage ? \n");
        scanf("%d", &bag1.kg);
        printf("Combien d'items comportera votre baggage ? \n");
        scanf("%d", &bag1.nb_items);

        for(int i = 0; i<bag1.nb_items; i++){
            printf("Indiquez votre %d item ? \n", i + 1);
            scanf("%s", bag1.items[i]);
        }

        if(passenger1->nb_bags == 1){
            bag1.priority = 1;
            passenger1->bag[1] = bag1;
        }else{
            bag1.priority = 0;
            passenger1->bag[0] = bag1;
        }

        printf("Vous avez enregistrer un baggage  ! \n");
        passenger1->nb_bags = passenger1->nb_bags + 1;
    }
}

void ticket_bag(flight* vol1, passenger passenger1){

    for(int j=0; j<passenger1.nb_bags;j++){
        bag bag1 = passenger1.bag[j];
        printf("-------------Ticket_Baggage-------------\n");
        printf("Nom: %s   -   Prenom: %s \n", passenger1.surname, passenger1.name);
        printf("Items: ");
        for(int k = 0; k<bag1.nb_items;k++){
            printf("%s ,", bag1.items[k]);
        }
        printf("\n");
        printf("Poids: %dkg  \n", bag1.kg);
        printf("Depart: %s   -   Arrivee: %s \n", vol1->departure, vol1->arrival);
        if(bag1.priority == 1)  printf("Baggage prioritaire: 1  \n");
        if(bag1.priority == 0) printf("Baggage non-prioritaire: 1  \n");
        printf("----------------------------------------\n");
    }
}