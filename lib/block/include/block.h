/*  Di seguito viene riportato l'header file per la gestione dei blocchi 
    di transazione da inserire nella blockchain */

// Struttura del blocco di transazioni:

#ifndef blocco_h
#define blocco_h

#include<stdio.h>
#include<stdbool.h>

#define MAX_VALID_FIRST_HASH_ELEMENT 0x0FFFFFFF

typedef struct
{
    uint32_t *prev_hash;            // puntatore a 'hash' del blocco precedente
    uint32_t hash[6];               // 'hash' del blocco corrente  
    uint32_t nonce;                 // valore di nonce
    trans *head;                    // puntatore alla testa della lista 
    time_t creation_time;           // tempo per la creazione del blocco 
    uint32_t index;                     // indice numerico del blocco
} block;

// Funzione per la creazione di uno nuovo blocco di transazioni della blockchain:
block *new_block(const block *last, const trans *head);

// Mina il nuovo blocco creato, ovvero aggiunge il blocco alla blockchain:
void mine(block *const block_to_mine, uint *const count_index);

#endif