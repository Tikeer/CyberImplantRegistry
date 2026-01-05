#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include "implant_def.h"
#include "list_manager.h"

void save_database(char* db_path, Node* node) {
    Node* current = node;
    FILE *f = fopen(db_path,"w");

    if (!f) {
        printf("Blad przy otwieraniu pliku database.txt %s \n", strerror(errno));
        return;
    }

    while (current != NULL) {
        fprintf(f,"%s;%s;%s;%d;%lf;%d \n",
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
        printf("Plik bazy danych nie istnieje lub nie mozna otworzyc. Tworze nowa baze.\n");
        return;
    }

    //wczytywanie max znakow do srednika
    // [^;] skanuj wszystko co nie jest srednikiem
    //String max 100,127,127 ,int,double,int
    while (fscanf(f," %100[^;];%127[^;];%127[^;];%d;%lf;%d",
        temp_name,
        temp_id,
        temp_developer,
        &temp_risk,
        &temp_energy,
        &temp_status ) == 6) {

        Implant new_implant;
        strcpy(new_implant.name, temp_name);
        strcpy(new_implant.id, temp_id);
        strcpy(new_implant.developer, temp_developer);
        new_implant.energy = temp_energy;
        new_implant.risk = temp_risk;
        new_implant.status = (ImplantStatus)temp_status;

        append_node(head_ref, new_implant);
    }

    fclose(f);
}


