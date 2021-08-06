/*  Di seguito viene riportato l'header file per la gestione dei blocchi 
    di transazione da inserire nella blockchain */

// Struttura del blocco di transazioni:

#ifndef BLOCCO_H
#define BLOCCO_H

#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include <stdint.h>
#include <stdlib.h>

#include "transaction.h"
#include "format_string.h"
#include "chain.h"

#define MAX_VALID_FIRST_HASH_ELEMENT 0x0FFFFFFF
#define TIMEINFO_STR_LEN 20 // definizione della lunghezza della stringa per le info temporali di creazione del blocco
#define DATA_TRANS 3        // dati per ogni transazione -> sender, receiver, amount
#define BIT_PER_TRANS (DATA_TRANS * HEX_NUMB_LENGTH)

struct block
{
    struct block *next_block;        // puntatore al blocco successivo
    struct trans *first_trans;              // puntatore alla prima transazione della lista per lettura 
    struct trans *head_trans;               // puntatore alla transazione più recente della lista per scrittura
    uint32_t count_block;            // conteggio del numero di blocchi di una chain
    uint32_t *prev_hash;             // puntatore a 'hash' del blocco precedente
    uint32_t hash[8];                // 'hash' del blocco corrente
    uint32_t nonce;                  // numero di nonce dell blocco
    uint32_t num_trans;               // numero di transazioni nel blocco
    time_t creation_time;            // tempo per la creazione del blocco
};

// Funzione per la creazione di uno nuovo blocco di transazioni della blockchain:
struct block *new_block(struct block *const head_block);

// Mina il nuovo blocco creato, ovvero aggiunge il blocco alla blockchain:
void mine(struct chain *const chain);

bool get_str_creation_time(time_t creation_time, char *string);
#endif
