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
    char input_choice, end_choice;
    chain *chain_1 = new_chain(NULL);

    /*------------------------------------------------------------------------------
    *
    * Introduzione al programma implementato e messaggio di benvenuto
    * Interfacciamento con l'utente
    *
    *--------------------------------------------------------------------------------*/ 
    printf("\n\nBenvenuto! \n"
           "Questo programma simula l'algoritmo di gestione di una blockchain"
           "Sei pronto a scoprirlo? Premi un tasto per continuare...  :)\n");
        
    getchar(); // attesa di un input da tastiera per continuare l'esecuzione del programma

    do{
        printf("\n\nE' possibile creare le transazioni oppure fare in modo che il programma le crei in automatico.\n"
           "Inserisci:\n"
           "1 -> transazione manuale\n"
           "0 -> transazione automatica\n");

        scanf("%u", &work_type); // lettura scelta di modalità di lavoro 
        
        if(work_type != 0 && work_type != 1){
            printf("\n\nIl valore inserito non è valido!\n"
                    " Inserisci '0' o '1'");
        }
    }
    while(work_type != 0 && work_type != 1);

    insert_trans: // etichetta per tornare alla creazione delle transazioni
    
    if(work_type){
        // MANUAL MODE
        printf("\nSi è scelta la modalità di inserimento manuale");
           
        do{
            manual_trans(chain_1); // richiamo funzione per l'inserimento manuale delle transazioni
            printf("\nVuoi aggiungere un'altra transazone? (Y/y/N/n)");
            scanf("%c", &input_choice);

            // Controllo inserimento caratteri corretti 
            if(input_choice != 'Y' && input_choice != 'y' && input_choice != 'N' && input_choice != 'n'){
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
        // ATOMATIC MODE
        printf("\nSi è scelta la modalità di inserimento automatica");
        printf("\n Quante transazioni si volgiono generare?"); // Richiesta numero di transazioni che si vogliono generare
        scanf("%u", & num_trans_to_generate);

        // Controllo che il numero di transazioni che si vuole creare sia valido 
        while(num_trans_to_generate <= 0){
            printf("\nIl numero inserito non è valido!"
                    "Si inserisca un valore maggiore di 0");
            printf("\n Quante transazioni si volgiono generare?");
            scanf("%u", &num_trans_to_generate);
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
       while (getchar()!='\n'){};
        printf("\nSi vuole terminare qui in programma?\n"
            "Si inserisca:\n"
            "q -> USCITA/EXIT\n"
            "c -> Continue\n");
        scanf("%c", &end_choice);
        // Controllo inserimento carattere corretto per l'uscita o la comtinuazione del programma
        if (end_choice != 'q' && end_choice != 'Q' && end_choice != 'c' && end_choice != 'C'){
            printf("\n\nInserisci un carattere valido tra quelli elencati");
        }
   } while (end_choice != 'q' && end_choice != 'Q' && end_choice == 'c' && end_choice == 'C');
   
    
    if(end_choice == 'q' || end_choice == 'Q'){ // scelta di terminare
        save_chain(chain_1, BLOCKCHAIN_TXT);
        free_chain(chain_1);
        printf("\n\nIl programma termina qui!");
        return 0; // chiusura dell'esecuzione del programma 
    }
    else if (end_choice == 'c' || end_choice == 'C'){ // scelta di continuare
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
    while (getchar()!='\n');
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

    for(uint32_t i = 0; i < trans_to_generate; i++){
        
        sender = 4 * rand() * rand(); // assegnazione identificativo casuale al mittente (sender)
        receiver = 4 * rand() * rand(); // assegnazione identificativo casuale al destinatario (receiver)
        amount = 1 + rand() * 100; // assegnazione di importo (amount) causale

        input_trans(sender, receiver, amount, head_chain); // richiamo funzione per la creazione della transazione
        }
}