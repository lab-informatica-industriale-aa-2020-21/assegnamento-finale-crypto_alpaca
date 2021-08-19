/*===========================================================================*/
/**
 * @file format_string.h
 * @brief Header del modulo format_string.
*/
/*===========================================================================*/


#ifndef FORMAT_STRING_H
#define FORMAT_STRING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "blockchain.h"
#include "gui.h"

//costanti di lunghezza delle stringhe
#define TITLE_LENGTH 15         //max caratteri per il titolo
#define ARG_LENGTH 20           //max caratteri per l'argomento
#define LINE_LENGTH (TITLE_LENGTH + ARG_LENGTH)     //max caratteri per una riga
#define NUM_HEADER_LINE 11      //righe header blocco
#define NUM_TRANS_LINE 4        //righe per una transazione
#define BLOCK_HEADER_LENGTH (NUM_HEADER_LINE * (LINE_LENGTH + 1))   //numero caratteri del blocco
#define TRANS_LENGTH (NUM_TRANS_LINE * (LINE_LENGTH + 1))           //numer caratteri di una transazione
#define HEX_NUMB_LENGTH 8       //max caratteri per un int a 32 bit in esadecimale
#define DEC_NUMB_LENGTH 10      //max caratteri per un int a 32 bit in decimale

//stringhe costanti per titoli e nomi di file
#define IND "Index:"
#define CRE "Creation time:"
#define HASH "Hash number:"
#define SEND "Sender:"
#define RCV "Receiver:"
#define AMT "Amount:"
#define NONCE "Nonce number:"
#define TRNS "Transaction n."
#define NTRNS "N. di trans."



void uint32_to_stringHex(const uint32_t number, char *str_out);

void uint32_to_stringDec(const uint32_t number, char *str_out);

void print_line(const char *title, const char *arg, char *str_out);

void add_empty_line(char *str_out);

void print_block_header(const block *block_to_print, char *str_out);

void block_header_matrix(const block *block_to_print, char matrix [BLOCK_LINES][LINE_LENGTH + 1]);

void print_trans(const trans *trans_to_print, char *str_out);

void print_block_trans(const block *block_to_print, char *str_out);

void print_block(const block *block_to_print, char *str_out);

void format_data_for_hash(const block *block_source, char *trans_str);

#endif
