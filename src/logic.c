#include "list_manager.h"
#include "implant_def.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int validate_implant_rules(Implant data) {

    if (data.risk < 0 || data.risk > 10) {
        return 0;
    }

    if (data.energy > 85.0 && data.status == LEGAL) {
        printf("Moc energi zbyt duza, zmienianie statusu\n");
        return 0;
    }
    return 1;
}

void validate_number(char y) {
    int found=0;

    do {
        for (int i = 0; i < y;i++) {
            if (isdigit(y)) {
                found=1;
            }
        }

    }while (!found);
}

void validate_string(char* x) {
    int found = 0;

    do {
        for (int i = 0; i < strlen(x); ++i) {
            if (isalpha(x[i])) {
                found = 1;

            }
        }
    }while(!found);
}

void validate_implant(Node** head_ref) {
    Node* current = *head_ref;

}

void find_implant() {

}

void count_illegal() {

}

void try_delete_implant() {

}