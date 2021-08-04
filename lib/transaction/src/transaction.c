/* -------------------------------------------------------------------
 Gestione delle transazioni dalla creazione all'aggiunta della transazione
----------------------------------------------------------------------- */ 

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "transaction.h"


// Dichiarazione variabili: 
int count_trans = 0;
trans *first_trans = NULL;      // puntatore alle prima transazione della lista di transazioni 
trans *head_trans = NULL;       // puntatore alla testa delle transazioni, ovvero punta all'ultima transazione inserita nella lista

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
trans *new_trans(const int32_t public_key_sender, const int32_t public_key_receiver, const int32_t amount_transaction, int *count_trans ){
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
    *count_trans ++;

    return tmp_transaction;
}

/* Funzione: add_trans
*--------------------------------------------------------------------------------------------
* Aggiunge la transazione appena creata alla lista di transazioni 
*--------------------------------------------------------------------------------------------
* sender: variabile uint32_t contente l'identificativo del mittente della transazione;
* receiver: variabile uint32_t contente l'identificativo del destinatario della transazione;
* amount: variabile uint32_t contente l'importo della transazione;
* *head: puntatore alla testa delle transazioni;
* *count_trans: puntatore al conteggio del numero di transazioni 
*/
void add_trans(const uint32_t sender,const uint32_t receiver, const uint32_t amount, trans *head, int *const count_trans){
    trans *old_head = head_trans;                                         // salvataggio della 'testa' della lista 
    if (head_trans == NULL){
        first_trans = new_trans(sender, receiver, amount, &count_trans);
        head_trans = first_trans;
    }
    else{
        head_trans = new_trans(sender, receiver, amount, &count_trans);        // assegnazione della nuova 'testa' della lista
    }

    old_head -> next = head_trans;                                        // assegnazione del puntatore 'next' della transazione precedente
}
