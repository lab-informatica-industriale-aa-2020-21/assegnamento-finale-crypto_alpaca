#include "file_IO.h"
#include "trans.h"
#include "block.h"
#include "chain.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
// index        ->  uint
// creation     ->  data e ora
// hash         ->  6 righe di int32 Hex
// trans        ->  3 righe di int32 Hex per sender, receiver, Dec amount
// nonce        ->  int32


void int32_to_stringHex(const uint32_t number, char *str_out){
    snprintf(str_out, HEX_NUMB_LENGTH + 1, "%08x", (int)number);
}

void int32_to_stringDec(const uint32_t number, char *str_out){
    snprintf(str_out, DEC_NUMB_LENGTH + 1, "%08d", (int)number);
}

void print_line(const char *title, const char *arg, char *str_out){
    snprintf(str_out, LINE_LENGTH + 1, "%-*s%*s", TITLE_LENGTH, title, ARG_LENGTH, arg);
}

void print_trans(const uint32_t num_trans, const trans *trans_to_print, char *str_out){
    char line1 [TITLE_LENGTH + 1], line2 [TITLE_LENGTH + 1], line3 [TITLE_LENGTH + 1], line4 [TITLE_LENGTH + 1];
    char tmp [ARG_LENGTH];
    
    int32_to_stringDec(num_trans, tmp);
    snprintf(line1, LINE_LENGTH + 1, "#%s", tmp);

    int32_to_stringHex(trans_to_print -> sender, tmp);
    print_line(SEND, tmp, line2);

    int32_to_stringDec(trans_to_print -> receiver, tmp);
    print_line(RCV, tmp, line3);

    int32_to_stringDec(trans_to_print -> amount, tmp);
    print_line(AMT, tmp, line4);

    snprintf(str_out, TRANS_LENGTH +1, "%s\n%s\n%s\n%s\n", line1, line2, line3, line4);
}

void print_block_header(const struct block *block_to_print, char *str_out){
    //line1 -> index
    char line1 [LINE_LENGTH + 1];
    char tmp [ARG_LENGTH + 1];
    int32_to_stringDec(block_to_print -> index, tmp);
    print_line(IND, tmp, line1);

    //line2 -> creation
    char line2 [LINE_LENGTH + 1];
    print_line(CRE, block_to_print -> creation_time, line2);

    //line3, 4, 5, 6, 7, 8, 9, 10 -> hash
    char line3 [LINE_LENGTH + 1], line4 [LINE_LENGTH + 1], line5 [LINE_LENGTH + 1], line6 [LINE_LENGTH + 1], line7 [LINE_LENGTH + 1], line8 [LINE_LENGTH + 1], line9 [LINE_LENGTH + 1], line10 [LINE_LENGTH + 1], line11 [LINE_LENGTH + 1];

        //3
    int32_to_stringHex(block_to_print -> hash [0], tmp);
    print_line(HASH, tmp, line3);
        //4
    int32_to_stringHex(block_to_print -> hash [1], tmp);
    print_line(" ", tmp, line4);
        //5
    int32_to_stringHex(block_to_print -> hash [2], tmp);
    print_line(" ", tmp, line5);
        //6
    int32_to_stringHex(block_to_print -> hash [3], tmp);
    print_line(" ", tmp, line6);
        //7
    int32_to_stringHex(block_to_print -> hash [4], tmp);
    print_line(" ", tmp, line7);
        //8
    int32_to_stringHex(block_to_print -> hash [5], tmp);
    print_line(" ", tmp, line8);
        //9
    int32_to_stringHex(block_to_print -> hash [6], tmp);
    print_line(" ", tmp, line9);
        //10
    int32_to_stringHex(block_to_print -> hash [7], tmp);
    print_line(" ", tmp, line10);

    //line11 -> nonce
    int32_to_stringDec(block_to_print -> nonce, tmp);
    print_line(NONCE, tmp, line11);

    snprintf(str_out, BLOCK_HEADER_LENGTH + 1, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", line1, line2, line3, line4, line5, line6, line7, line8, line9, line10, line11);
}

void print_block_trans(const struct block *block_to_print, char *str_out){

    char tmp [TRANS_LENGTH + 1];

    struct trans *next_to_print = block_to_print -> first_trans;

    do {
        //stampa prima transazione
        print_trans(num_trans, next_to_print, tmp);
        strcat(str_out, tmp);
        //aggiorna il puntatore next_to_print alla successiva transazione
        next_to_print = next_to_print -> next;
    } while (next_to_print == NULL);
}

void print_block(const struct block *block_to_print, char *str_out){
    char block_header [BLOCK_HEADER_LENGTH + 1];
    char trans [TRANS_LENGTH * num_trans +1];

    print_block_header(block_to_print, block_header);
    print_block_trans(block_to_print,trans);

    snprintf(str_out, BLOCK_HEADER_LENGTH + num_trans * TRANS_LENGTH + 3, "%s\n%s\n", block_header, trans);
}

void write_block(const struct block *block_to_print){
    FILE *fp_chain;
    fp_chain = fopen("blockchain.txt", "w");

    char block_str [BLOCK_HEADER_LENGTH + num_trans * TRANS_LENGTH + 3];
    print_block(block_to_print, block_str);

    fprintf(fp_chain, "%s", block_str);

    fclose(fp_chain);
}