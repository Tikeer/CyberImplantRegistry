#include "list_manager.h"
#include "implant_def.h"
#include "ui.h"
#include <stdio.h>
#include <string.h>
#include <math.h>
//funkcja sprawdzajaca czy wprowadzane dane sa zgodne z ograniczeniami
int validate_implant_rules(Implant data) {

    if (data.risk < 0 || data.risk > 10) {
        return 0;
    }
    if (data.energy <= 0) {
        return 0;
    }

    if (data.energy > 85.0 && data.status == LEGAL) {
        return 2;
    }
    return 1;
}
//funkcja ktora znajduje wybrany implant wedlug wybranego kryterium
void find_implant(Node** head_ref,char* search,int mode) {
    Node* current = *head_ref;
    int found = 0;
    int search_int;
    double search_float;

    if (current == NULL) {
        return;
    }

    switch (mode) {
        case 1://nazwa
            printf("Podaj nazwe:\n");
            read_line(search, 100);
            break;
        case 2://id
            printf("Podaj ID:\n");
            read_line(search, 100);
            break;
        case 3://producent
            printf("Podaj producenta:\n");
            read_line(search, 100);
            break;
        case 4://ryzyko
            printf("Podaj ryzyko:\n");
            while (scanf("%d",&search_int) != 1) {
                printf("Nie liczba! Sproboj ponownie\n");
                clear_buffer();
            }
            clear_buffer();
            break;
        case 5://poziom mocy
            printf("Podaj poziom mocy:\n");
            while (scanf("%lf",&search_float) != 1) {
                printf("Nie liczba! Sproboj ponownie\n");
                clear_buffer();
            }
            clear_buffer();
            break;
        case 6://status
            printf("0 - LEGAL \n");
            printf("1 - GRAY_AREA\n");
            printf("2 - ILLEGAL\n");
            while (scanf("%d",&search_int) != 1) {
                printf("Nie liczba! Sproboj ponownie\n");
                clear_buffer();
            }
            clear_buffer();
            break;
        default:
            printf("Wybierz poprawna opcje\n");
            return;
    }

    int len = strlen(search);

    while (current != NULL) {
        switch (mode) {
            case 1:
                //wyszukiwanie po nazwie implantu
                if (strncmp(current->data.name,search,len) == 0) {
                    show_implant_data(current->data);
                    found = 1;
                }
                break;
            case 2:
                //wyszukiwanie po ID
                if (strncmp(current->data.id,search,len) == 0) {
                    show_implant_data(current->data);
                    found = 1;
                }
                break;
            case 3:
                //wyszukiwanie po producencie
                if (strncmp(current->data.developer,search,len) == 0) {
                    show_implant_data(current->data);
                    found = 1;
                }
                break;
            case 4:
                //wyszukiwanie po ryzyku
                if (current->data.risk == search_int) {
                    show_implant_data(current->data);
                    found = 1;
                }
                break;
            case 5:
                //wyszukiwanie po mocy energii
                if (fabs(current->data.energy - search_float) < 0.01) {
                    show_implant_data(current->data);
                    found = 1;
                }
                break;
            case 6:
                //wyszukiwanie po statusie
                if ((int)current->data.status == search_int) {
                    show_implant_data(current->data);
                    found = 1;
                }
                break;
        }
        current = current->next;
    }
    if (found == 0) {
        printf("Nie znaleziono.\n");
    }

}
//funkcja liczaca ilosc rekordow w bazie danych oraz ilosc poszczegolnych implantow z roznym statusem
stats count_illegal(Node** head_ref) {
    Node* current = *head_ref;
    stats s = {0,0,0,0};

    while (current != NULL) {
        if (current->data.status == LEGAL) {
            s.legal_counter++;
        }
        if (current->data.status == ILLEGAL) {
            s.illegal_counter++;
        }
        if (current->data.status == GRAY_AREA) {
            s.gray_area_counter++;
        }
        current = current->next;
    }
    s.sum = s.sum + s.legal_counter + s.illegal_counter + s.gray_area_counter;
    return s;
}
//funkcja sprawdzajaca czy wybrany implant jest usuwalny
void try_delete_implant(Node** head_ref,char* try_to_delete) {
    Node* current = *head_ref;
    int found = 0;
    if (current == NULL) {
        return;
    }

    while (current != NULL) {
        if (strcmp(current->data.id, try_to_delete) == 0) {
            if (current->data.status == ILLEGAL) {
                printf("NIE MOZNA USUNAC DOWOD W SPRAWIE");
                return;
            }else {
                delete_node(head_ref, try_to_delete);
                found = 1;
                return;
            }
        }
        current = current->next;
    }
    if (found == 0) {
        printf("Nie znaleziono.\n");
    }
}