#include "stdio.h"
#include "stdlib.h"
#include "ctype.h"
#include "implant_def.h"
#include "list_manager.h"
#include "string.h"
#include "time.h"

int main() {
    Node* head = NULL;
    Implant i1 = {"Oko","CyberDyne",5,100,LEGAL,"Janusz"};

    append_node(&head, i1);
}
