#ifndef PROJEKT_KONCOWY_PP_FILE_IO_H
#define PROJEKT_KONCOWY_PP_FILE_IO_H

#include "implant_def.h"

void save_database(char* db_path, Node* node);
void load_database(char* db_path, Node** head_ref);

#endif //PROJEKT_KONCOWY_PP_FILE_IO_H