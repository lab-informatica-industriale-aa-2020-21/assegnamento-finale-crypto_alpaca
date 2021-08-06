/*  Programma 'main' in cui viene implementato il programma principale di gestione 
    dell'algoritmo di blockchain.
    In questa parte di software vengono richiamate le sottoparti sviluppate (chain, transaction, block, hash).
*/

// Definizione delle librerie utili per il progetto 
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "chain.h"
#include "transaction.h"
#include "block.h"
#include "file_IO.h"


int main()
{
    // Dichiarazioni variabili:
    short work_type;
    trans transaction;
    uint32_t num_of_transaction = 0;
    char input_choice;

    // Introduzione al programma implementato e messaggio di benvenuto 
    printf("Benvenuto! \n"
           "Questo programma simula l'algoritmo di gestione di una blockchain"
           "Sei pronto a scoprirlo? Premi un tasto per continuare... ");
        
    getchar(); // attesa di un input da tastiera per continuare l'esecuzione del programma

    do{
        printf("\n\nE' possibile creare le transazioni oppure fare in modo che il programma le crei in automatico.\n"
           "Inserisci:\n"
           "0 -> transazione manuale\n"
           "1 -> transazione automatica");

        scanf("%d", work_type);
        if(work_type != 0 || work_type != 1){
            printf("\n\nIl valore inserito non è valido!\n"
                    " Inserisci '0' o '1'");
        }
    }
    while(work_type != 0 || work_type != 1);

    if(work_type){
        manual_trans();
    }
    else{
        do{
            num_of_transaction ++; // conteggio del numero di transazioni inserite
            manual_trans(num_of_transaction);
            printf("\nVuoi aggiungere un'altra transazone? (Y/N)")
            scanf("%s", input_choice);
        }
        while(input_choice == 'y');
    }

    printf("L'inserimento delle transazioni è terminato!\n"
           "Ora il programma precede ad inserirle in un blocco a svolgere"
           "l'operazione di mining di quest'ultimo .");
    
    /* Funzione: add_block
    * ----------------------------------------------------------------------------
    * Crea il blocco di transazioni, lo mina e successivamente lo aggiunge
    * alla blockchain.
    * ----------------------------------------------------------------------------
    * 
    * head_block -> puntatore all'ultimo blocco inserito 
    * head_trans -> puntatore alla testa della lista di transazioni (punta 
    * all'ultima transazione inserita)
    * 
    */
    add_block(block *const head_block, const trans *head_trans);

}


// Funzione creazione transazioni manuale 
void manual_trans(num_of_transaction)
{
    uint32_t sender, receiver, amount;
    
    printf("Inserisci i dati richiesti: \n");
    printf("\nSender (formato DEC_INT): ");
    scanf("%d", sender);
    printf("\nReceiver (formato DEC_INT): ");
    scanf("%d", receiver);
    printf("\nImporto della transazione (formato DEC_INT): ");
    scanf("%d", amount);
  //  add_trans(sender, receiver, amount);
}


// Funzione inserimento transazioni automatico
void automatic_trans()
{

}

