#ifndef PROJEKT_KONCOWY_PP_IMPLANT_DEF_H
#define PROJEKT_KONCOWY_PP_IMPLANT_DEF_H

typedef enum {
    LEGAL,
    GRAY_AREA,
    ILLEGAL
} ImplantStatus;

typedef struct statistics {
    int legal_counter;
    int illegal_counter;
    int gray_area_counter;
}stats;

typedef struct implant {
    char name[101];
    char developer[128];
    int risk;
    double energy;
    ImplantStatus status;
    char id[128];

}Implant;

typedef struct node {
    Implant data;
    struct node* next;
}Node;

#endif //PROJEKT_KONCOWY_PP_IMPLANT_DEF_H