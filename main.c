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
    printf("===============================Menu====================================== \n");
    printf("Veuillez choisir une fonction !\n");
    printf("\n");
    printf("1 - Ajouter un vol !\n");
    printf("2 - Mettre a jour un vol existant !\n");
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
    printf("2 - Enregistrer un passager sur ce vol !\n");
    printf("3 - Embarquer un passager sur ce vol !\n");
    printf("4 - Charger les bagages  ! \n");
    printf("5 - Faire décoller ce vol !\n");
    printf("\n");
    printf("Appuyez sur n'importe quelle autre numéro pour retourner au menu principal !\n");
    printf("==============================================================================\n");

    scanf("%d", &choice);

    switch(choice){

        case 1:
            addPassenger(f);
            break;
        case 2:
            showBags(f);
            //savePassenger(f);
            break;
        case 3:
            loadPassenger(f);
            break;
        case 4:
            loadBags(f);
            break;
        case 5:
            //TODO
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
    int choice, id;
    time(&u);
    srand(u);

    getFlights();
    showFlights();

    choice = send_menu();

    while (choice != 0){
        switch (choice){
            case 1:
                printf("Tres bien, nous allons proceder a l'ajout d'un vol ! \n");
                add_flight();
                break;
            case 2:
                printf("Veuillez entrez l'id du vol ?");
                scanf("%d", &id);

                flight *f = find(id);

                if(f != NULL){
                    flightMenu(f);
                }else{
                    printf("Ce vol est introuvable !");
                }
                break;
            default:
                printf("Ce menu n'existe pas ! \n");
                break;
            }

            choice = send_menu();
        }
    saveItemsForbidden();
    saveFlights();
    printf("Bonne continuation !");
}
