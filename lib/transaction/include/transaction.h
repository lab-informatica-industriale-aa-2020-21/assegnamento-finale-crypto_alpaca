/* ------------------------------------------------------------------------------
* Di seguito viene riportato l'header file per la gestione della transazione
---------------------------------------------------------------------------------*/

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stdbool.h>
#include <stdint.h>

#include "block.h"

// Definizione della struttura della transazione: 
typedef struct trans
{
    struct trans *next_trans;       // puntatore alla transazione successiva
    uint32_t sender;                // chiave pubblica del mittente 
    uint32_t receiver;              // chiave pubblica del destinatario
    uint32_t amount;                // importo della transazione
    uint32_t count_trans;           // conteggio del numero di transazioni
} trans;


// Funzioni utili per la gestione delle transazioni:

// Creazione di una nuova transazione
trans *new_trans(const int32_t public_key_sender, const int32_t public_key_receiver, const int32_t amount_transaction, block *const head_trans);

// Aggiunta transazione alla lista di transazioni 
void add_trans(const uint32_t sender,const uint32_t receiver, const uint32_t amount, trans *head_trans);

#endif 
