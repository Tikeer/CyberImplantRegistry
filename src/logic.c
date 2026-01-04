#include "list_manager.h"
#include "implant_def.h"
#include "ui.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validate_implant_rules(Implant data) {

    if (data.risk < 0 || data.risk > 10) {
        return 0;
    }

    if (data.energy > 85.0 && data.status == LEGAL) {
        data.status = ILLEGAL;
        printf("Moc energi zbyt duza, zmienianie statusu\n");
        return 0;
    }
    return 1;
}

void find_implant(Node** head_ref,char* search) {
    Node* current = *head_ref;
    int found = 0;

    if (current == NULL) {
        return;
    }

    while (current != NULL) {
        //wyszukiwanie po nazwie implantu
        if (strcmp(current->data.name, search) == 0) {
            show_implant_data(current->data);
            found = 1;
        }
        //wyszukiwanie po id
        if (strcmp(current->data.id, search) == 0) {
            show_implant_data(current->data);
            found = 1;
        }
        //wyszukwianie po producencie
        if (strcmp(current->data.developer, search) == 0) {
            show_implant_data(current->data);
            found = 1;
        }
        current = current->next;
    }
    if (found == 0) {
        printf("Nie znaleziono.\n");
    }

}

stats count_illegal(Node** head_ref) {
    Node* current = *head_ref;
    stats s = {0,0,0};

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
    }

    return s;
}

void try_delete_implant(Node** head_ref,char* try_to_delete) {
    Node* current = *head_ref;

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
            }
        }else {
            printf("Nie znaleziono.\n");
        }
    }
}