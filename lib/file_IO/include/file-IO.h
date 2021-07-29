#ifndef file_IO_h
#define file_IO_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "chanin.h"

#define TITLE_LENGTH 15         //max caratteri per il titolo
#define ARG_LENGTH 20           //max caratteri per l'argomento
#define LINE_LENGTH (TITLE_LENGTH + ARG_LENGTH)
#define HEX_NUMB_LENGTH 8
#define DEC_NUMB_LENGTH 10
#define IND "Index:"
#define CRE "Creation time:"
#define HASH "Hash:"
#define TRANS "Transaction:"
#define NONCE "Nonce number:"

#endif