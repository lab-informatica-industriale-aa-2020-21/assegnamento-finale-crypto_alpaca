/*===========================================================================*/
/**
 * @file format_string.h
 * @brief Header del modulo format_string.
*/
/*===========================================================================*/


/*!
 * @def TITLE_LENGTH
 * @brief Lunghezza massima dei titoli.
 * 
 * La macro definisce dimensione massima della stringa contenente
 * i titoli.
*/

/*!
 * @def ARG_LENGTH
 * @brief Lunghezza massima degli argomenti.
 * 
 * La macro definisce dimensione massima della stringa contenente
 * gli argomenti.
*/

/*!
 * @def LINE_LENGTH
 * @brief Lunghezza massima di una riga.
 * 
 * La macro definisce dimensione massima della stringa contenente
 * una riga con titolo e argomento.
*/

/*!
 * @def NUM_HRADER_LINE
 * @brief Numero di righe per l'header del blocco.
 * 
 * La macro definisce il numero di righe necessarie per la stampa
 * dell'header di un blocco.
*/

/*!
 * @def TRANS_LINE
 * @brief Numero di righe per una transazione.
 * 
 * La macro definisce il numero di righe necessarie per la stampa
 * di una transazione.
*/

/*!
 * @def BLOCK_HEADER_LENGTH
 * @brief Lunghezza di una stringa contenente l'header di un blocco.
 * 
 * La macro definisce la dimensione della stringa utilizzata per
 * stampare l'header di un blocco.
*/

/*!
 * @def TRANS_LENGTH
 * @brief Lunghezza di una stringa contenente una transazione.
 * 
 * La macro definisce la dimensione della stringa utilizzata per
 * stampare una transazione.
*/

/*!
 * @def HEX_NUMB_LENGTH
 * @brief Numero di caratteri per un uint32_t in HEX.
 * 
 * La macro definisce il numero di caratteri necessario per la
 * stampa di un numero a 32 bit in esadecimele.
*/

/*!
 * @def DEC_NUMB_LENGTH
 * @brief Numero di caratteri per un uint32_t in DEC.
 * 
 * La macro definisce il numero di caratteri necessario per la
 * stampa di un numero a 32 bit in decimale.
*/

/*!
 * @def IND
 * @brief Stringa da stampare alla voce 'index'.
 * 
 * La macro definisce il titolo da stampare alla riga
 * contenente la voce 'index'.
*/

/*!
 * @def CRE
 * @brief Stringa da stampare alla voce 'creation time'.
 * 
 * La macro definisce il titolo da stampare alla riga
 * contenente la voce 'creation time'.
*/

/*!
 * @def HASH
 * @brief Stringa da stampare alla voce 'hash'.
 * 
 * La macro definisce il titolo da stampare alla riga
 * contenente la voce 'hash'.
*/

/*!
 * @def SEND
 * @brief Stringa da stampare alla voce 'sender'.
 * 
 * La macro definisce il titolo da stampare alla riga
 * contenente la voce 'sender'.
*/

/*!
 * @def RCV
 * @brief Stringa da stampare alla voce 'receiver'.
 * 
 * La macro definisce il titolo da stampare alla riga
 * contenente la voce 'receiver'.
*/

/*!
 * @def AMT
 * @brief Stringa da stampare alla voce 'amount'.
 * 
 * La macro definisce il titolo da stampare alla riga
 * contenente la voce 'amount'.
*/

/*!
 * @def NONCE
 * @brief Stringa da stampare alla voce 'nonce'.
 * 
 * La macro definisce il titolo da stampare alla riga
 * contenente la voce 'nonce'.
*/

/*!
 * @def TRNS
 * @brief Stringa da stampare alla voce 'transaction'.
 * 
 * La macro definisce il titolo da stampare alla riga
 * contenente la voce 'transaction'.
*/

/*!
 * @def NTRNS
 * @brief Stringa da stampare alla voce 'n. of trans.'
 * 
 * La macro definisce il titolo da stampare alla riga
 * contenente la voce 'n. of trans.'
*/

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
#define NTRNS "N. of trans."



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
