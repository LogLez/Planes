/**
 * \file passenger.c
 * \brief Programme répertoriant les fonctions relatifs aux passengers.
 * \author Rayane.M & Lorène.B
 * \version 0.1
 * \date 26 octobre 2019
 *
 * Programme de passagers pour l'objet de gestion des passagers relatifs aux vols.
 * Permet d'ajouter un passager sur un vol, l'enregistrer, l'embarquer s'il le peut, vérifier ses bagages
 * et montrer ses informations.
 */

#pragma once
#include "passenger.h"

#include "stdio.h"
#include "../flight/flight.h"
#include "../flight/flight.c"
#include "../bag/bag.c"

void showBillet(flight *f, passenger *p);
int addPassenger(flight *f );
int crossBorder(flight *f, passenger p);
int savePassenger(flight *f);
int checkBeforeLoading(flight *f);
int loadPassenger(flight *f );

/*============================================================*/

/**
* \fn showBillet(flight *f, passenger *p)
* \brief  Fonction d'affichage du boarding pass
* \param  f un pointeur sur le vol dont le passager est inscrit, ne peut être NULL.
* \param  p un pointeur sur le passager concerné par le billet, ne peut être NULL.
* \return void
*/

void showBillet(flight *f, passenger *p){
    printf(" \n \n");
    printf("===============================================\n");
    printf("Nom: %s            -   Pr%cnom: %s \n", p->surname, 130, p->name);
    printf("Age: %d                -   Date de naissance : %d/%d/%d\n", p->age, p->birthday[0], p->birthday[1],  p->birthday[2]);
    printf("Passeport: %d        -   Billet: %d \n", p->passport_number, p->ticket);
    printf("D%cpart: %s           -   Arriv%ce: %s \n", 130, f->departure, 130, f->arrival);
    printf("Nombre de bagages:  %d \n", p->nb_bags);
    if(p->priority == 1){
        printf("Passager prioritaire \n");
    }else{
        printf("Passager non prioritaire \n");
    }

    printf("===============================================\n");
}

/**
* \fn addPassenger(flight *f )
* \brief  Fonction d'ajout d'un passager.
*        Récupère des informations concernant le passager pour l'ajouter sur le vol
* \param  f un pointeur sur le vol dont le passager veut s'inscrire, ne peut être NULL.
* \return 0
*/


int addPassenger(flight *f ){
    printf("Bienvenue dans la cat%cgorie : Ajouter un passager !\n", 130);

    passenger *p = malloc(sizeof(passenger));
    p->nb_bags = 0;
    p->isRegistered = 0;
    p->visa = 0;

    printf("\n \n");
    printf("Rappel: Vol  : d%cpart-> %s  arriv%ce -> %s \n \n", 130, f->departure, 130, f->arrival);
    printf("-------------------------------- \n");

    if(hasVisa(f, p) == -1) return -1;
    strcpy(p->destination,f->arrival);

    printf("Est-ce un passager prioritaire ? (1 = OUI, 0 = NON)\n");
    scanf("%d", &p->priority);

    printf("Veuillez entrer le nom de famille du passager ! \n");
    scanf("%s", p->surname);
    printf("Veuillez entrer le pr%cnom du passager !\n", 130);
    scanf("%s", p->name);
    printf("Veuillez entrer l'age du passager !\n");
    scanf("%d", &p->age);
    printf("Veuillez entrer la date de naissance du passager !\n");
    printf("Veuillez indiquer le jour de naissance.\n");
    scanf("%d", &p->birthday[0]);
    while (p->birthday[0] <= 0 || p->birthday[0] > 31){
        printf("Jour incorrect ! Veuillez indiquer le jour de naissance. ( < 0 et > 32)\n");
        scanf("%d", &p->birthday[0]);
    }
    printf("Veuillez indiquer le mois de naissance !\n");
    scanf("%d", &p->birthday[1]);
    while ( (p->birthday[0] > 28 && p->birthday[1] == 2 ) || (p->birthday[1] <=  0) || (p->birthday[1] > 12) ){
        printf("Mois incorrect ! Veuillez indiquer le mois de naissance. ( > 0 et < 13) ou (diff. de 2 si il y a plus de 28 jours)\n");
        scanf("%d", &p->birthday[1]);
    }

    printf("Veuillez indiquer l'ann%ce de naissance !\n", 130);
    scanf("%d", &p->birthday[2]);
    while  (p->birthday[2] < 1900 || p->birthday[2] >= 2019){
        printf("Ann%ce incorrecte ! Veuillez indiquer  l'ann%ce de naissance valide.\n", 130 ,130);
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

    return 0;

}

/**
* \fn crossBorder(flight *f, passenger p)
* \brief  Fonction de passage des frontières
 *        Autorise le passager à passer les frontiières si, lorsque le vol nécéssite un visa, le passager en possède un
* \param  f un pointeur sur le vol dont le passager est inscrit, ne peut être NULL.
* \param  p le passenger concerné par le visa, ne peut être NULL.
* \return -1 si il possède pas de visa, 0 si il l'a ou que le vol ne demande pas de visa.
*/


int crossBorder(flight *f, passenger p){

    printf("Le passager %s %s veut se rendre en %s !\n", p.surname, p.name, f->arrival);
    if(f->visa == 1){
        printf("Ce vol demande un visa au passager !\n");
        if(p.visa == 1){
            printf("et %s %s poss%cde bien un visa \n", p.surname, p.name, 138);
        }else{
            printf("et %s %s ne poss%cde pas de visa \n", p.surname
                    , p.name, 138);
            return -1;
        }
    }else{
        printf("Ce vol ne demande pas de visa \n");

    }
    return 0;
}

/**
* \fn savePassenger(flight *f)
* \brief  Fonction d'enregistrement d'un passager sur un vol
*        vérifie que le passager n'a pas déjà été enregistré
*        attribue une place au passager
*        fait passer les frontières au passager
*        affiche le boarding pass
* \param  f un pointeur sur le vol dont le passager est inscrit, ne peut être NULL.
* \return -1 si échec, 0 si réussi.
*/


int savePassenger(flight *f){

    int ticket, i, choice, response;

    printf("Indiquez le num%cro du billet du passager !\n", 130);
    scanf("%i", &ticket);

    for(i = 0; i < f->nbPassengers; i++){
        if(f->passengers[i].ticket != ticket) continue;

        if(f->passengers[i].isRegistered == 1){
            printf("Ce passager %c d%cj%c %ct%c enregistr%c, il faurait l'embarquer maintenant ! \n", 133,130,133, 130, 130, 130);
            return -1;
        }


        printf("Le passager souhaite t-il avoir une place sp%ccifique  ? (1 = OUI, 0 = NON)\n", 130);
        scanf("%d", &choice);

        if(choice != 1){
            f->passengers[i].place = randomPlace(f);
        }else{
            printf("Ecrire la place souhait%ce  > 0 et < 501! \n", 130);
            scanf("%d", &choice);
            response = specificPlace(f, choice);

            while(response == 0){
                printf("Cette place n'est pas disponible, veuillez saisir une nouvelle place. \n");
                scanf("%d", &choice);
                response = specificPlace(f, choice);
            }

            f->passengers[i].place= response;

        }

        if(crossBorder(f, f->passengers[i]) != 0) printf("Une erreur est survenue avec le visa du passager ! \n");

        printf(" \n \n");
        printf("==============Boarding_Pass================\n");
        printf("Nom: %s   -   Pr%cnom: %s \n", f->passengers[i].surname, 130, f->passengers[i].name);
        printf("Place: %d  -   Billet: %d \n", f->passengers[i].place, f->passengers[i].ticket);
        printf("D%cpart: %s   -   Arriv%ce: %s \n", 130, f->departure, 130, f->arrival);
        if(f->passengers[i].priority==1){printf("Passager prioritaire. \n");}
        else{printf("Passager non prioritaire. \n");}
        printf("==========================================\n");
        printf("\n");

        f->passengers[i].isRegistered = 1;
        ticketBag(f, f->passengers[i]);

        return 0;
    }

    printf("\nAucun passager avec ce num%cro de billet n'est inscrit ! \n\n", 130);
    return -1;
}

/**
* \fn checkBeforeLoading(flight *f)
* \brief  Fonction de vérification pour l'embarquement
*         vérifie que tous les passagers prioritaires ont embarqué
* \param  f un pointeur sur le vol dont le passager est inscrit, ne peut être NULL.
* \return -1 échec, 0 si réussi.
*/


int checkBeforeLoading(flight *f){
    int nbPriority = 0;
    for (int i = 0; i < f->nbPassengers; i++) {
        if (f->passengers[i].priority == 1) {
            nbPriority++;
        }
    }

    if (f->nbPassengersLoaded < nbPriority) {
        printf("Impossible, tous les prioritaires doivent embarquer avant !\n");
        return -1;
    }

    return 0;
}

/**
* \fn loadPassenger(flight *f)
* \brief  Fonction d'embarquement des passagers
*        vérifie que le passager est enregistré pour l'embarquer
*        fait passer la sécurité pour vérifier les sacs cabines
* \param  f un pointeur sur le vol dont le passager est inscrit, ne peut être NULL.
* \return -1 si le passager n'a pas été touvé, 0 si cas contraire.
*/


int loadPassenger(flight *f ){
    int ticket;

    printf("Indiquez le num%cro du billet du passager !\n", 130);
    scanf("%i", &ticket);

    for(int j = 0; j < f->nbPassengers; j++){
        if(f->passengers[j].ticket != ticket) continue;

        if (!(f->passengers[j].isRegistered)) {
            printf("Ce passager n'a pas %ct%c enregistr%c, il faudrait l'enregistrer avant de l'embarquer ! \n", 130, 130, 130);
            return -1;
        }


        if(!(f->passengers[j].priority)){

            checkBeforeLoading(f);
            checkHandBag(&f->passengers[j]);

            printf("Le passager %s %s a embarqu%c sur le vol %d \n", f->passengers[j].surname, f->passengers[j].name,130, f->id);
            f->passengersLoaded[f->nbPassengersLoaded] = f->passengers[j];
            f->nbPassengersLoaded++;

            return 0;

        }


        checkHandBag(&f->passengers[j]);

        printf("Le passager %s %s a embarqu%c sur le vol %d \n", f->passengers[j].surname, f->passengers[j].name, 130, f->id);
        f->passengersLoaded[f->nbPassengersLoaded] = f->passengers[j];
        f->nbPassengersLoaded++;

        return 0;

    }

    printf("Aucun passager avec ce billet n'a %ct%c trouve ! \n", 130, 130);
    return -1;

}