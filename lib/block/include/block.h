/*  Di seguito viene riportato l'header file per la gestione dei blocchi 
    di transazione da inserire nella blockchain */

// Struttura del blocco di transazioni:

#ifndef BLOCK_H
#define BLOCK_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

#include "transaction.h"
#include "chain.h"
//#include "hash.h"
//#include "format_string.h"

#define MAX_VALID_FIRST_HASH_ELEMENT 0x0FFFFFFF
#define TIMEINFO_STR_LEN 20 // definizione della lunghezza della stringa per le info temporali di creazione del blocco
#define DATA_TRANS 3        // dati per ogni transazione -> sender, receiver, amount
#define BIT_PER_TRANS (DATA_TRANS * HEX_NUMB_LENGTH)

struct Block
{
    struct Block *next_block;        // puntatore al blocco successivo
    struct Trans *first_trans;              // puntatore alla prima transazione della lista per lettura 
    struct Trans *head_trans;               // puntatore alla transazione più recente della lista per scrittura
    uint32_t count_block;            // conteggio del numero di blocchi di una chain
    uint32_t *prev_hash;             // puntatore a 'hash' del blocco precedente
    uint32_t hash[8];                // 'hash' del blocco corrente
    uint32_t nonce;                  // numero di nonce dell blocco
    uint32_t num_trans;               // numero di transazioni nel blocco
    time_t creation_time;            // tempo per la creazione del blocco
};
typedef struct Block block;

// Funzione per la creazione di uno nuovo blocco di transazioni della blockchain:
block *new_block(block *const head_block);

// Mina il nuovo blocco creato, ovvero aggiunge il blocco alla blockchain:
//void mine(chain *const chain_to_mine);

bool get_str_creation_time(time_t creation_time, char *string);
#endif
