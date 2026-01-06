#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define SIZE 100
#include "file_io.h"
#include "implant_def.h"
#include "list_manager.h"
#include "logic.h"
#ifdef _WIN32
    #define CLEAR "cls"
#else
    #define CLEAR "clear"
#endif
//funkcja czysci smieci z buffera
void clear_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}
//funkcja wczytuje tekst oraz robi walidacje dlugosci
void read_line(char* buffer, int size) {
    if (fgets(buffer, size, stdin) != NULL) {

        char *newline = strchr(buffer, '\n');

        if (newline) {
            *newline = '\0';
        }
        else {
            clear_buffer();
        }

    }
}
//funkcja do lepszej iwdocznosci programu
void wait_for_enter() {
    printf("\nNacisnij enter aby kontynuowac");
    getchar();
}
//funkcja zamienia enum na tekst
const char* status_string(ImplantStatus status) {
    switch (status) {
        case LEGAL: return "LEGAL";
        case GRAY_AREA: return "GRAY AREA";
        case ILLEGAL: return "ILLEGAL";
        default: return "ERROR";
    }
}
//funkcja wyswietla menu do usuwania danych
int show_delete_criteria_menu() {
    int program;
    int wybor;
    printf("Podaj jak chcesz usunac:\n");
    printf("1.Za pomoca ID\n");
    printf("2.Po ryzyku > X (masowo)\n");

    do {
        program = scanf(" %d", &wybor);
        if (program != 1) {
            while (getchar() != '\n');
            printf("To nie jest liczba! Sproboj ponownie\n");
            continue;
        }
        if (wybor < 1 || wybor > 2) {
            printf("Podaj liczbe z zakresu 1-2\n");
        }
    }while (program != 1 || wybor < 1 || wybor > 2);

    return wybor;
}
//funkcja wyswietla menu sortujace
int show_criteria_menu() {
    int program;
    int wybor;
    printf("Jak chcesz posortowac dane?\n");
    printf("1. Nazwa\n");
    printf("2. ID\n");
    printf("3. Ryzyko\n");

    do {
        program = scanf(" %d", &wybor);
        if (program != 1) {
            while (getchar() != '\n');
            printf("To nie jest liczba! Sproboj ponownie\n");
            continue;
        }
        if (wybor < 1 || wybor > 3) {
            printf("Podaj liczbe z zakresu 1-3\n");
        }
    }while (program != 1 || wybor < 1 || wybor > 3);

    return wybor;
}
//funkcja wyswietla menu wyszukiwania
int show_search_menu() {
    int program;
    int wybor;
    printf("Podaj po czym chceszz wyszukac:\n");
    printf("1.Nazwa\n");
    printf("2.ID\n");
    printf("3.Producent\n");
    printf("4.Ryzyko\n");
    printf("5.Poziom mocy\n");
    printf("6.Status\n");


    do {
        program = scanf(" %d", &wybor);
        if (program != 1) {
            while (getchar() != '\n');
            printf("To nie jest liczba! Sproboj ponownie\n");
            continue;
        }
        if (wybor < 1 || wybor > 6) {
            printf("Podaj liczbe z zakresu 1-6\n");
        }
    }while (program != 1 || wybor < 1 || wybor > 6);

    return wybor;
}
//funkcja pobiera dane od uzytkownika
Implant get_user_input() {
    Implant temp;
    int x = -1;

    clear_buffer();

    printf("Podaj nazwe implantu:\n");
    read_line(temp.name,SIZE);
    printf("\n");

    printf("Podaj nazwe producenta:\n");
    read_line(temp.developer,SIZE);
    printf("\n");

    printf("Podaj ID wlasciciela:\n");
    read_line(temp.id,SIZE);
    printf("\n");

    printf("Podaj ryzyko implantu:\n");
    while (scanf("%d",&temp.risk) != 1){
        printf("To nie liczba! Sproboj ponownie!\n");
        clear_buffer();
    }
    clear_buffer();
    printf("\n");

    printf("Podaj poziom mocy energi:\n");
    while (scanf("%lf",&temp.energy) != 1) {
        printf("To nie liczba! Sproboj ponownie!\n");
        clear_buffer();
    }
    clear_buffer();
    printf("\n");

    printf("Wybierz status implantu: \n");
    printf("1. LEGAL 2.GRAY_AREA 3.ILLEGAL\n");

    while(scanf(" %d", &x) != 1) {
        printf("To nie liczba! Sproboj ponownie!\n");
        clear_buffer();
    }
    clear_buffer();

    if (x >= 1 && x <= 3) {
        temp.status = (ImplantStatus)(x - 1);
    } else {
        printf("Błąd: Podaj liczbę z zakresu 1-3.\n");
        temp.status = ILLEGAL;
    }

    return temp;
}
//funkcja wypisuje dane w formie tabeli
void print_table(Node* head,stats s) {

    if (head == NULL) {
        printf("Baza danych jest pusta\n");
    }

    printf("\n%-20s || %-15s || %-15s || %-5s || %-8s || %-10s\n",
           "Nazwa", "ID", "Producent", "Ryzyko", "Poziom mocy", "Status");

    while (head != NULL) {
        printf("%-20s || %-15s || %-15s || %-5d || %-8.2f || %-10s\n",
            head->data.name,
            head->data.id,
            head->data.developer,
            head->data.risk,
            head->data.energy,
            status_string(head->data.status));
        head = head->next;
    }

    printf("\nSTATYSTYKI\n");
    printf("Znaleziono: %d rekordow w tym:\n",s.sum);
    printf("%d legalnych implantow\n",s.legal_counter);
    printf("%d implantow z szarej strefy\n",s.gray_area_counter);
    printf("%d nielegalnych implantow\n",s.illegal_counter);
}
//funkcja wyswietlajaca menu
int print_menu(Node** head_ref,char* db_path) {
    int program = -1;
    char buffer[128];

    system(CLEAR);
    printf("Witaj w Neonowej Warszawie gdzie ulice nigdy nie spia\n");
    printf("Oto Centralny Rejestr Cybernetycznych Modyfikacji \n");
    printf("Wybierz co chcesz zrobic: \n");
    printf("1. Rejestracja implantu\n");
    printf("2. Wyszukiwanie danych o implantach\n");
    printf("3. Modyfikowanie danych o implantach\n");
    printf("4. Sortowanie danych\n");
    printf("5. Usuwanie danych\n");
    printf("6. Zapis do bazy danych\n");
    printf("7. Wyswietlenie tabelki z danymi\n");
    printf("0. Wyjdz z programu\n");

    if (scanf(" %d", &program) != 1) {
        while (getchar() != '\n');
        program = -1;
    }

    switch (program) {
        case 1: {
            Implant new_product = get_user_input();
            int wynik = validate_implant_rules(new_product);
            if (wynik == 1) {
                append_node(head_ref,new_product);
            }
            else if (wynik == 2) {
                new_product.status = ILLEGAL;
                printf("Poziom mocy jest zbyt duzy, zmienianie statusu\n");
                append_node(head_ref,new_product);
            }
            else {
                printf("Blad przy rejestracji.\n");
            }
            clear_buffer();
            wait_for_enter();
            break;
        }
        case 2: {
            char search[100];


            int choice = show_search_menu();
            if (choice >= 1 && choice <= 3) {
                clear_buffer();
            }
            find_implant(head_ref,search,choice);

            wait_for_enter();
            break;
        }
        case 3: {
            clear_buffer();

            printf("Podaj ID do zmodyfikowania danych:\n");
            read_line(buffer, SIZE);

            edit_implant_data(head_ref,buffer);

            clear_buffer();
            wait_for_enter();
            break;
        }
        case 4: {
            int choice;
            stats s = count_illegal(head_ref);
            choice = show_criteria_menu();
            sort_list(head_ref,choice);

            print_table(*head_ref,s);

            clear_buffer();
            wait_for_enter();
            break;
        }
        case 5: {
            int choice = show_delete_criteria_menu();

            if (choice == 1) {
                clear_buffer();
                printf("Podaj dane do usuniecia:\n");
                read_line(buffer, SIZE);
                try_delete_implant(head_ref,buffer);
            }
            else {
                int risk;
                printf("Podaj prog ryzyka:\n");
                while (scanf("%d",&risk) != 1) {
                    clear_buffer();
                    printf("Podaj liczbe! Sproboj ponownie\n");
                }
                clear_buffer();
                delete_node_by_risk(head_ref,risk);
            }
            clear_buffer();
            wait_for_enter();
            break;
        }
        case 6:
            save_database(db_path,*head_ref);
            printf("Dane zostaly zapisane w: %s \n",db_path);

            clear_buffer();
            wait_for_enter();
            break;
        case 7: {
            stats st = count_illegal(head_ref);

            print_table(*head_ref,st);

            clear_buffer();
            wait_for_enter();
            break;
        }
        case 0:
            save_database(db_path,*head_ref);
            return 0;
        default:
            printf("Podaj poprawny numer programu!\n\n");
            clear_buffer();
            wait_for_enter();
    }
    return 1;
}
//funkcja wyswietla informacje o implancie
void show_implant_data(Implant data) {

    printf("DANE IMPLANTU\n");
    printf("Nazwa: %s\n",data.name);
    printf("ID: %s\n", data.id);
    printf("Producent: %s \n",data.developer);
    printf("Ryzyko: %d \n",data.risk);
    printf("Poziom mocy: %.2f \n",data.energy);
    printf("Status: %s \n\n",status_string(data.status));


}
//funkcja wyswietla menu do edytowania danych
int show_edit_menu() {
    int program;
    int wybor;
    printf("Wybierz ktore pole chcesz zmodyfikowac:\n");
    printf("1. ID\n");
    printf("2. Producent\n");
    printf("3. Ryzyko\n");
    printf("4. Poziom mocy\n");

    do {
        program = scanf(" %d", &wybor);
        if (program != 1) {
            while (getchar() != '\n');
            printf("To nie jest liczba! Sproboj ponownie\n");
            continue;
        }
        if (wybor < 1 || wybor > 4) {
            printf("Podaj liczbe z zakresu 1-4\n");
        }
    }while (program != 1 || wybor < 1 || wybor > 4);

    return wybor;
}