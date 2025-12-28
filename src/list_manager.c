#include <stdio.h>
#include <stdlib.h>
#include "implant_def.h"

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

