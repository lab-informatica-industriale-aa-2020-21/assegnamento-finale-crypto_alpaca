// File header per la funzione di hash:
#ifndef HASH_H
#define HASH_H

#include <stdbool.h>
#include <stdint.h>

unsigned int rotate (unsigned int num, int n_bit);
unsigned int sigma_0 (unsigned int x);
unsigned int sigma_1 (unsigned int x);
unsigned int usigma_0 (unsigned int x);
unsigned int usigma_1 (unsigned int x);
unsigned int maggiority (unsigned int x, unsigned int y,  unsigned int z);
unsigned int choice ( unsigned int x, unsigned int y,  unsigned int z);
unsigned int bin_to_decimal (bool *x, int len_x);
void decimal_to_bin (unsigned int x, bool *vett, int len_vett);
char* int_32_to_char(unsigned int input);

// Funzione per creaare il messaggio a partire dai dati ricevuti dal blocco
unsigned int* create_block(unsigned int list_trans_len, int *n_block);

// Funzione per il caricamento dei dati relativi al blocco (pre_hash, nonce ecc...)
void loading_data (unsigned int* block_data, int n_block, const unsigned int* prev_hash, unsigned int nonce, char* list_trans, unsigned int list_trans_len);

// Funzione per convertire dal formato uint32_t al formato uint8_t
void uint32_to_uint8 (unsigned int input, uint8_t *n);

#endif
