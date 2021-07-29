// File.c per la creazione di una nuova blockchain:

#include "block.h"

block *head_block = NULL;

// Aggiunta di un blocco minato alla blockchain:
void add_block(block *last, trans *head){
    block *old_head_block = head_block;
    head = mine(block *block_to_mine, uint index);
    old_head_block -> head = head_block;
}

