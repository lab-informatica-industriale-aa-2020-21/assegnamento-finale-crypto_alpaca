#include "file_IO.h"

// index        ->  uint
// creation     ->  data e ora
// hash         ->  6 righe di int32 Hex
// trans        ->  3 righe di int32 Hex per sender, receiver, Dec amount
// nonce        ->  int32

char titles [][] = {IND, CRE, HASH, TRANS, NONCE};

void int32_to_stringHex (const uint_32_t number, char *string){
    snprintf(string, HEX_NUMB_LENGTH + 1, "%08x", (int)number);
}

void int32_to_stringDec (const uint_32_t number, chat *string){
    snprintf(string, DEC_NUMB_LENGTH + 1, "%08d", (int)number);
}

void print_line (const char *title, const char *arg, char str_out){
    
}