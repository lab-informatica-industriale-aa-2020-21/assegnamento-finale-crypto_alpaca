// Header file per gestione della creazione di una blockchain

#ifndef chain_h
#define chain_h

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "block.h"
#include "transaction.h"

typedef struct
{ 
    chain *next_chain;       // puntatore alla chain successiva
    block *first_block;             // primo blocco di una chain
    struct block *head_block;              // blocco più recente di una chain
    uint32_t num_block;             // numero di blocchi inseriti in una chain 
    uint32_t count_chain;           // conteggio del numero di chain 
} chain;

struct chain *new_chain(struct chain *const head_chain);


/*-------------------------------------------------------------------------------------------------  
*   Funzione per deallocazione della memoria di una chain.
*   Una volta completata la sua costruzione, viene salvata all'interno di un file.txt
*   e successivamente viene liberata la memoria utilizzata.
---------------------------------------------------------------------------------------------------*/
void free_chain(struct chain *chain);

#endif
