#include <stdio.h>
#include <stdlib.h>
#include "implant_def.h"
#include <string.h>
#include "logic.h"
#include "ui.h"
//funkcja tworzy nowy wezel (wagon/pojemnik) w liscie
Node* create_node(Implant data) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}
//funkcja dodaje nowy wezel do listy
void append_node(Node** head_ref, Implant data) {
    Node* new_node = create_node(data);
    if (*head_ref == NULL) {
        *head_ref = new_node;
        return;
    }

    Node* current = *head_ref;

    while (current != NULL) {
        if (strcmp(current->data.id, data.id) == 0 && strcmp(current->data.name, data.name) == 0 ) {
            printf("DUPLIKAT");
            free(new_node);
            return;
        }

        if (current->next == NULL) {
            current->next = new_node;
            return;
        }
        current = current->next;
    }
}
//funkcja usuwa wybrany wezel/wezly z listy
void delete_node(Node** head_ref, char* id_to_delete) {
    Node* current = *head_ref;
    Node* previous = NULL;
    Node* temp_next = NULL;

    if (current == NULL) {
        return;
    }

    while (current != NULL) {
        if (strcmp(current->data.id, id_to_delete) == 0 ) {
            //nastepny
            temp_next = current->next;

            if (current->data.status == ILLEGAL) {
                printf("DOWOD W SPRAWIE, NIE MOZNA USUNAC");
                previous = current;
                current = current->next;
            }
            else {
                if (previous == NULL) {
                    //usuniecie glowy przechodzi na nastepny
                    *head_ref = temp_next;
                }
                else {
                    previous->next = temp_next;
                }
                printf("Poprawnie usunieto implant %s",current->data.name);
                free(current);
                current = temp_next;
            }
        }
        else {
            previous = current;
            current = current->next;
        }
    }
}
void delete_node_by_risk(Node** head_ref, int risk_int) {
    Node* current = *head_ref;
    Node* previous = NULL;
    Node* next_node = NULL;
    int deleted_count = 0;

    while (current != NULL) {
        next_node = current->next;

        if (current->data.risk >= risk_int) {
            if (current->data.status == ILLEGAL) {
                printf("Pominieto usuwanie: %s (DOWOD W SPRAWIE)\n", current->data.id);
                previous = current;
                current = next_node;
            }
            else {
                if (previous == NULL) {
                    *head_ref = next_node;
                } else {
                    previous->next = next_node;
                }
                free(current);
                deleted_count++;
                current = next_node;
            }
        }
        else {
            previous = current;
            current = next_node;
        }
    }
    printf("Usunieto %d implant/ow o ryzyku > %d\n", deleted_count, risk_int);
}
//funkcja ktora czysci liste
void free_list(Node** head_ref) {
    Node* current = *head_ref;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}
//funkcja pomocnicza zwraca dlugosc listy
int list_length(Node* head) {
    Node* current = head;
    int length = 0;

    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}
//funkcja ktora sortuje liste wedlug wybranego kryterium
void sort_list(Node** head_ref, int criteria) {
    Node* current = *head_ref;
    int swapped =0;
    int should_swap = 0;

    if (current == NULL || list_length(current) <=1) {
        return;
    }
    do{
        swapped = 0;
        current = *head_ref;
        do {
            switch (criteria) {
                case 1:
                    if (strcmp(current->data.name, current->next->data.name) > 0) {
                        should_swap = 1;
                    }
                    break;
                case 2:
                    if (strcmp(current->data.id, current->next->data.id) > 0) {
                        should_swap = 1;
                    }
                    break;
                case 3:
                    if (current->data.risk > current->next->data.risk) {
                        should_swap = 1;
                    }
                    break;
                }
            if (should_swap == 1) {
                Implant temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = 1;
            }
            current = current->next;
            should_swap = 0;
        }while (current->next != NULL);
    }while (swapped == 1);
}
//funkcja ktora umozliwia edytowanie danych z bazy danych z walidacja
void edit_implant_data(Node** head_ref,char* search_data) {
    Node* current = *head_ref;
    int choice = -1;
    char buffer[128];

    if (current == NULL) {
        return;
    }

    Implant temp;

    while (current != NULL) {
        if (strcmp(current->data.id, search_data) == 0) {
            choice = show_edit_menu();
            temp = current->data;
            switch (choice) {
                case 1: {
                    clear_buffer();
                    printf("Podaj nowe dane:\n");
                    read_line(buffer, 128);
                    strcpy(current->data.id, buffer);
                    break;
                }
                case 2: {
                    clear_buffer();
                    printf("Podaj nowe dane:\n");
                    read_line(buffer, 128);
                    strcpy(current->data.developer, buffer);
                    break;
                }
                case 3: {
                    printf("Podaj nowe dane:\n");
                    while (scanf("%d",&temp.risk) != 1) {
                        printf("Podaj liczbe! Sproboj ponownie:\n");
                        clear_buffer();
                    }
                    clear_buffer();

                    int res = validate_implant_rules(temp);

                    if (res == 1 || res == 2) {
                        current->data.risk = temp.risk;
                    }
                    else {
                        printf("Blad przy zmianie danych.\n");
                    }
                    break;
                }
                case 4: {
                    printf("Podaj nowe dane:\n");
                    while (scanf("%lf",&temp.energy) != 1) {
                        printf("Podaj liczbe! Sproboj ponownie:\n");
                        clear_buffer();
                    }
                    clear_buffer();

                    int res = validate_implant_rules(temp);

                    if (res == 1 || res == 2) {
                        current->data.energy = temp.energy;
                        if (res == 2) {
                            current->data.status = ILLEGAL;
                        }
                    }
                    else {
                        printf("Blad przy zmianie danych.\n");
                    }
                    break;
                }
                default:
                    printf("Wybierz poprawny numer z zakresu 1-4\n");
            }
            return;
        }
        else {
            printf("Nie znaleziono.\n");
        }
        current = current->next;
    }
}