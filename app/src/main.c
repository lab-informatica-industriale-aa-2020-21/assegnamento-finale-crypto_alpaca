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


#include "blockchain.h"
#include "gui.h"


int main(void) {
    chain *chain1 = new_chain(NULL);
    print_menu(chain1);

    return 0;
}