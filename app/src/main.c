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
#include "trans.h"
#include "block.h"


int main()
{
    // Dichiarazioni variabili:
    short work_type;
    trans transaction;
    uint32_t num_of_transaction;
    char input_choice;

    // Introduzione al programma implementato e messaggio di benvenuto 
    printf("Benvenuto! \n"
           "Questo programma simula l'algoritmo di gestione di una blockchain"
           "Sei pronto a scoprirlo? Premi un tasto per continuare... ");
        
    getchar(); // attesa di un input da tastiera per continuare l'esecuzione del programma

    do{
        printf("\n\nE' pissibile creare le transazioni oppure fare in modo che il programma le crei in automatico.\n"
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
        do{
            automatic_trans(num_of_transaction);
            printf("\nVuoi aggiungere un'altra transazone? (Y/N)")
            scanf("%s", input_choice);
        }
        while(input_choice == 'y');

    }
    else{
        //transaction = manual_trans(transaction);
    }

}



// Funzione creazione transazioni manuale 
void manual_trans(num_of_transaction)
{
    uint32_t sender, receiver, amount;

    printf("Inserisci i dati richiesti: \n");
    printf("\nPublic Key Sender (formato DEC): ");
    scanf("%d", sender);
    printf("\nPublic Key Receiver (formato DEC): ");
    scanf("%d", receiver);
    printf("\nInserisci l'importo della transazione (formato DEC):");
    scanf("%d", amount);
    new_trans(sender, receiver, amount, num);
}

/*
// Funzione inserimento transazioni automatico
trans automatic_trans()
{

}
*/
