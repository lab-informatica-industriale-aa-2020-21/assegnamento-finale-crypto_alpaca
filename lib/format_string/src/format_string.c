#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "blockchain.h"
#include "format_string.h"
#include "hash.h"
#include "file_IO.h"


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
    Nonce number:  <nonce HEX>              /
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
    N. di trans.   <numero DEC>             /
    \n

******************************************************************************/


//[*] -> snprintf(char *stringa_output, int dim_max_stringa, "testo", ...);


/*Funzione: 'uint32_to_stringHex' 
*----------------------------------------------------------------------------------------
* Converte un tipo intero in una stringa di lunghezza 'HEX_NUMB_LENGTH' in 
* rappresentazione esadecimale; 
* verranno aggiunti '0' negli eventuali spazi vuoti
* ---------------------------------------------------------------------------------------
* args:        number      ->   numero da convertire
*              str_out     ->   puntatore alla stringa su cui verrà salvato il risultato
* return:     void
*
*/
void uint32_to_stringHex(const uint32_t number, char *str_out){
    snprintf(str_out, HEX_NUMB_LENGTH + 1, "%0*x", HEX_NUMB_LENGTH, number);    //[*]
}


/* Funzione: 'uint32_to_stringDec' 
*------------------------------------------------------------------------------------------
* converte un tipo intero in una stringa di lunghezza 'DEC_NUMB_LENGTH' in 
* rappresentazione decimale;
* verranno aggiunti '0'  negli eventuali spazi vuoti
*------------------------------------------------------------------------------------------
* args:         number      ->  numero da convertire
*               str_out     ->  puntatore alla stringa su cui verrà salvato il risultato
* return:     void
*
*/
void uint32_to_stringDec(const uint32_t number, char *str_out){
    snprintf(str_out, DEC_NUMB_LENGTH + 1, "%0*u", DEC_NUMB_LENGTH, number);    //[*]
}


/* Funzione:'print_line' 
*-------------------------------------------------------------------------------------------
* formatta una stringa di lunghezza 'LINE_LENGTH' contenente una riga
* da stampare nel file 'blockchain.txt'. La riga è composta unendo un titolo
* (allineato a sx) di lunghezza 'TITLE_LENGTH' e un argomento (allineato a dx) di
* lunghezza 'ARG_LENGTH'.
*-------------------------------------------------------------------------------------------
*
*line:       Titolo:                   Argomento
*            \_____________/\__________________/
*             TITLE_LENGTH       ARG_LENGTH
*            \_________________________________/
*                       LINE_LENGTH
* args:       title       -> puntatore alla stringa contenente il titolo
*            arg         -> puntatore alla stringa contenente l'argomento
*            str_out     -> puntatore alla stringa su cui verrà salvato il risultato
* return:     void
*/
void print_line(const char *title, const char *arg, char *str_out){
    snprintf(str_out, LINE_LENGTH + 1, "%-*s%*s",
            TITLE_LENGTH, title, ARG_LENGTH, arg);  //[*]
}


void add_empty_line(char *str_out){
    char tmp [LINE_LENGTH + 1];  //per salvare le stringhe momentanee
    snprintf(tmp, LINE_LENGTH + 1, "%*c", LINE_LENGTH, ' ');
    strcat(str_out, tmp);
}


/* Funzione: 'print_block_header' 
*-------------------------------------------------------------------------------------------
* formatta una stringa 11 righe contenenti i dati di un blocco.
* (vedere anche formattazione completa all'inizio)
* line1   ->  indice del blocco
* line2   ->  data e ora di creazione
* line3   ->  hash
* line4   ->  hash
* line5   ->  hash
* line6   ->  hash
* line7   ->  hash
* line8   ->  hash
* line9   ->  hash
* line10  ->  hash
* line11  ->  nonce
*-------------------------------------------------------------------------------------------
* 
* args:        block_to_print  ->  puntatore al blocco da stampare
*              str_out         ->  puntatore alla stringa su cui verrà salvato il risultato
* return:      void
*/
void print_block_header(const block *block_to_print, char *str_out){
    char tmp [ARG_LENGTH + 1];  //per salvare le stringhe momentanee

    //line1 -> index
    char line1 [LINE_LENGTH + 1];
    uint32_to_stringDec(block_to_print -> count_block, tmp);
    print_line(IND, tmp, line1);

    //line2 -> creation
    char line2 [LINE_LENGTH + 1];
    get_str_creation_time(block_to_print -> creation_time, tmp);
    print_line(CRE, tmp, line2);

    //line3, 4, 5, 6, 7, 8, 9, 10 -> hash
    char line3 [LINE_LENGTH + 1], line4 [LINE_LENGTH + 1],
            line5 [LINE_LENGTH + 1], line6 [LINE_LENGTH + 1],
            line7 [LINE_LENGTH + 1], line8 [LINE_LENGTH + 1],
            line9 [LINE_LENGTH + 1], line10 [LINE_LENGTH + 1],
            line11 [LINE_LENGTH + 1];

        //3
    uint32_to_stringHex(block_to_print -> hash [0], tmp);
    print_line(HASH, tmp, line3);
        //4
    uint32_to_stringHex(block_to_print -> hash [1], tmp);
    print_line(" ", tmp, line4);
        //5
    uint32_to_stringHex(block_to_print -> hash [2], tmp);
    print_line(" ", tmp, line5);
        //6
    uint32_to_stringHex(block_to_print -> hash [3], tmp);
    print_line(" ", tmp, line6);
        //7
    uint32_to_stringHex(block_to_print -> hash [4], tmp);
    print_line(" ", tmp, line7);
        //8
    uint32_to_stringHex(block_to_print -> hash [5], tmp);
    print_line(" ", tmp, line8);
        //9
    uint32_to_stringHex(block_to_print -> hash [6], tmp);
    print_line(" ", tmp, line9);
        //10
    uint32_to_stringHex(block_to_print -> hash [7], tmp);
    print_line(" ", tmp, line10);

    //line11 -> nonce
    uint32_to_stringHex(block_to_print -> nonce, tmp);
    print_line(NONCE, tmp, line11);

    //stringa finale
    snprintf(str_out, BLOCK_HEADER_LENGTH + 1,
            "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s",
            line1, line2, line3, line4, line5, line6, line7, line8, line9,
            line10, line11);    //[*]
}


/* Funzione: 'print_trans' 
*-------------------------------------------------------------------------------------------
* formatta una stringa di 4 righe contenenti i dati di una transazione.
* (vedere anche formattazione completa all'inizio)
* line1   ->  numero transazione
* line2   ->  numero mittente in esadecimale
* line3   ->  numero destinatario in esadecimale
* line4   ->  importo in decimale
*-------------------------------------------------------------------------------------------
*
* args:         count       -> numero transazione
*               trans       -> puntatore alla transazione da stampare
*               str_out     -> puntatore alla stringa su cui verrà salvato il risultato
* return:       void
*
*/
void print_trans(const trans *trans_to_print, char *str_out){
    char tmp [ARG_LENGTH];  //per salvare le stringhe momentanee
    
    char line1 [LINE_LENGTH + 1], line2 [LINE_LENGTH + 1],
            line3 [LINE_LENGTH + 1], line4 [LINE_LENGTH + 1];

    //line1 ->  numero transazione
    uint32_to_stringDec(trans_to_print -> count_trans, tmp);
    print_line(TRNS, tmp, line1);

    //line2 ->  sender
    uint32_to_stringHex(trans_to_print -> sender, tmp);
    print_line(SEND, tmp, line2);

    //line3 -> receiver
    uint32_to_stringHex(trans_to_print -> receiver, tmp);
    print_line(RCV, tmp, line3);

    //line4 -> amount
    uint32_to_stringDec(trans_to_print -> amount, tmp);
    print_line(AMT, tmp, line4);

    //stringa finale
    snprintf(str_out, TRANS_LENGTH +1, "%s\n%s\n%s\n%s\n",
            line1, line2, line3, line4);
}


/* Funzione: 'print_block_trans' 
*-------------------------------------------------------------------------------------------
* formatta una stringa contenente la lista completa delle
* transazioni da inserire in un blocco, ognuna di esse formattata da
* 'print_trans', quindi la lista sarà una stringa di 4 * n_transactions righe.
* Alla fine della lista viene inserito il numero delle transazioni riportate.
* (vedere anche formattazione completa all'inizio)
* ------------------------------------------------------------------------------------------
*
* args:         block_to_print  ->  puntatore al blocco da stampare
*               str_out         ->  puntatore alla stringa su cui verrà salvato il risultato
* return:       void
*
*/
void print_block_trans(const block *block_to_print, char *str_out){
    char tmp [TRANS_LENGTH + 1];    //per salvare le stringhe momentanee

    //puntatore alla transazione da stampare
    trans *next_to_print = block_to_print -> first_trans;
    int n_cycle = 0;

    //il ciclo stampa una transazione alla volta fino alla fine della lista
    do {
        //stampa la transazione in 'tmp'
        print_trans(next_to_print, tmp);

        //aggiunge 'tmp' a 'str_out'
        if (n_cycle == 0)
            strcpy(str_out, tmp);
        else
            strcat(str_out, tmp);

        //aggiorna il puntatore next_to_print alla successiva transazione
        next_to_print = next_to_print -> next_trans;

        n_cycle ++;

    } while (next_to_print != NULL);

    //Per stampare alla fine il numero di transizioni inserite nel blocco
    char count_printed_trans [LINE_LENGTH + 1];
    snprintf(count_printed_trans, LINE_LENGTH + 1, "%-*s%*d", TITLE_LENGTH, NTRNS, ARG_LENGTH, n_cycle); //[*]
    strcat(str_out, count_printed_trans);
}


/* Funzione: 'print_block' 
*-------------------------------------------------------------------------------------------
* unisce le stringhe formattate da 'print_block_header' e
* 'print_block_trans' per formare un'unica srtinga contenente tutte le informazioni
* del blocco.
* (vedere anche formattazione completa all'inizio)
*-------------------------------------------------------------------------------------------
*
* args:       block_to_print  ->  puntatore al blocco da stampare
*             str_out         ->  puntatore alla stringa su cui verrà salvato il risultato 
* return:     void
*
*/


void print_block(const block *block_to_print, char *str_out){
    //per stampare l'header del blocco e le transazioni
    char block_header [BLOCK_HEADER_LENGTH + 1];
    char trans [TRANS_LENGTH * block_to_print -> num_trans + LINE_LENGTH + 1];
    print_block_header(block_to_print, block_header);
    print_block_trans(block_to_print, trans);

    //unione di header e transazioni
    snprintf(str_out, BLOCK_HEADER_LENGTH + block_to_print -> num_trans * TRANS_LENGTH + LINE_LENGTH + 1 + 1,
            "%s\n%s\n", block_header, trans);   //[*]
}


void format_data_for_hash(const block *block_source, char *str_for_hash){
    trans *next_to_print = block_source -> first_trans;
    char tmp [HEX_NUMB_LENGTH + 1];

    // Ricerca del prev hash:
    uint32_t previous_hash [DIM_HASH] = {0};

    if (block_source -> prev_hash == NULL)     //non esistono blocchi precedenti nella catena della sessione attuale
        get_prev_hash(previous_hash, BLOCKCHAIN_TXT);           //lettura prev_hash dal file blockchain.txt
    else
        for (int i = 0; i < DIM_HASH; i++)                      //copia del vettore prev_hash in previous_hash
            previous_hash [i] = block_source -> prev_hash [i];

    for (int i = 0; i < DIM_HASH; i++){
        uint32_to_stringHex(previous_hash[i], tmp);
        if (i == 0)
            strcpy(str_for_hash, tmp);
        else
            strcat(str_for_hash, tmp);

    do{
        uint32_to_stringHex(next_to_print -> sender, tmp);
        strcat(str_for_hash, tmp);

        uint32_to_stringHex(next_to_print -> receiver, tmp);
        strcat(str_for_hash, tmp);

        uint32_to_stringHex(next_to_print -> amount, tmp);
        strcat(str_for_hash, tmp);

        next_to_print = next_to_print -> next_trans;
    } while(next_to_print != NULL);
}