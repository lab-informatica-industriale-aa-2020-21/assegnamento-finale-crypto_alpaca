// Header file per gestione della creazione di una blockchain

#ifndef chain_h
#define chain_h

#include<stdio.h>
#include<stdlib.h>

#include "block.h"
#include "transaction.h"

// Funzione per la creazione di una nuova blockchain:
void add_block(block *last, trans *head);
    
#endif
