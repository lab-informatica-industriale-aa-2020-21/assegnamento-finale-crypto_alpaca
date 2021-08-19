/**
 * @mainpage Blockchain Demo
 * Questa è la pagina principale del progetto.
 * 
 * 1. Vengono richiamate le funzioni principali per la gestione della GUI.
 * 2. Vengono richiamate le funzioni per la creazione di una o più blockchain.
 * 
 * @authors Andrea Binotto
 * @authors Filippo Toffano
 * @authors Alberto Trabacchin
 * @authors Emanuele Zanoni
 */

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "gui.h"


void print_main_menu(void);
void print_manual_menu(unsigned int *const trans_counter);
void print_automatic_menu(unsigned int *const trans_counter);
void print_exit_warning(const unsigned int *const trans_counter);


int main(void) {
    print_main_menu();

    return 0;
}


void print_main_menu(void) {
    unsigned int trans_counter = 0;

    char title[] = "BLOCKCHAIN DEMO";
    int num_items = 2;
    int choice;
    char selections[MAX_ITEMS][MAX_STR_LEN + 1] = {"Inserimento Automatico",
                                                   "Inserimento Manuale"};
    
    while (1) {
        choice = selection_box(title, num_items, selections, -1, NULL, 0);

        switch (choice) {
            case 0:
                print_automatic_menu(&trans_counter);
                break;
            case 1:
                print_manual_menu(&trans_counter);
                break;
            case -1:
                print_exit_warning(&trans_counter);
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
}


void print_manual_menu(unsigned int *const trans_counter) {
    char subtitle[] = "INSERIMENTO MANUALE";
    int num_items = 4;
    int choice;
    char selections[MAX_ITEMS][MAX_STR_LEN + 1] = {"Aggiungi una transazione",
                                                   "Mina il blocco",
                                                   "Visualizza il blocco",
                                                   "Torna al menu principale"};

    choice = selection_box(subtitle, num_items, selections, -1, NULL, 0);
}

void print_automatic_menu(unsigned int *const trans_counter) {
    char subtitle[] = "INSERIMENTO AUTOMATICO";
    int num_items = 5;
    uint32_t n_trans = 0;
    int choice;
    char selections [MAX_ITEMS][MAX_STR_LEN + 1] = {"n. transazioni da aggiungere",
                                                    "Aggiungi le transazioni",
                                                    "Mina il blocco",
                                                    "Visualizza il blocco",
                                                    "Torna al menu principale"};

    choice = selection_box(subtitle, num_items, selections, 0, &n_trans, 0);
}

void print_exit_warning(const unsigned int *const trans_counter) {
    if (*trans_counter == 0)
        exit(EXIT_SUCCESS);
        
    char subtitle[] = "ATTENZIONE! ALCUNE TRANSAZIONI NON SONO ANCORA STATE MINATE";
    int num_items = 1;
    int choice;
    char selections [MAX_ITEMS][MAX_STR_LEN + 1] = {"Torna al menu precedente per minarle"};

    choice = selection_box(subtitle, num_items, selections, -1, NULL, 0);
}