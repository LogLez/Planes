#pragma once

typedef struct s_bag{
    int priority, kg, nb_items;
    char items[20][30];
} bag;
typedef struct s_bag_cabine{
    int kg, nb_items;
    char items[20][30];
} bag_cabine;
