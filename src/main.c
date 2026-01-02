#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "implant_def.h"
#include "list_manager.h"
#include <string.h>
#include <time.h>

int main(int argc, char* argv[]) {
    if (argc < 2) {
        printf("Nie podano zadnych argumentow \n");
        printf("Instrukcja: %s <sciezka_do_pliku>\n", argv[0]);
        return 1;
    }

    char* db_path = argv[1];
}