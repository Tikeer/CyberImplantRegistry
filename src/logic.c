#include "list_manager.h"
#include "implant_def.h"
#include "ui.h"
#include <stdio.h>
#include <string.h>

int validate_implant_rules(Implant data) {

    if (data.risk < 0 || data.risk > 10) {
        return 0;
    }

    if (data.energy > 85.0 && data.status == LEGAL) {
        return 2;
    }
    return 1;
}

void find_implant(Node** head_ref,char* search,int mode) {
    Node* current = *head_ref;
    int found = 0;
    int search_int;
    float search_float;

    if (current == NULL) {
        return;
    }

    int len = strlen(search);

    while (current != NULL) {

        switch (mode) {
            case 1: {
                //wyszukiwanie po nazwie implantu
                read_line(search, 100);
                if (strncmp(current->data.name,search,len) == 0) {
                    show_implant_data(current->data);
                    found = 1;
                }
                break;
            }
            case 2: {
                //wyszukiwanie po ID
                read_line(search, 100);
                if (strncmp(current->data.id,search,len) == 0) {
                    show_implant_data(current->data);
                    found = 1;
                }
                break;
            }
            case 3: {
                //wyszukiwanie po producencie
                read_line(search, 100);
                if (strncmp(current->data.developer,search,len) == 0) {
                    show_implant_data(current->data);
                    found = 1;
                }
                break;
            }
            case 4: {
                //wyszukiwanie po ryzyku
                scanf("%d",&search_int);
                if (current->data.risk == search_int) {
                    show_implant_data(current->data);
                    found = 1;
                }
            }
            case 5: {
                //wyszukiwanie po mocy energii
                scanf("%f",&search_float);
                if (current->data.energy == search_float) {
                    show_implant_data(current->data);
                    found = 1;
                }
            }
            case 6: {
                //wyszukiwanie po statusie
                printf("0 - LEGAL");
                printf("1 - GRAY_AREA");
                printf("2 - ILLEGAL");

                scanf("%d",&search_int);
                if (current->data.status == search_int) {
                    show_implant_data(current->data);
                    found = 1;
                }
            }
            default:
                printf("Wybierz poprawna opcje\n");
        }


        current = current->next;
    }
    if (found == 0) {
        printf("Nie znaleziono.\n");
    }

}

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
    s.sum = s.sum + s.legal_counter + s.illegal_counter;
    return s;
}

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