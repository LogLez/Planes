/**
 * \file bag.c
 * \brief Programme répertoriant les fonctions relatifs aux bagages.
 * \author Rayane.M & Lorène.B
 * \version 0.1
 * \date 26 octobre 2019
 *
 * Programme de bagages pour l'objet de gestion des bagages relatifs au passagers d'un vol.
 *
 */

#pragma once
#include "bag.h"

int saveItemsForbidden();
int getItemsForbidden();

void addBag(passenger* passenger1);
void ticketBag(flight* f, passenger passenger1);
void loadBags(flight* vol1);
void addHandBag(passenger* p);
void checkHandBag(passenger* p);

int nbItemsForbidden = 0;
char itemsForbidden[100][50];
/*============================================================*/

/**
 * \fn int saveItemsForbidden()
 * \brief Fonction de sauvegarde des items interdits dans un fichier.
 *        Recupère les items du tableau itemsForbidden[100][50] et les
 *        sauvegarde dans un fichier.
 * \return 0 si reussi, -1 si echec.
 */

int saveItemsForbidden(){
    FILE *outfile;
    outfile = fopen ("/Users/lorenebergougnoux/Desktop/NF05/TD8/td8/items.txt" , "w");
    if (outfile == NULL){
        fprintf(stderr, "\nLe fichier n'existe pas ! V%crifiez le nom du repertoire.\n", 130);
        return -1;
    }

    fprintf(outfile, "%d \n", nbItemsForbidden);

    for (int i = 0; i < nbItemsForbidden; i++){
           fprintf(outfile, "%s\n", itemsForbidden[i]);
    }
    fclose(outfile);
    return 0;
}

/**
 * \fn int getItemsForbidden()
 * \brief Fonction de récupération des items interdits depuis un fichier.
 *        Charge les items dans le tableau itemsForbidden[100][50] depuis un
 *        fichier.
 * \return 0 si reussi, -1 si echec.
 */

int getItemsForbidden(){
    FILE *infile;
    infile = fopen ("/Users/lorenebergougnoux/Desktop/NF05/TD8/td8/items.txt", "r");
    if (infile == NULL) {
        fprintf(stderr, "\nLe fichier n'existe pas ! Il sera cr%ce a la fin du programme.\n", 130);
        return -1;
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

/**
 * \fn void addBag(passenger* p){
 * \brief Fonction de création de un ou des bagages pour un passager.
 *        Ajout de 1 bagage ou 2 si le passager est priritaire.
 *
 * \param p un pointeur sur le passenger dont on souhaite ajouter les bagages , ne peut être NULL.
 * \return void
 */
void addBag(passenger* p){
    int choice;

    if(p->priority == 1){
        printf("Souhaitez-vous enregistrer un bagage prioritaire ? (1 = OUI, 0 = NON)\n");
        scanf("%i", &choice);
        if(choice == 1){
            bag b;
            b.priority = 1;

            printf("Veuillez indiquez le poids du baggage ? (en kg) \n");
            scanf("%d", &b.kg);
            printf("Combien d'items comportera votre bagage ? \n");
            scanf("%d", &b.nbItems);

            for(int i = 0; i<b.nbItems; i++){
                printf("Indiquez votre %d item ? \n", i + 1);
                scanf("%s", b.items[i]);
            }

            printf("Vous avez enregistre un bagage prioritaire ! \n");

            p->bag[0] = b;
            p->nb_bags = p->nb_bags + 1;
        }
    }

    printf("Souhaitez-vous enregistrer un bagage non-prioritaire ? (1 = OUI, 0 = NON)\n");
    scanf("%i", &choice);
    if(choice == 1){
        bag bag1;

        printf("Veuillez indiquer le poids du bagage ? (en kg)\n");
        scanf("%d", &bag1.kg);
        printf("Combien d'items comportera votre bagage ? \n");
        scanf("%d", &bag1.nbItems);

        for(int i = 0; i<bag1.nbItems; i++){
            printf("Indiquez votre %d item ? \n", i + 1);
            scanf("%s", bag1.items[i]);
        }

        if(p->nb_bags == 1){
            bag1.priority = 1;
            p->bag[1] = bag1;
        }else{
            bag1.priority = 0;
            p->bag[0] = bag1;
        }

        printf("Vous avez enregistr%c un baggage  ! \n", 130);
        p->nb_bags = p->nb_bags + 1;
    }
}

/**
 * \fn void ticketBag(flight* f, passenger passenger1);
 * \brief Fonction de création de un ou des tickets bagages  pour un passager.
 *        affiche les infos de chaque bagage d'un passager.
 *
 * \param f un pointeur sur le vol du passager , ne peut être NULL.
 * \param p un passager dont on souhaite afficher les informations des bagaes, ne peut être NULL.
 * \return void
 */
void ticketBag(flight* f, passenger p){

    for(int j=0; j<p.nb_bags;j++){
        bag bag1 = p.bag[j];
        printf("-------------Ticket_Baggage-------------\n");
        printf("Nom: %s   -   Pr%cnom: %s \n", p.surname, 130, p.name);
        if(bag1.nbItems != 0) {
            printf("Items: ");
            for (int k = 0; k < bag1.nbItems; k++) {
                printf("%s, ", bag1.items[k]);
            }
        }
        else{
            printf("Aucun item.");
        }
        printf("\n");
        printf("Poids: %dkg  \n", bag1.kg);
        printf("D%cpart: %s   -   Arrivee: %s \n", 130, f->departure, f->arrival);
        if(bag1.priority == 1)  printf("Baggage prioritaire: 1  \n");
        if(bag1.priority == 0 ) printf("Baggage non-prioritaire: 1 \n");
        printf("----------------------------------------\n");
    }
}

/**
 * \fn void loadBags(flight* f)
 * \brief Fonction de chargement des bagages dans un vol.
 *        Charge tous les bagages de tous les passagers d'un vol.
 *
 * \param  f un pointeur sur le vol dont on souhaite charger les bagages, ne peut être NULL.
 * \return void
 */
void loadBags(flight* f){

    for(int i = 0; i < f->nbPassengersLoaded; i++){

        if(f->passengersLoaded[i].priority != 1) continue;

        for(int j = 0; j <f->passengersLoaded[i].nb_bags;j++){
            printf("Bagage prioritaire de %s %s charg%c et embarqu%c ! \n", f->passengersLoaded[i].name,f->passengersLoaded[i].surname, 130 ,130);
            f->bagsLoaded[f->nbBags] = f->passengersLoaded[i].bag[j];
            f->nbBags++;
        }
    }

    for(int i = 0; i < f->nbPassengersLoaded; i++){

        if(f->passengersLoaded[i].priority == 1) continue;

        for(int j = 0; j <f->passengersLoaded[i].nb_bags;j++){
            printf("Bagage de %s %s charg%c et embarqu%c ! \n", f->passengersLoaded[i].name,f->passengersLoaded[i].surname, 130, 130);
            f->bagsLoaded[f->nbBags] = f->passengersLoaded[i].bag[j];
            f->nbBags++;
        }
    }
}

/**
 * \fn void addHandBag(passenger* p)
 * \brief Fonction de création d'un handBag d'un passager (sac à dos, ou sac à main).
 *        Charge tous les bagages de tous les passagers d'un vol.
 * \param  p un pointeur sur le passager dont le handBag doit être ajouté, ne peut être NULL.
 * \return void
 */
void addHandBag(passenger* p) {

    printf("Combien d'items comportera votre bagage cabine ? \n");
    scanf("%d", &p->handbag.nbItems);

    for (int i = 0; i < p->handbag.nbItems; i++) {
        printf("Indiquez votre %d item ? \n", i + 1);
        scanf("%s", p->handbag.items[i]);
    }
}

/**
 * \fn void checkHandBag(passenger *p)
 * \brief Fonction de vérification des objets d'un handBag d'un passager (sac à dos, ou sac à main).
 *        Vérifie tous les items un par un et retire un item si celui-ci est interdit.
 *
 * \param  p un pointeur sur le passager dont le handBag doit être vérifier, ne peut être NULL.
 * \return void
 */
void checkHandBag(passenger *p) {

    for (int i = 0; i < nbItemsForbidden; i++) {

        for (int k = 0; k < p->handbag.nbItems; k++) {

            int compare = strcmp(itemsForbidden[i], p->handbag.items[k]);
            if (compare == 0) {

                printf("L'%cl%cment %s est interdit au sein des bagages ! \n", 130, 130, p->handbag.items[k]);
                printf("L'%cl%cment %s va être supprime de votre bag ! \n", 130, 130, p->handbag.items[k]);

                for (int l = k; l < p->handbag.nbItems - 1; l++) {

                    strcpy(p->handbag.items[l], p->handbag.items[l + 1]);

                }
                p->handbag.nbItems--;

            }
        }
    }
}