#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "file_IO.h"
#include "transaction.h"
#include "block.h"


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



/*
'int32_to_stringHex' converte un tipo intero in una stringa di lunghezza
'HEX_NUMB_LENGTH' in rappresentazione esadecimale, verranno aggiunti degli '0'
negli eventuali spazi vuoti
args:       number      -> numero da convertire
            str_out     -> puntatore alla stringa su cui verrà salvato il risultato
return:     void
*/
void int32_to_stringHex(const uint32_t number, char *str_out){
    snprintf(str_out, HEX_NUMB_LENGTH + 1, "%08x", (int)number);    //[*]
}


/*
'int32_to_stringDec' converte un tipo intero in una stringa di lunghezza
'DEC_NUMB_LENGTH' in rappresentazione decimale, verranno aggiunti degli '0'
negli eventuali spazi vuoti
args:       number      -> numero da convertire
            str_out     -> puntatore alla stringa su cui verrà salvato il risultato
return:     void
*/
void int32_to_stringDec(const uint32_t number, char *str_out){
    snprintf(str_out, DEC_NUMB_LENGTH + 1, "%08d", (int)number);    //[*]
}


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
void print_line(const char *title, const char *arg, char *str_out){
    snprintf(str_out, LINE_LENGTH + 1, "%-*s%*s",
            TITLE_LENGTH, title, ARG_LENGTH, arg);  //[*]
}


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
void print_block_header(const block *block_to_print, char *str_out){
    char tmp [ARG_LENGTH + 1];  //per salvare le stringhe momentanee

    //line1 -> index
    char line1 [LINE_LENGTH + 1];
    int32_to_stringDec(block_to_print -> index, tmp);
    print_line(IND, tmp, line1);

    //line2 -> creation
    char line2 [LINE_LENGTH + 1];
    print_line(CRE, block_to_print -> creation_time, line2);

    //line3, 4, 5, 6, 7, 8, 9, 10 -> hash
    char line3 [LINE_LENGTH + 1], line4 [LINE_LENGTH + 1],
            line5 [LINE_LENGTH + 1], line6 [LINE_LENGTH + 1],
            line7 [LINE_LENGTH + 1], line8 [LINE_LENGTH + 1],
            line9 [LINE_LENGTH + 1], line10 [LINE_LENGTH + 1],
            line11 [LINE_LENGTH + 1];

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

    //stringa finale
    snprintf(str_out, BLOCK_HEADER_LENGTH + 1,
            "%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
            line1, line2, line3, line4, line5, line6, line7, line8, line9,
            line10, line11);    //[*]
}


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
void print_trans(const uint32_t num, const trans *trans_to_print, char *str_out){
    char tmp [ARG_LENGTH];  //per salvare le stringhe momentanee
    
    char line1 [LINE_LENGTH + 1], line2 [LINE_LENGTH + 1],
            line3 [LINE_LENGTH + 1], line4 [LINE_LENGTH + 1];

    //line1 ->  numero transazione
    snprintf(line1, LINE_LENGTH + 1, "%-*s%d", TITLE_LENGTH,TRNS, num); //[*]

    //line2 ->  sender
    int32_to_stringHex(trans_to_print -> sender, tmp);
    print_line(SEND, tmp, line2);

    //line3 -> receiver
    int32_to_stringDec(trans_to_print -> receiver, tmp);
    print_line(RCV, tmp, line3);

    //line4 -> amount
    int32_to_stringDec(trans_to_print -> amount, tmp);
    print_line(AMT, tmp, line4);

    //stringa finale
    snprintf(str_out, TRANS_LENGTH +1, "%s\n%s\n%s\n%s\n",
            line1, line2, line3, line4);
}


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
void print_block_trans(const struct block *block_to_print, char *str_out){
    char tmp [TRANS_LENGTH + 1];    //per salvare le stringhe momentanee
    uint32_t num = 0;   //per il conteggio delle transazioni

    //puntatore alla transazione da stampare
    struct trans *next_to_print = block_to_print -> first_trans;

    //il ciclo stampa una transazione alla volta fino alla fine della lista
    do {
        //stampa la transazione in 'tmp'
        print_trans(num, next_to_print, tmp);

        //aggiunge 'tmp' a 'str_out'
        strcat(str_out, tmp);

        num++;  //incrementa il contatore

        //aggiorna il puntatore next_to_print alla successiva transazione
        next_to_print = next_to_print -> next;

    } while (next_to_print == NULL);

    //Per stampare alla fine il numero di transizioni inserite nel blocco
    char num_printed_trans [DEC_NUMB_LENGTH + 2];
    snprintf(num_printed_trans, DEC_NUMB_LENGTH + 2, "-> %d transactions.\n", num); //[*]
    strcat(str_out, num_printed_trans)
}


/*
'print_block' unisce le stringhe formattate da 'print_block_header' e
'print_block_trans' per formare un'unica srtinga contenente tutte le informazioni
del blocco.
(vedere anche formattazione completa all'inizio)
args:       block_to_print  ->  puntatore al blocco da stampare
            str_out         ->  puntatore alla stringa su cui verrà salvato il risultato 
return:     void
*/
void print_block(const struct block *block_to_print, char *str_out){
    //per stampare l'header del blocco e le transazioni
    char block_header [BLOCK_HEADER_LENGTH + 1];
    char trans [TRANS_LENGTH * num_trans +1];
    print_block_header(block_to_print, block_header);
    print_block_trans(block_to_print,trans);

    //unione di header e transazioni
    snprintf(str_out, BLOCK_HEADER_LENGTH + num_trans * TRANS_LENGTH + 3,
            "%s\n%s\n", block_header, trans);   //[*]
}


/*
'write_block' apre il file 'blockchain.txt' (se non esiste lo crea) e scrive
al suo interno la stringa generata da 'print_block'.
args        block_to_print  ->  puntatore al blocco da stampare
return      void
*/
void write_block(const struct block *block_to_print){
    //apertura file
    FILE *fp_chain; //creazione puntatore al file
    fp_chain = fopen(BLOCKCHAIN_TXT, "w");  //apertura file

    if (fp_chain == NULL){  //controllo se l'apertura ha avuto esito positivo
        prinf("Error: can't open %s\n", BLOCKCHAIN_TXT);
        exit(EXIT_FAILURE);
    }

    //formattazione blocco
    char block_str [BLOCK_HEADER_LENGTH + num_trans * TRANS_LENGTH + 3];
    print_block(block_to_print, block_str);

    //scrittura blocco sul file di testo
    fprintf(fp_chain, "%s", block_str);

    //chiusura file
    fclose(fp_chain);
}

