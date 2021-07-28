// File delle funzioni

#include "block.h"

// Dichiarazioni delle variabili:
int count_index = 0;
block *last = NULL;

// Funzione per la creazione di uno nuovo blocco di transazioni della blockchain:
block *new_block(block *last, trans *head){

    block *tmp_block;
    tmp_block = malloc(sizeof(block));

    if(tmp_block == NULL){
        printf("Error: malloc() failure");
        exit(EXIT_FAILURE);
    }

    tmp_block -> prev_hash = last -> hash;
    tmp_block -> last = tmp_block; 
    tmp_block -> nonce = 0;
    // hash = (richiamo funzione di calcolo dell'hash)    //assegnazione hash 
}