// Header file per gestione della creazione di una blockchain

#ifndef chain_h
#define chain_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "block.h"
#include "transaction.h"

typedef struct chain
{ 
    struct chain *next_chain;       // puntatore alla chain successiva
    uint32_t count_chain;
    block *first_block;             // primo blocco di una chain
    block *head_block;              // blocco più recente di una chain
    uint32_t num_block;             // numero di blocchi inseriti in una chain 
}chain;

chain *new_chain(chain *head_chain, chain *new_chain);

/*  Funzione per l'aggiunta dei blocchi alla blockchain':
    Viene passata il puntatore alla lista delle transazioni che devono essere inserire nel blocco;
    Viene creato un nuovo blocco richiamando la funzione 'new_block';
    Successivamente il blocco viene minato attraverso l'esecuzione della funzione 'mine';
*/
void add_block(block *const head_block, const trans *head_trans);

// Funzione per creare una nuova catena della blockchain:
block *new_block(block *const head_block, const trans *head_trans);

#endif
