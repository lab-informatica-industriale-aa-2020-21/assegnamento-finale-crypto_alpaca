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

#include "blockchain.h"
#include "gui.h"

#define MAX_TRANS_TO_ADD 5000000


void print_menu(chain *chain_to_edit);
void print_manual_menu(chain *chain_to_edit, unsigned int *const trans_counter);
void print_automatic_menu(chain *chain_to_edit, unsigned int *const trans_counter);
void print_exit_warning(chain *chain_to_free, const unsigned int trans_counter);
int print_new_trans_menu(uint32_t *const sender, uint32_t *const receiver, uint32_t *const amount);
void make_random_trans(const int num_trans);


int main(void) {
    chain *chain1 = new_chain(NULL);

    print_menu(chain1);

    return 0;
}


void print_menu(chain *chain_to_edit) {
    unsigned int trans_counter = 0;

    char title[] = "BLOCKCHAIN DEMO";
    const int num_items = 2;
    int choice;
    char selections[MAX_ITEMS][MAX_STR_LEN + 1] = {"Inserimento Automatico",
                                                   "Inserimento Manuale"};
    
    while (1) {
        choice = selection_box(title, num_items, selections, -1, NULL, 0);

        switch (choice) {
            case 0:
                print_automatic_menu(chain_to_edit, &trans_counter);
                break;
            case 1:
                print_manual_menu(chain_to_edit, &trans_counter);
                break;
            case -1:
                print_exit_warning(chain_to_edit, trans_counter);
                break;
            default:
                exit(EXIT_FAILURE);
        }
    }
}


void print_manual_menu(chain *chain_to_edit, unsigned int *const trans_counter) {
    uint32_t sender = 0;
    uint32_t receiver = 0;
    uint32_t amount = 0;

    char subtitle[] = "INSERIMENTO MANUALE";
    const int num_items = 4;
    int choice;
    char selections[MAX_ITEMS][MAX_STR_LEN + 1] = {"Aggiungi una transazione",
                                                   "Mina il blocco",
                                                   "Visualizza il blocco",
                                                   "Torna al menu principale"};

    if (*trans_counter == 0)
        choice = selection_box(subtitle, num_items, selections, -1, NULL, 2, 1, 2);
    else
        choice = selection_box(subtitle, num_items, selections, -1, NULL, 0);

    switch (choice) {
        case 0:
            //Aggiungere transazione
            if (print_new_trans_menu(&sender, &receiver, &amount) == 0)
                (*trans_counter)++;
            break;
        case 1:
            //Minare blocco
            break;
        case 2:
            //Visualizzare blocco
            break;
        case 3:
            //Tornare al menu principale
            break;
        default:
            exit(EXIT_FAILURE);
    }
}

void print_automatic_menu(chain *chain_to_edit, unsigned int *const trans_counter) {
    char subtitle[] = "INSERIMENTO AUTOMATICO";
    int num_items = 5;
    uint32_t n_trans = 0;
    int choice;
    char selections [MAX_ITEMS][MAX_STR_LEN + 1] = {"n. transazioni da aggiungere",
                                                    "Aggiungi le transazioni",
                                                    "Mina il blocco",
                                                    "Visualizza il blocco",
                                                    "Torna al menu principale"};

    while (1) {
        if (*trans_counter == 0)
            choice = selection_box(subtitle, num_items, selections, 0, &n_trans, 2, 2, 3);
        else if (*trans_counter >= MAX_TRANS_TO_ADD)
            choice = selection_box(subtitle, num_items, selections, -1, NULL, 1, 0);
        else
            choice = selection_box(subtitle, num_items, selections, 0, &n_trans, 0);

        switch (choice) {
            case 0:
                break;
            case 1:
                //Aggiungere nova transazione
                make_random_trans(n_trans);
                *trans_counter += (uint32_t) n_trans;
                break;
            case 2:
                //Minare il blocco
                break;
            case 3:
                //Visualizzare il blocco
                break;
            case 4:
                //Tornare al menu principale
                return;
            case -1:
                print_exit_warning(chain_to_edit, *trans_counter);
                break;
            default:
                exit(EXIT_FAILURE);
        }
        n_trans = 0;
    }
}

void print_exit_warning(chain *chain_to_free, const unsigned int trans_counter) {
    if (trans_counter == 0)
        exit(EXIT_SUCCESS);

    char subtitle[MAX_STR_LEN];

    if (trans_counter == 1)
        sprintf(subtitle, "ATTENZIONE! %u TRANSAZIONE NON E' ANCORA STATA MINATA", trans_counter);
    else
        sprintf(subtitle, "ATTENZIONE! %u TRANSAZIONI NON SONO ANCORA STATE MINATE", trans_counter);

    int num_items = 1;
    int choice;
    char selections [MAX_ITEMS][MAX_STR_LEN + 1] = {"Torna al menu precedente per minarle"};

    choice = selection_box(subtitle, num_items, selections, -1, NULL, 0);

    switch (choice) {
        case 0:
            return;
        case -1:
            free(chain_to_free);
            exit(EXIT_SUCCESS);
        default:
            free(chain_to_free);
            exit(EXIT_FAILURE);
    }
}


int print_new_trans_menu(uint32_t *const sender, uint32_t *const receiver, uint32_t *const amount) {
    int choice;

    while (*sender == 0 || *receiver == 0 || *amount == 0) {
        choice = transaction_box("NUOVA TRANSAZIONE", sender, receiver, amount);
        if (choice == -1)
            break;
    }
    return choice;
}


void make_random_trans(const int num_trans) {

}