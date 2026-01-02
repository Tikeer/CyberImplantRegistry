#include <stdlib.h>
#include <stdio.h>
#include "implant_def.h"
#include "list_manager.h"
#include "logic.h"

Implant get_user_input() {
    Implant temp;
    int x = -1;

    printf("Podaj nazwe implantu:\n");
    scanf("%s", temp.name);
    printf("\n");

    printf("Podaj nazwe producenta:\n");
    scanf("%s", temp.developer);
    printf("\n");

    printf("Podaj ID wlasciciela:\n");
    scanf("%s", temp.id);
    printf("\n");

    printf("Podaj ryzyko implantu:\n");
    scanf("%d",&temp.risk);
    printf("\n");

    printf("Podaj poziom mocy energi:\n");
    scanf("%lf",&temp.energy);
    printf("\n");

    printf("Wybierz status implantu: \n");
    printf("1. LEGAL 2.GRAY_AREA 3.ILLEGAL\n");
    scanf(" %d",&x);

    switch (x) {
        case 1:
            temp.status = (ImplantStatus)x;
            break;
        case 2:
            temp.status = (ImplantStatus)x;
            break;
        case 3:
            temp.status = (ImplantStatus)x;
            break;
        default:
            printf("Podaj liczbe z zakresu 1-3:\n");
    }

    return temp;
}

int print_menu(Node* head) {
    int program = -1;

    system("cls");
    printf("Witaj w Neonowej Warszawie gdzie ulice nigdy nie spia\n");
    printf("Oto Centralny Rejestr Cybernetycznych Modyfikacji \n");
    printf("Wybierz co chcesz zrobic: \n");
    printf("1. Rejestracja implantu\n");
    printf("2. Wyszukiwanie danych o implantach\n");
    printf("3. Modyfikowanie danych o implantach\n");
    printf("4. Sortowanie danych\n");
    printf("5. Usuwanie danych\n");
    printf("6. Zapis/Odczyt z bazy danych\n");
    printf("0. Wyjdz z programu\n");
    scanf(" %d", &program);

    switch (program) {
        case 1:
            Implant new_product = get_user_input();

            if (validate_implant_rules(new_product) == 1) {
                append_node(&head,new_product);
            }
            else {
                printf("Blad przy rejestracji.\n");
            }
            break;
        case 2:

            break;
        case 3:

            break;
        case 4:

            break;
        case 5:

            break;
        case 6:

            break;
        case 0:
            return 0;
        default:
            printf("Podaj poprawny numer programu!");
    }
}

void get_implant_data() {

}

void print_table() {

}