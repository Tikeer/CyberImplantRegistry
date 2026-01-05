#include <stdio.h>
#include <stdlib.h>
#include "implant_def.h"
#include <string.h>
#include "logic.h"
#include "ui.h"

Node* create_node(Implant data) {
    Node* new_node = (Node*)malloc(sizeof(Node));

    if (new_node == NULL) {
        return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

void append_node(Node** head_ref, Implant data) {
    Node* current = *head_ref;
    Node* new_node = create_node(data);

    while (current != NULL) {
        if (strcmp(current->data.id, data.id) == 0 && strcmp(current->data.name, data.name) == 0 ) {
            printf("DUPLIKAT");
            return;
        }
        current = current->next;
    }

    if (new_node == NULL) {
        return;
    }

    if (*head_ref == NULL) {
        *head_ref = new_node;
    }else {
        current = *head_ref;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void delete_node(Node** head_ref, char* id_to_delete) {
    Node* current = *head_ref;
    Node* previous = NULL;

    if (current == NULL) {
        return;
    }

    while (current != NULL) {
        if (strcmp(current->data.id, id_to_delete) == 0 ) {

            if (current->data.status == ILLEGAL) {
                printf("DOWOD W SPRAWIE, NIE MOZNA USUNAC");
                return;
            }
            else {
                if (previous == NULL) {
                    *head_ref = current->next;
                    free(current);
                }
                else {
                    previous->next = current->next;
                    free(current);
                }
            }
        }
        previous = current;
        current = current->next;
    }
}

void free_list(Node** head_ref) {
    Node* current = *head_ref;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}
int list_length(Node* head) {
    Node* current = head;
    int length = 0;

    while (current != NULL) {
        length++;
        current = current->next;
    }
    return length;
}
void sort_list(Node** head_ref, int cryteria) {
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
            switch (cryteria) {
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

void edit_implant_data(Node** head_ref,char* search_data) {
    Node* current = *head_ref;
    int program = -1;
    int choice = -1;
    char buffer[128];

    if (current == NULL) {
        return;
    }

    Implant temp;

    while (current != NULL) {
        if (strcmp(current->data.id, search_data) == 0) {
            choice = show_edit_menu(program);
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
                    scanf("%d",&temp.risk);

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
                    scanf("%lf",&temp.energy);

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
        current = current->next;
    }
}