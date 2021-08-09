#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>

#define MAX_VALID_FIRST_HASH_ELEMENT 0x0FFFFFFF
#define TIMEINFO_STR_LEN 20                             // definizione della lunghezza della stringa per le info temporali di creazione del blocco
#define DATA_TRANS 3                                    // dati per ogni transazione -> sender, receiver, amount
#define BIT_PER_TRANS (DATA_TRANS * HEX_NUMB_LENGTH)


struct Trans
{
    struct Trans *next_trans;       // puntatore alla transazione successiva
    uint32_t sender;                // chiave pubblica del mittente 
    uint32_t receiver;              // chiave pubblica del destinatario
    uint32_t amount;                // importo della transazione
    uint32_t count_trans;           // conteggio del numero di transazioni
};
typedef struct Trans trans;

struct Block
{
    struct Block *next_block;       // puntatore al blocco successivo
    struct Trans *first_trans;      // puntatore alla prima transazione della lista per lettura 
    struct Trans *head_trans;       // puntatore alla transazione più recente della lista per scrittura
    uint32_t count_block;           // conteggio del numero di blocchi di una chain
    uint32_t *prev_hash;            // puntatore a 'hash' del blocco precedente
    uint32_t hash[8];               // 'hash' del blocco corrente
    uint32_t nonce;                 // numero di nonce dell blocco
    uint32_t num_trans;             // numero di transazioni nel blocco
    time_t creation_time;           // tempo per la creazione del blocco
};
typedef struct Block block;

struct Chain
{ 
    struct Chain *next_chain;       // puntatore alla chain successiva
    struct Block *first_block;      // primo blocco di una chain
    struct Block *head_block;       // blocco più recente di una chain
    uint32_t num_block;             // numero di blocchi inseriti in una chain 
    uint32_t count_chain;           // conteggio del numero di chain 
};
typedef struct Chain chain;

//definizione funzioni

trans *new_trans(const int32_t sender, const int32_t receiver, const int32_t amount, trans *const head_trans);

chain *new_chain(chain *const head_chain);

block *new_block(block *const head_block);

bool get_str_creation_time(time_t creation_time, char *string);

void input_trans(uint32_t sender, uint32_t receiver, uint32_t amount, chain *in_chain);

void mine(chain *const chain_to_mine);

void free_chain(chain *chain);

#endif
