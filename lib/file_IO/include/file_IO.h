/*===========================================================================*/
/**
 * @file file_IO.h
 * @brief Header del modulo file_IO.
*/
/*===========================================================================*/

/*!
 * @def BLOCK_CHAIN_TXT
 * @brief Stringa contenente il 'path' di blockchain.txt.
 * 
 * La macro definisce la directory in cui si trova il file
 * blockchain.txt e il nome del file stesso.
*/

/*!
 * @def TEST_BLOCK_CHAIN_TXT
 * @brief Stringa contenente il 'path' di test_blockchain.txt.
 * 
 * La macro definisce la directory in cui si trova il file
 * test_blockchain.txt e il nome del file stesso.
*/


#ifndef FILE_IO_H
#define FILE_IO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "blockchain.h"

#define BLOCKCHAIN_TXT "../inout/blockchain.txt"
#define TEST_BLOCKCHAIN_TXT "../inout/test_blockchain.txt"


void write_block(const block *block_to_print, FILE *fp);


void save_chain(const chain *chain_to_print, const char *file_path);


void get_arg(FILE *fp, const long line, char *arg);


uint32_t get_arg_uint32Dec(FILE *fp, long line);


uint32_t get_arg_uint32Hex(FILE *fp, long line);


uint32_t get_prev_index(const char *file_path);


void get_prev_hash(uint32_t *hash, const char *file_path);


void get_trans_str(char *str_out, const char *file_path);

#endif
