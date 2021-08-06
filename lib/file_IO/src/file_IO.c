#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file_IO.h"
#include "transaction.h"
#include "block.h"
#include "chain.h"
#include "format_string.h"


void write_block(const block *block_to_print, FILE *fp){
    //formattazione blocco
    char block_str [BLOCK_HEADER_LENGTH + block_to_print -> num_trans * TRANS_LENGTH + 2 * (LINE_LENGTH + 1) + 1];
    print_block(block_to_print, block_str);
    add_empty_line(block_str);

    //scrittura blocco sul file di testo
    fprintf(fp, "%s\n", block_str);

    //chiusura file
    fclose(fp);
}


void save_chain(const chain *chain_to_print, const char *file_path){
    //apertura file
    FILE *fp_chain; //creazione puntatore al file
    fp_chain = fopen(file_path, "w");  //apertura file in scrittura

    if (fp_chain == NULL){  //controllo se l'apertura ha avuto esito positivo
        printf("Error: can't open %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    block *next_to_print = chain_to_print -> first_block;
    do{
        write_block(next_to_print, fp_chain, file_path);
        next_to_print = next_to_print -> next_block;
    } while(next_to_print != NULL);
}


void get_arg(FILE *fp, const long line, char *arg){
    fseek(fp, (LINE_LENGTH + 1) * line, SEEK_END);

    char line_str [LINE_LENGTH + 1];
    fgets(line_str, LINE_LENGTH + 1, fp);

    int steps = 0;
    
    while (line_str [LINE_LENGTH - 1 - steps] != ' ')
        steps++;
    
    strcpy(arg, line_str + LINE_LENGTH - steps);
}


uint32_t get_arg_uint32Dec(FILE *fp, long line){
    char arg [ARG_LENGTH + 1];
    get_arg(fp, line, arg);

    uint32_t tmp = 0;
    sscanf(arg, "%010u", &tmp);

    return tmp;
}


uint32_t get_arg_uint32Hex(FILE *fp, long line){
    char arg [ARG_LENGTH + 1];
    get_arg(fp, line, arg);

    uint32_t tmp = 0;
    sscanf(arg, "%08x", &tmp);

    return tmp;
}


void get_prev_hash(uint32_t *hash, const char *file_path){
    //apertura file
    FILE *fp_chain; //creazione puntatore al file
    fp_chain = fopen(file_path, "r");  //apertura file in lettura

    if (fp_chain == NULL){  //controllo se l'apertura ha avuto esito positivo
        printf("Error: can't open %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    uint32_t count_transaction = get_arg_uint32Dec(fp_chain, -2);

    for (int i = 0; i < 8; i++)                                                                                             //---------------> inserire costante 8 da <hash.h>
        hash [i] = get_arg_uint32Hex(fp_chain, (long)(-2 - NUM_TRANS_LINE * (int)count_transaction - 1 - 8 + i));          //---------------> inserire costante 8 da <hash.h>
}