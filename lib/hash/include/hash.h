// File header per la funzione di hash:
#ifndef HASH_H
#define HASH_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define setBit(A,k)     ( A[(k)/8] |= (1 << ((k)%8)) )
#define clearBit(A,k)   ( A[(k)/8] &= ~(1 << ((k)%8)) )
#define testBit(A,k)    ( A[(k)/8] & (1 << ((k)%8)) )

// Variabili define:

#define WORD_LEN_BITS 32
#define BIT_PER_CHAR 8
#define CHARS_PER_WORD 4
#define DIM_HASH 8                      //L'hash avrà sempre dimensione pari a 256bit -> 8word
#define PCI_HASH 65                     //Dimensione info di ridondanza definite dall'algoritmo SHA-256
#define DIM_BLOCK_HASH 16               //Dimensione blocco hash in W32
#define VAL_MAX_32BIT 2147483648
#define DIM_PREV_HASH 640               //Dimesione hash sempre pari a 256, per definizione. Poichè la funz. hash accetta in input solo char a seguito della conversione risulta: 
                                        //8(uint32) * N_CHAR_PER_UINT32 * 8bit(dimensione di un char) = 640.

#define N_CHAR_PER_UINT32 10
#define N_CHAR_PER_PREV_HASH 20         //N celle char per memorizzare il prev hash 10char per ogni unsigned int, sapendo che l'hash è costituito da 8 unsigned int 

#define OFFSET_MOD_0 32768              //Separatore tra dati e padding in caso di list_trans_len % 4 == 0. 
#define OFFSET_MOD_1 128                //Separatore tra dati e padding in caso di list_trans_len % 4 == 1. 
#define OFFSET_MOD_2 2147483648         //Separatore tra dati e padding in caso di list_trans_len % 4 == 2. 
#define OFFSET_MOD_3 8388608            //Separatore tra dati e padding in caso di list_trans_len % 4 == 3. 

#define MSG_INFO_LEN_WORDS 2
#define MSG_INFO_LEN_BYTES 8
#define MSG_BLOCK_LEN_WORDS 16
#define MSG_BLOCK_LEN_BYTES 64

#define H_INIZIALI  0x6a09e667,\
                    0xbb67ae85,\
                    0x3c6ef372,\
                    0xa54ff53a,\
                    0x510e527f,\
                    0x9b05688c,\
                    0x1f83d9ab,\
                    0x5be0cd19

#define KI_INIZIALI 0x428a2f98,\
                    0x71374491,\
                    0xb5c0fbcf,\
                    0xe9b5dba5,\
                    0x3956c25b,\
                    0x59f111f1,\
                    0x923f82a4,\
                    0xab1c5ed5,\
                    0xd807aa98,\
                    0x12835b01,\
                    0x243185be,\
                    0x550c7dc3,\
                    0x72be5d74,\
                    0x80deb1fe,\
                    0x9bdc06a7,\
                    0xc19bf174,\
                    0xe49b69c1,\
                    0xefbe4786,\
                    0x0fc19dc6,\
                    0x240ca1cc,\
                    0x2de92c6f,\
                    0x4a7484aa,\
                    0x5cb0a9dc,\
                    0x76f988da,\
                    0x983e5152,\
                    0xa831c66d,\
                    0xb00327c8,\
                    0xbf597fc7,\
                    0xc6e00bf3,\
                    0xd5a79147,\
                    0x06ca6351,\
                    0x14292967,\
                    0x27b70a85,\
                    0x2e1b2138,\
                    0x4d2c6dfc,\
                    0x53380d13,\
                    0x650a7354,\
                    0x766a0abb,\
                    0x81c2c92e,\
                    0x92722c85,\
                    0xa2bfe8a1,\
                    0xa81a664b,\
                    0xc24b8b70,\
                    0xc76c51a3,\
                    0xd192e819,\
                    0xd6990624,\
                    0xf40e3585,\
                    0x106aa070,\
                    0x19a4c116,\
                    0x1e376c08,\
                    0x2748774c,\
                    0x34b0bcb5,\
                    0x391c0cb3,\
                    0x4ed8aa4a,\
                    0x5b9cca4f,\
                    0x682e6ff3,\
                    0x748f82ee,\
                    0x78a5636f,\
                    0x84c87814,\
                    0x8cc70208,\
                    0x90befffa,\
                    0xa4506ceb,\
                    0xbef9a3f7,\
                    0xc67178f2


struct Msg_block {
    uint8_t *data;
    uint32_t msg_len;
};
typedef struct Msg_block msg_block;



unsigned int rotate (unsigned int num, int n_bit);
unsigned int sigma_0 (unsigned int x);
unsigned int sigma_1 (unsigned int x);
unsigned int usigma_0 (unsigned int x);
unsigned int usigma_1 (unsigned int x);
unsigned int majority (unsigned int x, unsigned int y,  unsigned int z);
unsigned int choice ( unsigned int x, unsigned int y,  unsigned int z);
unsigned int bin_to_decimal (bool *x, int len_x);
void decimal_to_bin (unsigned int x, bool *vett, int len_vett);
char* int_32_to_char(unsigned int input);
void shift_state_reg(unsigned int *vett, int len);
bool copy_vector(const unsigned int *vett1, uint32_t len1, unsigned int *vett2, uint32_t len2);
bool sum_vector(const unsigned int *vett1, int len1, unsigned int *vett2, int len2);

uint32_t *make_msg_block(const char *const str_input, uint32_t *const n_blocks);
void load_data(const char *const str_input, uint32_t *msg_data, uint32_t * const n_blocks);
uint8_t get_free_bytes(const char *const string);
void hash(const char *const str_input, uint32_t *const h_i);

#endif
