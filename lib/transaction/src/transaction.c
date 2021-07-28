/* -------------------------------------------------------------------
 Gestione delle transazioni dalla creazione 
 all'aggiunta della transazione
----------------------------------------------------------------------- */ 

#include "transaction.h"

// Dichiarazione variabili: 
int count = 0; 
int *count_pointer;

// Funzione creazione di una nuova transazione 

struct trans *new_trans(public_key_sender, public_key_receiver, amount_transaction, ){
    struct  trans = malloc(sizeof(struct trans)); 
    new_trans -> sender = public_key_sender;            // inserimento della chiave pubblica del mittente 
    new_trans -> receiver = public_key_receiver;        // inserimenro della chiave pubblica del ricevente 
    new_trans -> amount = amount_transaction;           // inserimento 

    return new_trans;
}

bool add_trans(trans *head, trans *new_node){

}
