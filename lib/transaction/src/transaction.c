/* -------------------------------------------------------------------
 Gestione delle transazioni dalla creazione 
 all'aggiunta della transazione
----------------------------------------------------------------------- */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "transaction.h"


// Dichiarazione variabili: 
int count = 0;
trans *first_trans = NULL;
trans *head_trans = NULL;

// Funzione per la creazione di una nuova transazione: 

trans *new_trans(const int32_t public_key_sender, const int32_t public_key_receiver, const int32_t amount_transaction, int *count ){
    trans *tmp_transaction;                     // definizione di una variabile con struttura 'trans'
    tmp_transaction = malloc(sizeof(trans));    // allocazione di memoria per una transazione

    // Controllo funzioanmento corretto di malloc():
    if(tmp_transaction == NULL){
        printf("Error: malloc() failed");
        exit(EXIT_FAILURE);
    } 

    // Inserimento dati della transazione:
    tmp_transaction -> sender = public_key_sender;            // inserimento della chiave pubblica del mittente 
    tmp_transaction -> receiver = public_key_receiver;        // inserimenro della chiave pubblica del ricevente 
    tmp_transaction -> amount = amount_transaction;           // inserimento dell'importo da trasferire nella transazione
    tmp_transaction -> next = NULL;                           // puntatore al successivo della lista 

    // incremento del contatore che tiene traccia del numero di transazioni che vengono create:
    *count ++;

    return tmp_transaction;
}

/* Creazione della lista di transazioni:
    questa funzione aggiunge le nuove transazioni alla lista delle transazioni  */
void add_trans(const uint32_t sender,const uint32_t receiver, const uint32_t amount, trans *head, int *const count){
    trans *old_head = head_trans;                                         // salvataggio della 'testa' della lista 
    if (head_trans == NULL){
        first_trans = new_trans(sender, receiver, amount, &count);
        head_trans = first_trans;
    }
    else{
        head_trans = new_trans(sender, receiver, amount, &count);        // assegnazione della nuova 'testa' della lista
    }

    old_head -> next = head_trans;                                        // assegnazione del puntatore 'next' della transazione precedente
}

// Funzione che ritorna il numero delle transazioni che sono state create:
uint32_t get_count_trans(){
    return count; 
}

// Funzione che ritorna l'indirizzo della prima transazione della lista:
uint32_t *get_first_trans(){
    return first_trans; 
}
