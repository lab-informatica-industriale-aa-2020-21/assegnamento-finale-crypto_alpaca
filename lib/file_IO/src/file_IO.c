#include "file_IO.h"
#include<stdio.h>
#include<string.h>

// index        ->  uint
// creation     ->  data e ora
// hash         ->  6 righe di int32 Hex
// trans        ->  3 righe di int32 Hex per sender, receiver, Dec amount
// nonce        ->  int32


void int32_to_stringHex(const uint_32_t number, char *str_out){
    snprintf(str_out, HEX_NUMB_LENGTH + 1, "%08x", (int)number);
}

void int32_to_stringDec(const uint_32_t number, char *str_out){
    snprintf(str_out, DEC_NUMB_LENGTH + 1, "%08d", (int)number);
}

void print_line(const char *title, const char *arg, char str_out){
    snprintf(str_out, LINE_LENGTH + 1, "%-*s%*s", TITLE_LENGTH, title, ARG_LENGTH, arg);
}

void print_block_header(const block *block_to_print, char *str_out){
    //line1 -> index
    char line1 [LINE_LENGTH + 1];
    char tmp [ARG_LENGTH + 1];
    int32_to_stringDec(*block_to_print -> index, tmp);
    print_line(IND, tmp, line 1);

    //line2 -> creation
    char line2 [LINE_LENGTH + 1];
    print_line(CRE, block_to_print -> creation_time, line2);

    //line3, 4, 5, 6, 7, 8 -> hash
    char line3 [LINE_LENGTH + 1], line4 [LINE_LENGTH + 1], line5 [LINE_LENGTH + 1], line6 [LINE_LENGTH + 1], line7 [LINE_LENGTH + 1], line8 [LINE_LENGTH + 1];

        //3
    int32_to_stringHex(*block_to_print -> hash [0], tmp);
    print_line(HASH, tmp, line3);
        //4
    int32_to_stringHex(*block_to_print -> hash [1], tmp);
    print_line(" ", tmp, line4);
        //5
    int32_to_stringHex(*block_to_print -> hash [2], tmp);
    print_line(" ", tmp, line5);
        //6
    int32_to_stringHex(*block_to_print -> hash [3], tmp);
    print_line(" ", tmp, line6);
        //7
    int32_to_stringHex(*block_to_print -> hash [4], tmp);
    print_line(" ", tmp, line7);
        //8
    int32_to_stringHex(*block_to_print -> hash [5], tmp);
    print_line(" ", tmp, line8);

    //line9 -> nonce
    char line9 [LINE_LENGTH + 1]
    int32_to_stringDEC(*block_to_print -> nonce, tmp);
    print_line(NONCE, tmp, line9)

    snprintf(str_out, BLOCK_HEADER_LENGTH + 1, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n"), line1, line2, line3, line4, line5, line6, line7, line8, line9)
}

void print_block_trans(const block *block_to_print, char *str_out){
    int num_trans = *block_to_print -> num_trans;

    trans *next = block_to_print -> first_trans;

    do {
        //stampa prima transazione
        //aggiorna il puntatore next alla successiva transazione
    } while (next == NULL);
}