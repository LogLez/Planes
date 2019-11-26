
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