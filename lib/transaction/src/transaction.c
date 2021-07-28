/* -------------------------------------------------------------------
 Gestione delle transazioni dalla creazione 
 all'aggiunta della transazione
----------------------------------------------------------------------- */ 

#include "transaction.h"

// Dichiarazione variabili: 
int count = 0;
trans *head = NULL;

// Funzione per la creazione di una nuova transazione: 

trans *new_trans(int32_t public_key_sender, int32_t public_key_receiver, int32_t amount_transaction, int &count ){
    trans *tmp_transaction;
    tmp_transaction = malloc(sizeof(trans));

    // Controllo funzioanmento malloc():
    if(tmp_transaction == NULL){
        printf("Error: malloc() failed");
        exit(EXIT_FAILURE)
    } 

    // Inserimento dati della transazione:
    tmp_transaction -> sender = public_key_sender;            // inserimento della chiave pubblica del mittente 
    tmp_transaction -> receiver = public_key_receiver;        // inserimenro della chiave pubblica del ricevente 
    tmp_transaction -> amount = amount_transaction;           // inserimento dell'importo da trasferire nella transazione
    tmp_transaction -> next = NULL;

    *count ++;

    return tmp_transaction;
}

/* Creazione della lista di transazioni:
    questa funzione aggiunge le nuove transazioni alla lista delle transazioni  */
void add_trans(const uint32_t sender,const uint32_t receiver, const uint32_t amount, trans *head, int &count);{
    trans *old_head = head;
    head = new_trans(int32_t public_key_sender, int32_t public_key_receiver, int32_t amount_transaction, int &count );
    old_head -> next = head;
}

// Funzione che ritorna il numero delle transazioni che sono state create:
uint get_count_trans(){
    return count; 
}