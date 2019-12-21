/**
 * \file main.c
 * \brief Programme principal.
 * \author Rayane.M & Lorène.B
 * \version 0.1
 * \date 26 octobre 2019
 *
 * Programme principal pour l'objet de gestion des différents menus.
 *
 */
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "passenger/passenger.c"
#include "flight/flight.c"
#include "bag/bag.c"

/**
* \fn send_menu()
* \brief  Fonction d'affichage d'un menu
 *        propose différents choix à l'utilisateur
* \return choice
*/


int send_menu()
{
    getItemsForbidden();
    int choice;
    printf("\n");
    printf("===============================Menu======================================\n");
    printf("Veuillez choisir une fonction !\n");
    printf("\n");
    printf("1 - Ajouter un vol !\n");
    printf("2 - Mettre %c jour un vol existant !\n", 133);
    printf("3 - Bonus, informations sur une p%criode de vols ! \n", 130);
    printf("\n");
    printf("0 - Quitter le logiciel !\n");
    printf("========================================================================\n");

    scanf("%d", &choice);
    return choice;
}

/**
* \fn flightMenu()
* \brief  Fonction d'affichage d'un menu
 *        propose différents choix concernant un vol à l'utilisateur
* \param  f flight sur lequel le passager est inscrit, ne peut être NULL.
* \return 0
*/

int flightMenu(flight *f){

    int choice;
    printf("\n");
    printf("===============================Modifier vol : %d ====================================== \n", f->id);
    printf("Veuillez choisir une fonction !\n");
    printf("\n");
    printf("1 - Ajouter un passager sur ce vol (Achat du billet) !\n");
    printf("2 - Enregistrer un passager sur ce vol et passer les frontieres (Visa) !\n");
    printf("3 - Faire passer la s%ccurit%c et embarquer un passager sur ce vol !\n", 130, 130);
    printf("4 - Charger les bagages  ! \n");
    printf("5 - Faire d%ccoller ce vol !\n", 130);
    printf("\n");
    printf("Appuyez sur n'importe quel autre num%cro pour retourner au menu principal !\n", 130);
    printf("==============================================================================\n");

    scanf("%d", &choice);

    switch(choice){

        case 1:
            addPassenger(f);
            break;
        case 2:
            savePassenger(f);
            break;
        case 3:
            loadPassenger(f);
            break;
        case 4:
            loadBags(f);
            break;
        case 5:
            sendFlight(f);
            break;
        default:
            printf("Ce menu n'existe pas !\n");
            break;

    }
    return 0;
}


int main()
{
    long int u;
    int choice, id, day, month, finalDay, finalMonth;
    time(&u);
    srand(u);

    getFlights();
    showFlights();

    choice = send_menu();

    while (choice != 0){
        switch (choice){
            case 1:
                printf("Tr%cs bien, nous allons proc%cder %c l'ajout d'un vol ! \n", 138, 130, 133);
                addFlight();
                break;
            case 2:
                printf("Veuillez entrez l'id du vol ?\n");
                scanf("%d", &id);

                flight *f = find(id);

                if(f != NULL){
                    flightMenu(f);
                }else{
                    printf("Ce vol est introuvable !\n");
                }
                break;

            case 3:
                printf("Tres bien, nous allons proc%cder %c la r%ccuperation de la p%criode de vol ! \n",130,133,130,130);
                printf("Attention, cette fonctionnalit%c ne prends pas en compte le changement d'ann%ce (2018/2019) mais seulement sur une ann%ce ! \n\n", 130 ,130,130);
                printf("Veuillez entrez  Le jour et mois de depart de d'arrivee ! \n");
                do{
                    printf("d%cpart: jour < 32 et > 0 \n", 130);
                    scanf("%d", &day);
                }while(1 > day || day > 31);
                do{
                    printf("d%cpart: mois  < 13 et > 0 \n", 130);
                    scanf("%d", &month);
                }while(1 > month || month > 12);
                do{
                    printf("arriv%ce: jour  < 32 et > 0\n", 130);
                    scanf("%d", &finalDay);
                }while(1 > day || day > 31);
                do{
                    printf("arriv%ce: mois  < 13 et > 0\n", 130);
                    scanf("%d", &finalMonth);
                }while(1 > month || month > 12);

                printf("Vous avez choisi la p%criode %d/%d à %d/%d\n",130, day, month, finalDay, finalMonth);
                getPeriod(day, month, finalDay, finalMonth);
                break;

            default:
                printf("Ce menu n'existe pas ! \n");
                break;
        }
        choice = send_menu();
    }

    saveItemsForbidden();
    saveFlights();
    printf("Bonne continuation !\n");
}
