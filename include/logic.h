#ifndef PROJEKT_KONCOWY_PP_LOGIC_H
#define PROJEKT_KONCOWY_PP_LOGIC_H

int validate_implant_rules(Implant data);
void find_implant(Node** head_ref,char* search);
stats count_illegal(Node** head_ref);
void try_delete_implant(Node** head_ref,char* try_to_delete);

#endif //PROJEKT_KONCOWY_PP_LOGIC_H