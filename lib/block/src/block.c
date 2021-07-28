// File delle funzioni

#include "block.h"

// Dichiarazioni delle variabili:
uint count_index = 0;
block *last = NULL;

// Funzione per la creazione di uno nuovo blocco di transazioni della blockchain:
block *new_block(const block *last, const trans *head){

    block *tmp_block;
    tmp_block = malloc(sizeof(block));

    if(tmp_block == NULL){
        printf("Error: malloc() failure");
        exit(EXIT_FAILURE);
    }

    tmp_block -> prev_hash = last -> hash;
    tmp_block -> last = tmp_block; 
    tmp_block -> nonce = 0;     //valore temporaneo
    tmp_block -> index = 0;     //valore temporaneo
    // hash = (richiamo funzione di calcolo dell'hash)    //assegnazione hash

    return tmp_block;
}

void mine(block *const block_to_mine, uint *const count_index){
    while (block_to_mine -> hash[0] > MAX_VALID_FIRST_HASH_ELEMENT){     //controllo se i primi 4 bit (del primo uint_32) sono diversi da 0
        block_to_mine -> nonce ++;
        // block_to_mine -> hash = funzione calcolo hash();
    }

    // block_to_mine -> creation_time = funzione tempo();
    *count_index ++;
    block_to_mine -> index = *count_index;
}