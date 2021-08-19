/*===========================================================================*/
/**
 * @file file_IO.c
 * @brief File sorgente del modulo file_IO.
 * 
 * Commento modulo file_IO...
 * 
 * @author Emanuele Zanoni
 */
/*===========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "blockchain.h"
#include "file_IO.h"
#include "format_string.h"
#include "hash.h"


/** 
 * Scrive tutte le informazioni di un blocco nel file di testo specificato.
 *
 * @param[in] block_to_print puntatore al blocco da cui prendere le informazioni
 * 
 * @param[in, out] fp puntatore al file su cui stampare 
 */

void write_block(const block *block_to_print, FILE *fp){
    //formattazione blocco
    char block_str [BLOCK_HEADER_LENGTH + block_to_print -> num_trans * TRANS_LENGTH + 2 * (LINE_LENGTH + 1) + 1];
    print_block(block_to_print, block_str);
    add_empty_line(block_str);

    //scrittura blocco sul file di testo
    fprintf(fp, "%s\n", block_str);
}


/** 
 * Salva tutti i blocchi di una chain su un file di testo.
 *
 * @param[in] chain_to_print puntatore alla catena da cui prendere le informazioni
 * 
 * @param[in] file_path stringa contenente la directory e il file su cui stampare
 */

void save_chain(const chain *chain_to_print, const char *file_path){
    //apertura file
    FILE *fp_chain; //creazione puntatore al file
    fp_chain = fopen(file_path, "a+");  //apertura file in scrittura
    

    if (fp_chain == NULL){  //controllo se l'apertura ha avuto esito positivo
        printf("Error: can't open %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    fseek(fp_chain, 0L, SEEK_END);

    block *next_to_print = chain_to_print -> first_block;
    do{
        write_block(next_to_print, fp_chain);
        next_to_print = next_to_print -> next_block;
    } while(next_to_print != NULL);

    fclose(fp_chain);
}


/** 
 * Ricava un argomento da un file di testo con stampati dei blocchi.
 *
 * @param[in, out] fp puntatore al file da cui leggere
 * 
 * @param[in] line riga di testo da cui leggere (partendo dalla
 * fine del file -> numero negativo)
 * 
 * @param[out] arg stringa su cui salvare l'argomento
 */

void get_arg(FILE *fp, const long line, char *arg){
    fseek(fp, (LINE_LENGTH + 1) * line, SEEK_END);

    char line_str [LINE_LENGTH + 1];
    fgets(line_str, LINE_LENGTH + 1, fp);

    int steps = 0;
    
    while (line_str [LINE_LENGTH - 1 - steps] != ' ')
        steps++;
    
    strcpy(arg, line_str + LINE_LENGTH - steps);
}


/** 
 * Ricava un argomento (numero decimale) da un file di testo con stampati
 * dei blocchi e lo converte in uint32_t.
 *
 * @param[in, out] fp puntatore al file da cui leggere
 * 
 * @param[in] line riga di testo da cui leggere (partendo dalla
 * fine del file -> numero negativo)
 * 
 * @return argomento in formato uint32_t
 */

uint32_t get_arg_uint32Dec(FILE *fp, long line){
    char arg [ARG_LENGTH + 1];
    get_arg(fp, line, arg);

    uint32_t tmp = 0;
    sscanf(arg, "%010u", &tmp);

    return tmp;
}


/** 
 * Ricava un argomento (numero esadecimale) da un file di testo con stampati
 * dei blocchi e lo converte in uint32_t.
 *
 * @param[in, out] fp puntatore al file da cui leggere
 * 
 * @param[in] line riga di testo da cui leggere (partendo dalla
 * fine del file -> numero negativo)
 * 
 * @return argomento in formato uint32_t
 */

uint32_t get_arg_uint32Hex(FILE *fp, long line){
    char arg [ARG_LENGTH + 1];
    get_arg(fp, line, arg);

    uint32_t tmp = 0;
    sscanf(arg, "%08x", &tmp);

    return tmp;
}


/** 
 * Ricava l'indice dell'ultimo blocco stampato su un file di testo.
 *
 * @param[in] file_path stringa contenente la directory e il file in cui leggere
 * 
 * @return indice in formato uint32_t
 */

uint32_t get_prev_index(const char *file_path){
    //apertura file
    FILE *fp_chain; //creazione puntatore al file
    fp_chain = fopen(file_path, "r");  //apertura file in lettura

    if (fp_chain == NULL){  //controllo se l'apertura ha avuto esito positivo
        printf("Error: can't open %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    //posizionamento all'inizio del file
    fseek(fp_chain, 0L, SEEK_END);
    if (!ftell(fp_chain))   //controllo se il file è vuoto
        return 0;

    uint32_t count_transaction = get_arg_uint32Dec(fp_chain, -2);
    
    return get_arg_uint32Dec(fp_chain, (long)(-2 - NUM_TRANS_LINE * (int)count_transaction - 1 - DIM_HASH - 2));
}


/** 
 * Ricava l'hash dell'ultimo blocco stampato su un file di testo.
 * 
 * @param[out] hash vettore in cui inserire l'hash letto dal blocco precedente
 *
 * @param[in] file_path stringa contenente la directory e il file in cui leggere
 */

void get_prev_hash(uint32_t *hash, const char *file_path){
    //apertura file
    FILE *fp_chain; //creazione puntatore al file
    fp_chain = fopen(file_path, "r");  //apertura file in lettura

    if (fp_chain == NULL){  //controllo se l'apertura ha avuto esito positivo
        printf("Error: can't open %s\n", file_path);
        exit(EXIT_FAILURE);
    }

    //posizionamento all'inizio del file
    fseek(fp_chain, 0L, SEEK_END);
    if (!ftell(fp_chain))   //controllo se il file è vuoto
        return;

    uint32_t count_transaction = get_arg_uint32Dec(fp_chain, -2);

    for (int i = 0; i < DIM_HASH; i++)
        hash [i] = get_arg_uint32Hex(fp_chain, (long)(-2 - NUM_TRANS_LINE * (int)count_transaction - 1 - DIM_HASH + i));
}