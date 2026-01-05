#ifndef PROJEKT_KONCOWY_PP_LIST_MANAGER_H
#define PROJEKT_KONCOWY_PP_LIST_MANAGER_H
#include "implant_def.h"

Node* create_node(Implant data);
void append_node(Node** head_ref, Implant data);
void delete_node(Node** head_ref, char* id_to_delete);
void free_list(Node** head_ref);
void sort_list(Node** head_ref, int cryteria);
void edit_implant_data(Node** head_ref,char* search_data);

#endif //PROJEKT_KONCOWY_PP_LIST_MANAGER_H