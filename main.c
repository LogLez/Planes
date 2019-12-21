#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "passenger/passenger.c"
#include "flight/flight.c"
#include "bag/bag.c"


int send_menu()
{
    getItemsForbidden();
    int choice;
    printf("\n");
    printf("===============================Menu======================================\n");
    printf("Veuillez choisir une fonction !\n");
    printf("\n");
    printf("1 - Ajouter un vol !\n");
    printf("2 - Mettre a jour un vol existant !\n");
    printf("3 - Bonus, informations sur une periode de vols ! \n");
    printf("\n");
    printf("0 - Quitter le logiciel !\n");
    printf("========================================================================\n");

    scanf("%d", &choice);
    return choice;
}

int flightMenu(flight *f){

    int choice;
    printf("\n");
    printf("===============================Modifier vol : %d ====================================== \n", f->id);
    printf("Veuillez choisir une fonction !\n");
    printf("\n");
    printf("1 - Ajouter un passager sur ce vol (Achat du billet) !\n");
    printf("2 - Enregistrer un passager sur ce vol et passer les frontieres (Visa) !\n");
    printf("3 - Faire passer la sécurité et embarquer un passager sur ce vol !\n");
    printf("4 - Charger les bagages  ! \n");
    printf("5 - Faire décoller ce vol !\n");
    printf("\n");
    printf("Appuyez sur n'importe quel autre numéro pour retourner au menu principal !\n");
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
                printf("Tres bien, nous allons proceder a l'ajout d'un vol ! \n");
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
                printf("Tres bien, nous allons proceder a la recuperation de la periode de vol ! \n");
                printf("Attention, cette fonctionnalite ne prends pas en compte le changement d'annee (2018/2019) mais seulement sur une annee ! \n\n");
                printf("Veuillez entrez  Le jour et mois de depart de d'arrivee ! \n");
                do{
                    printf("depart: jour < 32 et > 0 \n");
                    scanf("%d", &day);
                }while(1 > day || day > 31);
                do{
                    printf("depart: mois  < 13 et > 0 \n");
                    scanf("%d", &month);
                }while(1 > month || month > 12);
                do{
                    printf("arrivee: jour  < 32 et > 0\n");
                    scanf("%d", &finalDay);
                }while(1 > day || day > 31);
                do{
                    printf("arrivee: mois  < 13 et > 0\n");
                    scanf("%d", &finalMonth);
                }while(1 > month || month > 12);

                printf("Vous avez choisi la periode %d/%d à %d/%d\n", day, month, finalDay, finalMonth);
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
