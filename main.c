#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "passenger/passenger.c"


int main()
{
    long int u, choice;
    time(&u);
    srand(u);

    printf("Bie,venue dans le logiciel de gestion de l'aeroport !\n");
    printf("Veuillez choisir le fonction voulue en tapant le numero associe !\n");
    printf("\n");
    printf("1 - Ajouter un vol !\n");
    printf("2 - Ajouter un passager sur un vol !\n");
    printf("3 - Enregistrer un passager sur un vol !\n");
    printf("4 - Passer la douane pour un passager !\n");
    printf("5 - Embarquer un vol !\n");
    scanf("%d", &choice);

    flight vol1;
    vol1.id = 1;
    vol1.nb = 0;
    strcpy(vol1.arrival,  "Antique");
    strcpy(vol1.departure,  "France");
//


    switch (choice){
        case 1:
            printf("Vous avez chosi d'ajouter un vol !\n");
            break;
        case 2:
            add_passenger(&vol1);
            save_passenger(&vol1);
            printf("Vous avez chosi d'ajouter un passager sur un vol !\n");
            break;
        case 3:
            printf("Vous avez chosi d'enregistrer un passager sur un vol !\n");
            break;
        case 4:
            printf("Vous avez chosi d'e faire passer la douane à un passager !\n");
            break;
        case 5:
            printf("Vous avez chosi d'embarquer un vol !\n");
            break;
        default:
            break;
    }

    /*flight vol1;
    vol1.id = 1;
    vol1.nb = 0;
    strcpy(vol1.arrival,  "Antique");
    strcpy(vol1.departure,  "France");

    add_passenger(&vol1);
    save_passenger(&vol1);*/

    return 0;
}
