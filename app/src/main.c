/*  Programma 'main' in cui viene implementato il programma principale di gestione 
    dell'algoritmo di blockchain.
    In questa parte di software vengono richiamate le sottoparti sviluppate (chain, transaction, block, hash).
*/

// Definizione delle librerie utili per il progetto 
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>

#include "blockchain.h"
#include "file_IO.h"

void manual_trans(chain *head_chain);
void automatic_trans(chain *head_chain, uint32_t trans_to_generate);

int main()
{
    // Dichiarazioni e iniziallizazione delle variabili:
    uint32_t work_type = 0;
    uint32_t num_trans_to_generate = 0;
    char input_choice, end_choice = 'a';
    chain *chain_1;

    /*------------------------------------------------------------------------------
    *
    * Introduzione al programma implementato e messaggio di benvenuto
    * Interfacciamento con l'utente
    *
    *--------------------------------------------------------------------------------*/ 
    printf("Benvenuto! \n"
           "Questo programma simula l'algoritmo di gestione di una blockchain"
           "Sei pronto a scoprirlo? Premi un tasto per continuare...  :)");
        
    getchar(); // attesa di un input da tastiera per continuare l'esecuzione del programma

    do{
        printf("\n\nE' possibile creare le transazioni oppure fare in modo che il programma le crei in automatico.\n"
           "Inserisci:\n"
           "0 -> transazione manuale\n"
           "1 -> transazione automatica");

        scanf("%d", &work_type); // lettura scelta di modalità di lavoro 
        
        if(work_type != 0 || work_type != 1){
            printf("\n\nIl valore inserito non è valido!\n"
                    " Inserisci '0' o '1'");
        }
    }
    while(work_type != 0 || work_type != 1);

    insert_trans: // etichetta per tornare alla creazione delle transazioni
    if(work_type){
        // MANUAL MODE
        printf("\nSi è scelta la modalità di inserimento manuale");
        manual_trans(chain_1);
    
        do{
            manual_trans(chain_1); // richiamo funzione per l'inserimento manuale delle transazioni
            printf("\nVuoi aggiungere un'altra transazone? (Y/y/N/n)");
            scanf("%c", &input_choice);

            // Controllo inserimento caratteri corretti 
            if(input_choice != 'Y' || input_choice != 'y' || input_choice != 'N' || input_choice != 'n'){
                printf("\nL'inserimento non è valido. \n Inserisci uno tra i caratteri indicati");
                printf("\nVuoi aggiungere un'altra transazone? (Y/y/N/n)");
                scanf("%c", &input_choice);
            }
            // Controllo di conclusione di inserimento delle transazioni 
            else if(input_choice == 'N' || input_choice == 'n'){
                printf("L'inserimento delle transazioni è terminato!\n"
                        "Ora il programma precede alla creazione e all'inserimento in un blocco e"
                        "infine a svolgere l'operazione di mining di quest'ultimo .");
            }
        }
        while(input_choice == 'y' || input_choice == 'Y');
    }
    else{
        // AUTOMATIC MODE
        printf("\nSi è scelta la modalità di inserimento manuale");
        printf("\n Quante transazioni si volgiono generare?"); // Richiesta numero di transazioni che si vogliono generare
        scanf("%d", & num_trans_to_generate);

        // Controllo che il numero di transazioni che si vuole creare sia valido 
        while(num_trans_to_generate <= 0){
            printf("\nIl numero inserito non è valido!"
                    "Si inserisca un valore maggiore di 0");
            printf("\n Quante transazioni si volgiono generare?");
            scanf("%d", &num_trans_to_generate);
        }

        // Richiamo della funzione per la creazione automatica delle transazioni
        automatic_trans(chain_1, num_trans_to_generate);
    }
    
    /*------------------------------------------------------------------------------
    *  Finita la creazione delle transazioni , esse vengono aggiunte in un blocco.
    *  Successivamente questo blocco dovrà essere minato per poter essere 
    *  aggiunto alla blockchain;
    *-------------------------------------------------------------------------------
    */

   mine(chain_1);

   /*-------------------------------------------------------------------------------
   * Se si decide di terminare il programma, inserendo 'q', i dati creati vengono 
   * salvati utilizzando la funzione save_chain(chain). Successivamente viene 
   * deallocata la memoria occupata dalla chain creata richiamando la funzione 
   * free_chain(chain).
   * E' possibile trovare la stampa dei dati nel file BLOCKCHAIN_TXT   
   *--------------------------------------------------------------------------------*/
    // Richiesta scelta se terminare o continuare il programma 
   do
   {
        printf("\nSi vuole terminare qui in programma?"
            "Si inserisca:"
            "q -> USCITA/EXIT"
            "c -> Continue");
        scanf("%c", &end_choice);
        // Controllo inserimento carattere corretto per l'uscita o la comtinuazione del programma
        if (end_choice != 'q' || end_choice != 'Q' || end_choice != 'c' || end_choice != 'C'){
            printf("\n\nInserisci un carattere valido tra quelli elencati");
        }
   } while (end_choice != 'q' || end_choice != 'Q');
   
    
    if(end_choice == 'q' || end_choice == 'Q'){
        save_chain(chain_1, BLOCKCHAIN_TXT);
        free_chain(chain_1);
        printf("\n\nIl programma termina qui!");
        exit(0); // chiusura dell'esecuzione del programma 
    }
    else{
        goto insert_trans; 
    }
}


/*------------------------------------------------------------------------
* Funzione inserimento transazioni manuale
* Vengono generati in modo casuale gli identificativi di mittente (sender) e 
* e ricevente (receiver) e anche dell'importo (amount) della transazione
*-------------------------------------------------------------------------*/ 
void manual_trans(chain *head_chain)
{
    uint32_t sender, receiver, amount;
    
    printf("\n");
    printf("Inserisci i dati richiesti: \n");
    printf("\nSender (formato DEC_INT): ");
    scanf("%u", &sender);
    printf("\nReceiver (formato DEC_INT): ");
    scanf("%u", &receiver);
    printf("\nImporto della transazione (formato DEC_INT): ");
    scanf("%u", &amount);
    input_trans(sender, receiver, amount, head_chain); // richiamo funzione per la creazione della transazione
}


/*------------------------------------------------------------------------
* Funzione inserimento transazioni automatico
* Vengono inseriti in maniera casuale gli identificativi del mittente 
* (sender), destinatario (receiver) e dell'importo della transazioni.
* Successivamente questi dati vengono passati alla funzione che si occupa
* della creazione della transazione
*-------------------------------------------------------------------------*/
void automatic_trans(chain *head_chain, uint32_t trans_to_generate)
{
    uint32_t sender, receiver, amount;

    /*--------------------------------------------------------------------
    * Generazione di un numero random da assegnare come indentificativo  
    * al mittente e al destinatario.
    * Il numero max assegnabile corrisponde a 2^32 = 4.294.967.296
    * Eseguendo 4*rand()*rand() il numero max raggiungibile è 4.294.705.156,
    * ovvero 4 * 32767 * 32767 (max numero raggiungibile in c)
    * L'importo può variare tra 1€ e 3276700€ (32767*100)
    * 
    * rand(): funzione che genera numeri random contenuta nella libreria 
    * standard <stdlib.h>
    *---------------------------------------------------------------------*/

    for(int i = 0; i < trans_to_generate; i++){
        sender = 4 * rand() * rand(); // assegnazione identificativo casuale al mittente (sender)
        // Controllo di sicurezza che il numero non sia maggiore del max valore consentito da uint32_t
        if(sender > 4294967296){ 
            sender = 4 * rand() * rand(); // riassegnazione dell'identificativo
        }

        receiver = 4 * rand() * rand(); // assegnazione identificativo casuale al destinatario (receiver)
        // Controllo di sicurezza che il numero non sia maggiore del max valore consentito da uint32_t
        if(receiver > 4294967296){ 
            sender = 4 * rand() * rand(); // riassegnazione dell'identificativo
        }

        amount = 1 + rand() * 100; // assegnazione di importo (amount) causale

        input_trans(sender, receiver, amount, head_chain); // richiamo funzione per la creazione della transazione
        }
}