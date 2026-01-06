#ifndef PROJEKT_KONCOWY_PP_UI_H
#define PROJEKT_KONCOWY_PP_UI_H

const char* status_string(ImplantStatus status);
Implant get_user_input();
int print_menu(Node** head_ref,char* db_path);
void show_implant_data(Implant data);
int show_edit_menu();
void read_line(char* buffer, int size);
void wait_for_enter();
void print_table(Node* head,stats s);
void clear_buffer();

#endif //PROJEKT_KONCOWY_PP_UI_H