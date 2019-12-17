#pragma once
#include "bag.h"

void add_bag(passenger* passenger1);
void ticket_bag(flight* vol1, passenger passenger1);
void load_bags(flight* vol1);

int nbItemsForbidden = 0;
char itemsForbidden[100][50];
/*============================================================*/

int saveItemsForbidden(){
    FILE *outfile;
    outfile = fopen ("/Users/lorenebergougnoux/Desktop/NF05/TD8/td8/items.txt" , "w");
    if (outfile == NULL){
        fprintf(stderr, "\nLe fichier n'existe pas ! Il sera creer a la fin du programme.\n");
        return 0;
    }

    fprintf(outfile, "%d \n", nbItemsForbidden);

    for (int i = 0; i < nbItemsForbidden; i++){
           fprintf(outfile, "%s\n", itemsForbidden[i]);
    }
    fclose(outfile);
    return 0;
}

int getItemsForbidden(){
    FILE *infile;
    infile = fopen ("/Users/lorenebergougnoux/Desktop/NF05/TD8/td8/items.txt" , "r");
    if (infile == NULL) {
        fprintf(stderr, "\nLe fichier n'existe pas ! Il sera creer a la fin du programme.\n");
        return 0;
    }

    int i = 0;
    fscanf(infile, "%d", &nbItemsForbidden);

   while(i != nbItemsForbidden){
       fscanf(infile, "%s", itemsForbidden[i]);
       i++;
   }
    fclose(infile);
    return 0;
}

void showBags(flight* f){
    passenger *p = &f->passengers[0];
    for (int i = 0; i < p->nb_bags ; i++) {
        printf("Bag n %d :\n", i);
        for (int j = 0; j < p->bag[i].nbItems; j++) {
            printf(" %s ", p->bag[i].items[j]);

        }
        printf("\n");
    }
    free(p);
}
void add_bag(passenger* passenger1){
    int choice;

    if(passenger1->priority == 1){
        printf("Souhaitez-vous enregistrer un bagage prioritaire ?\n");
        scanf("%i", &choice);
        if(choice == 1){
            bag b;
            b.priority = 1;

            printf("Veuillez indiquez le poids du baggage ? \n");
            scanf("%d", &b.kg);
            printf("Combien d'items comportera votre baggage ? \n");
            scanf("%d", &b.nbItems);

            for(int i = 0; i<b.nbItems; i++){
                printf("Indiquez votre %d item ? \n", i + 1);
                scanf("%s", b.items[i]);
            }

            printf("Vous avez enregistrer un bagage prioritaire ! \n");

            passenger1->bag[0] = b;
            passenger1->nb_bags = passenger1->nb_bags + 1;
        }
    }

    printf("Souhaitez-vouis enregistrer un bagage non-prioritaire ? \n");
    scanf("%i", &choice);
    if(choice == 1){
        bag bag1;

        printf("Veuillez indiquez le poids du baggage ? \n");
        scanf("%d", &bag1.kg);
        printf("Combien d'items comportera votre baggage ? \n");
        scanf("%d", &bag1.nbItems);

        for(int i = 0; i<bag1.nbItems; i++){
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
        if(bag1.nbItems != 0) {
            printf("Items: ");
            for (int k = 0; k < bag1.nbItems; k++) {
                printf("%s ,", bag1.items[k]);
            }
        }
        else{
            printf("Aucun item. \n");
        }
        printf("\n");
        printf("Poids: %dkg  \n", bag1.kg);
        printf("Depart: %s   -   Arrivee: %s \n", vol1->departure, vol1->arrival);
        if(bag1.priority == 1)  printf("Baggage prioritaire: 1  \n");
        if(bag1.priority == 0 ) printf("Baggage non-prioritaire: 1 \n");
        printf("----------------------------------------\n");
    }
}


//TODO A TESTER
void loadBags(flight* f){

    for(int i = 0; i < f->nbPassengersLoaded; i++){

        if(f->passengersLoaded[i].priority != 1) continue;
        for(int j = 0; j <f->passengersLoaded[i].nb_bags;j++){
            printf("Bag prioritaire chargé et embarqué ! \n");
            f->bagsLoaded[f->nbBags] = f->passengersLoaded[i].bag[j];
            f->nbBags++;
        }
    }

    for(int i = 0; i < f->nbPassengersLoaded; i++){

        if(f->passengersLoaded[i].priority == 1) continue;
        for(int j = 0; j <f->passengersLoaded[i].nb_bags;j++){
            printf("Bag chargé et embarqué ! \n");
            f->bagsLoaded[f->nbBags] = f->passengersLoaded[i].bag[j];
            f->nbBags++;
        }
    }
}

//BONUS
int checkBag(passenger *p){

    for (int i = 0; i < nbItemsForbidden; ++i) {

        for (int j = 0; j < p->nb_bags; ++j) {

            for (int k = 0; k < p->bag[j].nbItems; ++k) {

                if(strcmp(itemsForbidden[i],  p->bag[j].items[k])){

                    printf("L'element %s est interdit au sein des bagages ! \n", p->bag[j].items[k]);
                    printf("L'element %s va être supprime de votre bag ! \n",  p->bag[j].items[k]);

                    for (int l = k; l < p->bag[j].nbItems ; ++l) {

                        //p->bag[j].items[l] = p->bag[j].items[l + 1];

                    }
                    p->bag[j].nbItems--;

                }

            }

        }


    }
    return 0;

}
