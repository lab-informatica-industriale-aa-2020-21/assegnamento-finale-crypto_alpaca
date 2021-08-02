#ifndef file_IO_h
#define file_IO_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include "chain.h"
#include "trans.h"
#include "block.h"

#define TITLE_LENGTH 15         //max caratteri per il titolo
#define ARG_LENGTH 20           //max caratteri per l'argomento
#define LINE_LENGTH (TITLE_LENGTH + ARG_LENGTH)
#define NUM_HEADER_LINE 11
#define NUM_TRANS_LINE 4
#define BLOCK_HEADER_LENGTH (NUM_HEADER_LINE * (LINE_LENGTH + 1))
#define TRANS_LENGTH (NUM_TRANS_LINE * (LINE_LENGTH + 1))
#define HEX_NUMB_LENGTH 8
#define DEC_NUMB_LENGTH 10
#define IND "Index:"
#define CRE "Creation time:"
#define HASH "Hash:"
#define SEND "Sender:"
#define RCV "Receiver:"
#define AMT "Amount:"
#define NONCE "Nonce number:"

//  Definizioni delle funzioni utilizzate in 'file_IO.c'

//  Conversione da un intero a 32bit a una stringa di esadecimale
void int32_to_stringHex(const uint_32_t number, char *str_out);

//  Conversione da un intero a 32bit a una stringa di decimali
void int32_to_stringDec(const uint_32_t number, char *str_out);

//  Stampa di una riga con struttura: TITLE - ARGUMENT 
void print_line(const char *title, const char *arg, char str_out);

/*  Stampa il blocco (escluse la lista delle transazioni inserite)
    Vengono stampate tutte le intestazioni (nonce, hash, prev_hash, ecc..)*/  
void print_block_header(const block *block_to_print, char *str_out);

//  Stampa di tutte le transazioni appartenenti ad un blocco 
void print_block_trans(const block *block_to_print, char *str_out);

#endif