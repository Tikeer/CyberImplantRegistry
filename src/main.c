#include <stdio.h>
#include "implant_def.h"
#include "file_io.h"

#include "ui.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Nie podano zadnych argumentow \n");
        printf("Instrukcja: %s <sciezka_do_bazy_danych>\n", argv[0]);
        return 1;
    }

    char* db_path = argv[1];
    Node* head = NULL;

    load_database(db_path,&head);

    while (1) {
        if (print_menu(&head,db_path) == 0) {
            break;
            }
        }
    return 0;
}
