/* -------------------------------------------------------------------
 Gestione delle transazioni dalla creazione all'aggiunta della transazione
----------------------------------------------------------------------- */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "transaction.h"
#include "block.h"
#include "chain.h"

/* Funzione: new_trans
 *---------------------------------------------------------------------------------------------
 * crea la struttura di una nuova transazione: inserisce nei campi della struttura 
 * 'trans' mittente, destinatario e importo della transazione.
 *---------------------------------------------------------------------------------------------
 * sender: variabile int32_t che contiene la chiave pubblica del mittente; 
 * receiver: variabile int32_t che contiene la chiave pubblica del destinataio;
 * amount: variabile uint32_t contente l'importo della transazione;
 * count_trans: variabile int che contiene il numero di transazioni create;
 * tmp_transaction: variabile trans che contiene i campi della transazione; 
 * 
 * return: ritorna una transazione con i relativi campi inseriti;
*/
trans *new_trans(const int32_t sender, const int32_t receiver, const int32_t amount, trans *const head_trans){  
    trans *tmp_trans = malloc(sizeof(trans));    // allocazione di memoria per una transazione

    // Controllo funzioanmento corretto di malloc():
    if(tmp_trans == NULL){
        printf("Error: malloc() failed");
        exit(EXIT_FAILURE);
    } 

    // Controllo prima transazione inserita
    if(tmp_trans == NULL){
        tmp_trans -> count_trans = 0;
    }
    // transazioni successive alla prima 
    else{
        tmp_trans -> count_trans = head_trans -> count_trans +1;
        head_trans -> next_trans = tmp_trans;
    }
    
    // Inserimento dati della transazione:
    tmp_trans -> sender = sender;            // inserimento della chiave pubblica del mittente 
    tmp_trans -> receiver = receiver;        // inserimenro della chiave pubblica del ricevente 
    tmp_trans -> amount = amount;           // inserimento dell'importo da trasferire nella transazione
    tmp_trans -> next_trans = NULL;                           // puntatore al successivo della lista 
    // incremento del contatore che tiene traccia del numero di transazioni che vengono create:
    

    return tmp_trans;
}



void input_trans(uint32_t sender, uint32_t receiver, uint32_t amount, chain *in_chain){
    if (in_chain -> first_block == NULL){
        in_chain -> first_block = new_block(NULL);
        in_chain -> head_block = in_chain -> first_block;
    }

    if ((in_chain -> head_block) -> hash [0] <= MAX_VALID_FIRST_HASH_ELEMENT)
        in_chain -> head_block = new_block(in_chain -> head_block);

    (in_chain -> head_block) -> head_trans = new_trans(sender, receiver, amount, (in_chain -> head_block) -> head_trans);
}
