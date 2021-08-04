/* File.c per le funzioni: 
    - creazione di un nuovo blocco di transazioni; 
    - operazione di 'mining' dei blocchi; 
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#include "block.h"

#define TIMEINFO_STR_LEN 20

// Dichiarazioni delle variabili:
uint32_t count_index = 0;
block *head_block = NULL;

// Funzione per la creazione di uno nuovo blocco di transazioni della blockchain:
block *new_block(block *const head_block, const trans *first_trans){

    block *tmp_block;
    tmp_block = malloc(sizeof(block));

    // Controllo funzionamento della malloc()
    if(tmp_block == NULL){
        printf("Error: malloc() failure");
        exit(EXIT_FAILURE);
    }

    tmp_block -> prev_hash = head_block -> hash;      // assegnazione dell'hash del blocco precedente al prev_hash del blocco attuale      
    tmp_block -> nonce = 0;     //valore temporaneo di nonce
    tmp_block -> first_trans = first_trans;
    tmp_block -> num_trans = get_count_trans();
    tmp_block -> index = 0;     //valore temporaneo di index
    // hash = (richiamo funzione di calcolo dell'hash)    //assegnazione hash temporaneo
    
    return tmp_block;
}

void mine(block *const block_to_mine, const uint32_t *count_index){

    while (block_to_mine -> hash[0] > MAX_VALID_FIRST_HASH_ELEMENT){     //controllo se i primi 4 bit (del primo uint_32) sono diversi da 0
        block_to_mine -> nonce ++;              // incremento del valore di 'nonce' fino a trovare quello corretto, in base alle condizione di hash scelte
        // block_to_mine -> hash = funzione calcolo hash(char *prevhash, int trans_din_bit, char *trans, char *nonce); tutto nello heap
    }

    block_to_mine -> creation_time = time(NULL);      // info mm/gg/yy (data) - h:min:sec (ora) sulla creazione del nuovo blocco
    // !!ATTENZIONE!! -> quando andremo a stampare l'indice creation_time del blocco sarà necessario usare la funzione 'ctime()' per convertire il contenuto della struttura time in stringa  
    count_index ++;                                        // conteggio del numero di blocchi minati
    block_to_mine -> index = count_index;                  // inserisco il numero corrispondente al blocco 
}

bool get_str_creation_time(time_t creation_time, char *string) {
    struct tm *timeinfo;

    timeinfo = localtime(&creation_time);
    if(strftime(string, TIMEINFO_STR_LEN, "%F %T", timeinfo) == 0)
	return false;
    else
	return true;
}
