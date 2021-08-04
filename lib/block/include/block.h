/*  Di seguito viene riportato l'header file per la gestione dei blocchi 
    di transazione da inserire nella blockchain */

// Struttura del blocco di transazioni:

#ifndef BLOCCO_H
#define BLOCCO_H

#include <stdbool.h>
#include <time.h>

#include "transaction.h"

#define MAX_VALID_FIRST_HASH_ELEMENT 0x0FFFFFFF

typedef struct block
{
    uint32_t count_index;
    uint32_t *prev_hash;                    // puntatore a 'hash' del blocco precedente
    uint32_t hash[6];                       // 'hash' del blocco corrente  
    uint32_t nonce;
    struct trans *first_trans;             // puntatore alla prima transazione della lista
    int32_t num_trans;                  // numero di transazioni nel blocco
    time_t creation_time;           // tempo per la creazione del blocco
    block *head_block;
} block;

// Funzione per la creazione di uno nuovo blocco di transazioni della blockchain:
block *new_block(block *const head_block, const trans *head_trans);

// Mina il nuovo blocco creato, ovvero aggiunge il blocco alla blockchain:
void mine(block *const block_to_mine);

bool get_str_creation_time(time_t creation_time, char *string);
#endif
