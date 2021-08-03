// Header file per gestione della creazione di una blockchain

#ifndef chain_h
#define chain_h

#include<stdio.h>
#include<stdlib.h>

#include "block.h"
#include "transaction.h"

typedef struct chain
{ 
    block *head_block;
    struct chain *index_chain;
}chain;

/*  Funzione per l'aggiunta dei blocchi alla blockchain':
    Viene passata il puntatore alla lista delle transazioni che devono essere inserire nel blocco;
    Viene creato un nuovo blocco richiamando la funzione 'new_block';
    Successivamente il blocco viene minato attraverso l'esecuzione della funzione 'mine';
*/
void add_block(block *head_block, trans *head_trans);

// Funzione per creare una nuova catena della blockchain:
block *new_block(block *const head_block, const trans *head_trans);

#endif
