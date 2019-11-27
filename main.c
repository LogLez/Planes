#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "passenger/passenger.c"
#include "flight/flight.c"
#include "bag/bag.c"


int send_menu(){
    int choice;
    printf("\n");
    printf("===============================Menu====================================== \n");
    printf("Veuillez choisir le fonction voulue en tapant le numero associe !\n");
    printf("\n");
    printf("1 - Ajouter un vol !\n");
    printf("2 - Ajouter un passager sur un vol !\n");
    printf("3 - Enregistrer un passager sur un vol !\n");
    printf("4 - Passer la douane pour un passager !\n");
    printf("5 - Embarquer un vol !\n");
    printf("\n");
    printf("0 - Quitter le logiciel !\n");
    printf("========================================================================\n");

    scanf("%d", &choice);
    return choice;

}

void case1(){
    printf("Tres bien, nous allons proceder a l'ajout d'un vol ! \n");
    add_flight();
}
void case2(){
    int id;
    printf("Tres bien, nous allons proceder a l'ajout d'un passager sur un vol ! \n \n");
    printf("Veuillez entrez l'id du vol ?");
    scanf("%d", &id);

    if(0 == add_passenger(id)){
        printf("Passager ajoute avec succes ! \n");
    }else{
        printf("Une erreur est survenue avec le numero du vol ! \n");
    }
}

void case3(){
    int id;
    printf("Tres bien, nous allons proceder a l'enregistrement d'un passager ! \n \n");
    printf("Veuillez entrez l'id du vol ?");
    scanf("%d", &id);

    if(0 == save_passenger(id)){
        printf("Passager enregistre avec succes ! \n");
    }else{
        printf("Une erreur est survenue avec le billet ou le numero du vol ! \n");
    }
}

void case4(){
    printf("Tres bien, nous allons appliquer la douane a un passager ! \n");
    //TODO verifier la douane
}

void case5(){
    printf("Tres bien, nous allons embarquer les passagers d'un vol ! \n");
    //TODO tester la fonction load_passenger dans la classe flight.c
}



int main()
{
    long int u;
    int choice, id;
    time(&u);
    srand(u);

    printf("Bienvenue dans le logiciel de gestion de l'aeroport !\n");
    choice = send_menu();

    while (choice != 0){
        switch (choice){
            case 1:
                case1();
                break;
            case 2:
              case2();
                break;
            case 3:
               case3();
                break;
            case 4:
                case4();
                break;
            case 5:
                case5();
                break;
            default:
                printf("Cette fonctionnalite n'existe pas ! \n");
                break;
            }

            choice = send_menu();
        }
    printf("Bonne continuation !");
}
