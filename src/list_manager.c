#include <stdio.h>
#include <stdlib.h>
#include "implant_def.h"
#include <string.h>

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

    if (new_node == NULL) {
        return;
    }

    if (*head_ref == NULL) {
        *head_ref = new_node;
    }else {
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_node;
    }
}

void delete_node(Node** head_ref, char* id_to_delete) {
    Node* current = *head_ref;
    Node* previous = NULL;
    /*
     * sprawdzam czy lista nie jest pusta
     * szukam elementu ktory chce usunac przechodzac po liscie
     * porownoje id z istniejacym elementem
     * jesli tak to usuwam wagonik i omijam usuniety wagon i go lacze z nastepnym
     * czyli usuniecie wagonika to po prostu free(x)
     * laczymy po przez przypisanie poprzedniego do obecnego i obecnego do nastepnego
     * i petla przechodzi znowu i sprawdza ze poprzedni nie jest pusty i laczy wagoniki
     */
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
                    return;
                }
                else {
                    previous->next = current->next;
                    current = current->next;
                    free(current);
                    return;
                }
            }
        }
        previous = current;
        current = current->next;
    }
}

Node* free_list(Node** head_ref) {
    Node* current = *head_ref;
    while (current != NULL) {
        Node* next = current->next;
        free(current);
        current = next;
    }
    *head_ref = NULL;
}

void sort_list(Node** head_ref) {

}
