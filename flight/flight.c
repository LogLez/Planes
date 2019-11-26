
int give_Specific_Place(flight *vol1, int place) {

    if(vol1->nb == 1)
        return place;

    for(int i = 0 ; i<vol1->nb;i++){
        if(vol1->passengers[i].place != place) continue;
        return 0;
    }

    return place;
}

int give_place(flight* vol1){
    int random = 1 + (500-1) * ( (float) rand()) / RAND_MAX;

    if(vol1->nb == 1)
        return random;

    for(int i = 0 ; i<vol1->nb;i++){
        if(vol1->passengers[i].place != random) continue;
        give_place(vol1);
        return 0;
    }

    return random;
}

void load_passengers(flight* vol1){
    int tab[500], k = 0;
    for(int i =0; i<vol1->nb;i++){
        if(vol1->passengers[i].priority != 1) continue;
        printf("Embarcation de %s %s \n", vol1->passengers[i].surname, vol1->passengers[i].name );
        vol1->passengers_saved[k] = vol1->passengers[i];
        tab[k] = i;
        k++;
    }

    printf("Il y a au total %d  passagers prioritaire. Tous ont été embarqué !\n", k);
    for(int i = 0; i<vol1->nb; i++){
        for(int j = 0; j<k; j++)if(i==tab[j]) continue;

        printf("Embarcation de %s %s \n", vol1->passengers[i].surname, vol1->passengers[i].name);
        vol1->passengers_saved[k] = vol1->passengers[i];
        k++;

    }

    vol1->passengers_loaded = k;

    if(vol1->passengers_loaded != vol1->nb){ printf("Erreur, tous les passagers n'ont pas embarqué ! \n"); return; }
    printf("Tous les passagers ont  embarqué ! \n");
}


void load_bags(flight* vol1){

    int tab[500], k = 0;

    for(int i = 0; i<500;i++){

        if(vol1->passengers_saved[i].priority != 1) continue;
        for(int j = 0; j <vol1->passengers_saved[i].nb_bags;j++){
            printf("Bag prioritaire chargé et embarqué ! \n");
            vol1->bags_loaded[k] = vol1->passengers_saved[i].bag[j];
            tab[k] = i;
            k++;
        }
    }

    for(int i = 0; i<500;i++){
        for(int j = 0; j<k; j++) if(i == tab[j]) break;

        for(int l = 0; l<vol1->passengers_saved[i].nb_bags; l++){
            printf("Bag chargé et embarqué ! \n");
            vol1->bags_loaded[k] = vol1->passengers_saved[i].bag[l];
            tab[k] = i;
            k++;
        }
    }

}