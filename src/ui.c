#include <stdlib.h>
#include <stdio.h>
#include "implant_def.h"
#include "list_manager.h"
#include "logic.h"

const char* status_string(ImplantStatus status) {
    switch (status) {
        case LEGAL: return "LEGAL";
        case GRAY_AREA: return "GRAY AREA";
        case ILLEGAL: return "ILLEGAL";
    }
}

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
            temp.status = (ImplantStatus)(x - 1);
            break;
        case 2:
            temp.status = (ImplantStatus)(x - 1);
            break;
        case 3:
            temp.status = (ImplantStatus)(x - 1);
            break;
        default:
            printf("Podaj liczbe z zakresu 1-3:\n");
    }

    return temp;
}

int print_menu(Node** head_ref) {
    Node* current = *head_ref;
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
                append_node(&current,new_product);
            }
            else {
                printf("Blad przy rejestracji.\n");
            }
            break;
        case 2:
            char search[100];
            printf("Podaj nazwe,ID lub producenta implantu:\n");
            scanf("%s",search);
            printf("\n");

            find_implant(head_ref,search);
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

void show_implant_data(Implant data) {

    printf("DANE IMPLANTU\n");
    printf("Nazwa: %s\n",data.name);
    printf("ID: %s\n", data.id);
    printf("Producent: %s \n",data.developer);
    printf("Ryzyko: %d \n",data.risk);
    printf("Poziom mocy: %.2f \n",data.energy);
    printf("Status: %s \n",status_string(data.status));


}

void print_table() {

}