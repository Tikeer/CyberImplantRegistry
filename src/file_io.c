#include <stdio.h>
#include <c++/v1/cstring>
#include <sys/errno.h>
#include <stdlib.h>
#include "implant_def.h"


void save_file(FILE* file, Node* node) {
    FILE *f = fopen("data/database.txt","wb");
    if (!f) {
        printf("Error opening database.txt %s \n", strerror(errno));
        return;
    }
    fprintf(f,"NEO-WARSAW IMPLANT DATABASE\n");
    fprintf(f,"---------------------------\n\n");



}
Node* load_file(FILE* file) {

}
FILE* open_file(char* name, char* mode) {


    save_file();
    load_file();

    fclose(f);
}

