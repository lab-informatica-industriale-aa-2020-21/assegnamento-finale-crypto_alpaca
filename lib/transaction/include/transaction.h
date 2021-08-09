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
struct Trans
{
    struct Trans *next_trans;       // puntatore alla transazione successiva
    uint32_t sender;                // chiave pubblica del mittente 
    uint32_t receiver;              // chiave pubblica del destinatario
    uint32_t amount;                // importo della transazione
    uint32_t count_trans;           // conteggio del numero di transazioni
};
typedef struct Trans trans;


// Funzioni utili per la gestione delle transazioni:

// Creazione di una nuova transazione
trans *new_trans(const int32_t sender, const int32_t receiver, const int32_t amount, trans *const head_trans);

void input_trans(uint32_t sender, uint32_t receiver, uint32_t amount, chain *const in_chain);

#endif
