#ifndef file_IO_h
#define file_IO_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file_IO.h"
#include "transaction.h"
#include "block.h"

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
#define BLOCKCHAIN_TXT "blockchain.txt"


/******************************************************************************

    Formattazione testo blockchain:

    Index:         <num del blocco DEC>     \
    Creation time: <data e ora creazione>   |
    Hash number:   <hash [0]                |
                    hash [1]                |
                    hash [2]                |
                    hash [3]                |   BLOCK HEADER
                    hash [4]                |
                    hash [5]                |
                    hash [6]                |
                    hash [7] HEX>           |
    Nonce number:  <nonce DEC>              /
    Transaction n. <numero trans.>          \
    Sender:        <num. mittente HEX>      |
    Receiver:      <num. dest. HEX>         |
    Amount:        <importo DEC>            |
    Transaction n. <numero trans.>          |
    Amount:        ...                      |   TRANSACTION LIST
    .                                       |
    .   (per tutte le transazioni)          |
    .                                       |
                                            |
    -> <numero> transactions.               /


******************************************************************************/

//funzioni:

/*
'int32_to_stringHex' converte un tipo intero in una stringa di lunghezza
'HEX_NUMB_LENGTH' in rappresentazione esadecimale, verranno aggiunti degli '0'
negli eventuali spazi vuoti
args:       number      -> numero da convertire
            str_out     -> puntatore alla stringa su cui verrà salvato il risultato
return:     void
*/
void int32_to_stringHex(const uint32_t number, char *str_out);


/*
'int32_to_stringDec' converte un tipo intero in una stringa di lunghezza
'DEC_NUMB_LENGTH' in rappresentazione decimale, verranno aggiunti degli '0'
negli eventuali spazi vuoti
args:       number      -> numero da convertire
            str_out     -> puntatore alla stringa su cui verrà salvato il risultato
return:     void
*/
void int32_to_stringDec(const uint32_t number, char *str_out);


/*
'print_line' formatta una stringa di lunghezza 'LINE_LENGTH' contenente una riga
da stampare nel file 'blockchain.txt'. La riga è composta unendo un titolo
(allineato a sx) di lunghezza 'TITLE_LENGTH' e un argomento (allineato a dx) di
lunghezza 'ARG_LENGTH'.
line:       Titolo:                   Argomento
            \_____________/\__________________/
             TITLE_LENGTH       ARG_LENGTH
            \_________________________________/
                       LINE_LENGT
args:       title       -> puntatore alla stringa contenente il titolo
            arg         -> puntatore alla stringa contenente l'argomento
            str_out     -> puntatore alla stringa su cui verrà salvato il risultato
return:     void
*/
void print_line(const char *title, const char *arg, char *str_out);


/*
'print_block_header' formatta una stringa 11 righe contenenti i dati di un blocco.
(vedere anche formattazione completa all'inizio)
line1   ->  indice del blocco
line2   ->  data e ora di creazione
line3   ->  hash
line4   ->  hash
line5   ->  hash
line6   ->  hash
line7   ->  hash
line8   ->  hash
line9   ->  hash
line10  ->  hash
line11  ->  nonce
args:       block_to_print  ->  puntatore al blocco da stampare
            str_out         ->  puntatore alla stringa su cui verrà salvato il risultato
return:     void
*/
void print_block_header(const block *block_to_print, char *str_out);

/*
'print_trans' formatta una stringa di 4 righe contenenti i dati di una transazione.
(vedere anche formattazione completa all'inizio)
line1   ->  numero transazione
line2   ->  numero mittente in esadecimale
line3   ->  numero destinatario in esadecimale
line4   ->  importo in decimale
args:       num         -> numero transazione
            trans       -> puntatore alla transazione da stampare
            str_out     -> puntatore alla stringa su cui verrà salvato il risultato
return:     void
*/
void print_trans(const uint32_t num, const trans *trans_to_print, char *str_out);


/*
'print_block_trans' formatta una stringa contenente la lista completa delle
transazioni da inserire in un blocco, ognuna di esse formattata da
'print_trans', quindi la lista sarà una stringa di 4 * n_transactions righe.
Alla fine della lista viene inserito il numero delle transazioni riportate.
(vedere anche formattazione completa all'inizio)
args:       block_to_print  ->  puntatore al blocco da stampare
            str_out         ->  puntatore alla stringa su cui verrà salvato il risultato
return:     void
*/
void print_block_trans(const block *block_to_print, char *str_out);


/*
'print_block' unisce le stringhe formattate da 'print_block_header' e
'print_block_trans' per formare un'unica srtinga contenente tutte le informazioni
del blocco.
(vedere anche formattazione completa all'inizio)
args:       block_to_print  ->  puntatore al blocco da stampare
            str_out         ->  puntatore alla stringa su cui verrà salvato il risultato 
return:     void
*/
void print_block(const block *block_to_print, char *str_out);


/*
'write_block' apre il file 'blockchain.txt' (se non esiste lo crea) e scrive
al suo interno la stringa generata da 'print_block'.
args        block_to_print  ->  puntatore al blocco da stampare
return      void
*/
void write_block(const block *block_to_print);

#endif
