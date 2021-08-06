/* ------------------------------------------------------------------------------
* Di seguito viene riportato l'header file per la gestione della transazione
---------------------------------------------------------------------------------*/

#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#include "block.h"
#include "chain.h"


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
struct trans *new_trans(const int32_t sender, const int32_t receiver, const int32_t amount, struct trans *const head_trans);

void input_trans(uint32_t sender, uint32_t receiver, uint32_t amount, struct chain *const in_chain);

#endif
