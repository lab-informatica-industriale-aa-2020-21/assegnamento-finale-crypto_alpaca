/*  Programma 'main' in cui viene implementato il programma principale di gestione 
    dell'algoritmo di blockchain.
    In questa parte di software vengono richiamate le sottoparti sviluppate (chain, transaction, block, hash).
*/

// Definizione delle librerie utili per il progetto 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "blockchain.h"
#include "file_IO.h"
#include "gui.h"

#define EXIT 4
#define MANUAL_MODE 0
#define AUTO_MODE 1

#define ADD_TRANS 0
#define MINE 1
#define SHOW_BLOCK 2
#define RETURN_MAIN_MENU 3

#define YES 1
#define NO 0

#define TRANS_TO_GENERATE 10

// Funzioni modalità di inserimento delle funzioni:
void manual_trans(chain *head_chain);
void automatic_trans(chain *head_chain, uint32_t trans_to_generate);

// Funzioni modalità di funzionamento:
void add_chain_manual(chain *blockchain);
void add_chain_auto(chain *blockchain);
//void end_mode(chain *chain_to_mine);


int main()
{
    /*------------------------------------------------------------------------------
    *
    * Introduzione al programma implementato e messaggio di benvenuto
    * Interfacciamento con l'utente
    *
    *--------------------------------------------------------------------------------*/ 
    // Dichiarazioni e iniziallizazione delle variabili:
    uint8_t input_choice, save = 0;
    chain *chain_1 = new_chain(NULL);
    char selection[MAX_ITEMS][MAX_STR_LEN + 1] = {"SI", "NO"};
    
    while(1){
        input_choice = selection_box(3, "MANUAL", "AUTOMATIC", "EXIT");

        switch (input_choice)
        {
            case MANUAL_MODE:
                add_chain_manual(chain_1);
                break;
            case AUTO_MODE:
                add_chain_auto(chain_1);
                break;
            case EXIT:
                printf("\nAlcune transazioni non sono ancora state minate\n"
                        "Uscire comunque? ");
                save = selection_box(2, selection);
                if(save == YES)
                    save_chain(chain_1, BLOCKCHAIN_TXT);
                else{
                    mine(chain_1);
                    save_chain(chain_1, BLOCKCHAIN_TXT);
                }
                
                free_chain(chain_1);
                exit(EXIT_SUCCESS);
                break;  
        }
    }
}

/*------------------------------------------------------------------------
* Funzione inserimento transazioni manuale
* Vengono generati gli identificativi di mittente (sender) e 
* ricevente (receiver) e anche dell'importo (amount) della transazione
*-------------------------------------------------------------------------*/ 
void add_chain_manual(chain *blockchain){
    // MANUAL MODE
    uint32_t sender, receiver, amount;
    uint8_t input_choice, exit_choice;
    char selection[MAX_ITEMS][MAX_STR_LEN + 1] = {"ADD TRANSACTION", "MINING", "SHOW BLOCCO", "MENU' PRINCIPALE", "EXIT"};
    char selection_2 [MAX_ITEMS][MAX_STR_LEN + 1] = {"SI", "NO"};
    
    input_choice = selection_box(5, selection);
    switch (input_choice)
    {
    case ADD_TRANS: // aggiunta di una transazione
        printf("\nInserisci i dati richiesti: \n");
        printf("\nSender (formato DEC_INT): ");
        scanf("%u", &sender);
        printf("\nReceiver (formato DEC_INT): ");
        scanf("%u", &receiver);
        printf("\nImporto della transazione (formato DEC_INT): ");
        scanf("%u", &amount);
        input_trans(sender, receiver, amount, blockchain); // richiamo funzione per la creazione della transazione
        break;
    case MINE: // si mina il blocca
        mine(blockchain);
        break;
    case SHOW_BLOCK: // si stampa il blocco creato
        save_chain(blockchain, BLOCKCHAIN_TXT);
        break;
    case RETURN_MAIN_MENU:
        break;  
    case EXIT:
        printf("\nSe sicuro di voler uscire dal programma?");
        exit_choice = selection_box(2, selection_2);
        
        if(exit_choice == YES){
            free_chain(blockchain);
            return 0;
        }
        else{
            // torna alla schermata precedente per rifare la selezione
            input_choice = selection_box(4, selection);
        }
        break;
    }
}
    

/*------------------------------------------------------------------------
* Funzione inserimento transazioni automatico
* Vengono inseriti in maniera casuale gli identificativi del mittente 
* (sender), destinatario (receiver) e dell'importo della transazioni.
* Successivamente questi dati vengono passati alla funzione che si occupa
* della creazione della transazione
*-------------------------------------------------------------------------*/
void add_chain_auto(chain *blockchain){
    // AUTOMATIC MODE
    uint32_t sender, receiver, amount;
    uint8_t input_choice;

    char selection[MAX_ITEMS][MAX_STR_LEN + 1] = {"NUM. TRANSACTION", "ADD TRANSACTION", "MINING", "SHOW BLOCK", "MENU' PRINCIPALE", "EXIT"};
    char selection_2 [MAX_ITEMS][MAX_STR_LEN + 1] = {"SI", "NO"};

    input_choice = selection_box(6, selection);
    int exit_choice;

    switch (input_choice)
    {
    case ADD_TRANS:
        /*--------------------------------------------------------------------
        * Generazione di un numero random da assegnare come indentificativo  
        * al mittente e al destinatario.
        * Il numero max assegnabile corrisponde a 2^32 = 4.294.967.296
        * Eseguendo 4*rand()*rand() il numero max raggiungibile è 4.294.705.156,
        * ovvero 4 * 32767 * 32767 (max numero raggiungibile in C)
        * L'importo può variare tra 1€ e 3276700€ (32767*100)
        * 
        * rand(): funzione che genera numeri random contenuta nella libreria 
        * standard <stdlib.h>
        *---------------------------------------------------------------------*/
        for(uint32_t i = 0; i < TRANS_TO_GENERATE; i++){
            sender = 4 * rand() * rand();
            receiver = 4 * rand() * rand();
            amount = 1 + rand() * 100;

            input_trans(sender, receiver, amount, blockchain); 
        }        
        break;
    case MINE:
        mine(blockchain);
        break;
    case SHOW_BLOCK: // si stampa il blocco creato
        save_chain(blockchain, BLOCKCHAIN_TXT);
        break;
    case RETURN_MAIN_MENU:
        break;  
    case EXIT:
        printf("\nSe sicuro di voler uscire dal programma?");
        exit_choice = selection_box(2, selection_2);
        
        if(exit_choice == YES){
            free_chain(blockchain);
            exit(EXIT_SUCCESS);
        }
        else{
            // torna alla schermata precedente per rifare la selezione
            input_choice = selection_box(4, selection);
        }
    }
}
