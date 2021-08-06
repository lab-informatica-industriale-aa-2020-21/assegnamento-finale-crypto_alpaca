/* -------------------------------------------------------------------
 Gestione delle transazioni dalla creazione all'aggiunta della transazione
----------------------------------------------------------------------- */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "transaction.h"

/* Funzione: new_trans
 *---------------------------------------------------------------------------------------------
 * crea la struttura di una nuova transazione: inserisce nei campi della struttura 
 * 'trans' mittente, destinatario e importo della transazione.
 *---------------------------------------------------------------------------------------------
 * public_key_sender: variabile int32_t che contiene la chiave pubblica del mittente; 
 * public_key_receiver: variabile int32_t che contiene la chiave pubblica del destinataio;
 * amount_transaction: variabile uint32_t contente l'importo della transazione;
 * count_trans: variabile int che contiene il numero di transazioni create;
 * tmp_transaction: variabile trans che contiene i campi della transazione; 
 * 
 * return: ritorna una transazione con i relativi campi inseriti;
*/
trans *new_trans(const int32_t public_key_sender, const int32_t public_key_receiver, const int32_t amount_transaction, trans *const head_trans)
{  
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
    tmp_trans -> sender = public_key_sender;            // inserimento della chiave pubblica del mittente 
    tmp_trans -> receiver = public_key_receiver;        // inserimenro della chiave pubblica del ricevente 
    tmp_trans -> amount = amount_transaction;           // inserimento dell'importo da trasferire nella transazione
    tmp_trans -> next_trans = NULL;                           // puntatore al successivo della lista 
    // incremento del contatore che tiene traccia del numero di transazioni che vengono create:
    

    return tmp_trans;
}