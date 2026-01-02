#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "implant_def.h"
#include "list_manager.h"

void save_database(char* db_path, Node* node) {
    Node* current = node;
    FILE *f = fopen(db_path,"w");
    int index = 0;

    if (!f) {
        printf("Blad przy otwieraniu pliku database.txt %s \n", strerror(errno));
        return;
    }

    while (current != NULL) {
        index++;
        fprintf(f,"%s %s %s %d %lf %d \n",
            current->data.name,
            current->data.id,
            current->data.developer,
            current->data.risk,
            current->data.energy,
            current->data.status
            );
        current = current->next;
    }


    fclose(f);
}
void load_database(char* db_path, Node** head_ref) {
    FILE *f = fopen(db_path,"r");
    char temp_name[101];
    char temp_id[128];
    char temp_developer[128];
    double temp_energy;
    int temp_risk;
    int temp_status;


    if (!f) {
        printf("Blad przy otwieraniu pliku database.txt %s \n", strerror(errno));
        return;
    }

    while (fscanf(f,"%s %s %s %d %lf %d",
        temp_name,
        temp_id,
        temp_developer,
        &temp_risk,
        &temp_energy,
        &temp_status ) == 6) {

        Implant new;
        strcpy(new.name, temp_name);
        strcpy(new.id, temp_id);
        strcpy(new.developer, temp_developer);
        new.energy = temp_energy;
        new.risk = temp_risk;
        new.status = (ImplantStatus)temp_status;

        append_node(head_ref, new);
    }

    fclose(f);
}


