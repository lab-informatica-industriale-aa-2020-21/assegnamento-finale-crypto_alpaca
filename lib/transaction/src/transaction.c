/* -------------------------------------------------------------------
 Gestione delle transazioni dalla creazione 
 all'aggiunta della transazione
----------------------------------------------------------------------- */ 

#include "transaction.h"

// Dichiarazione variabili: 
int count = 0; 
int *count_pointer;
trans tmp_transaction;

// Funzione creazione di una nuova transazione 

trans *new_trans(int32_t public_key_sender, int32_t public_key_receiver, int32_t amount_transaction, int  ){
   
    trans = malloc(sizeof( trans ));
    // Controllo funzioanmento malloc():
    if(new_trans == NULL){
        printf("Error: malloc() failed");
        exit(EXIT_FAILURE)
    } 

    // Inserimento dati della transazione:
    tmp_transaction -> sender = public_key_sender;            // inserimento della chiave pubblica del mittente 
    tmp_transaction -> receiver = public_key_receiver;        // inserimenro della chiave pubblica del ricevente 
    tmp_transaction -> amount = amount_transaction;           // inserimento dell'importo da trasferire nella transazione

    return new_trans;
}

bool add_trans(trans *head, trans *new_node){

}
