/* -------------------------------------------------------------------------
*    File.c per le funzioni: 
*    - creazione di un nuovo blocco di transazioni; 
*    - operazione di 'mining' dei blocchi; 
   --------------------------------------------------------------------------*/ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "block.h"
#include "hash.h"

#define TIMEINFO_STR_LEN 20 // definizione della lunghezza della stringa per le info temporali di creazione del blocco 

// Dichiarazioni delle variabili:
uint32_t count_index = 0;
block *head_block = NULL;

/*Funzione: new_block
* ---------------------------------------------------------------------------------
* Crea un nuovo blocco di transazioni che successivamente verrà minato;
* ---------------------------------------------------------------------------------
* *head_block: puntatore al blocco di testa (ultimo blocco aggiunto)
* *first: puntatore al primo blocco della chain
*
* return: ritorna il nuovo blocco con i relativi campi (hash, hash precedente, nonce ecc..) inseriti 
*/
block *new_block(block *const head_block, const trans *first){

    block *tmp_block;
    tmp_block = malloc(sizeof(block));

    // Controllo funzionamento della malloc()
    if(tmp_block == NULL){
        printf("Error: malloc() failure");
        exit(EXIT_FAILURE);
    }

    tmp_block -> prev_hash = head_block -> hash;      // assegnazione dell'hash del blocco precedente al prev_hash del blocco attuale
    tmp_block -> nonce = 0;     //valore temporaneo di nonce
    tmp_block -> first_trans = first -> first_trans;
    tmp_block -> count_index = head_block -> count_index + 1;     //valore temporaneo di index
    // hash = (richiamo funzione di calcolo dell'hash)    //assegnazione hash temporaneo

    return tmp_block;
}

/*Funzione: mine
* ---------------------------------------------------------------------------------
* Funzione per il 'mining' di un blocco;
* ---------------------------------------------------------------------------------
* 
* *block_to_mine: puntatore al blocco su cui è necessario eseguire l'operazione di 
*                 mining per poi essere aggiunto alla chain
*
*/
void mine(block *const block_to_mine){

    while (block_to_mine -> hash[0] > MAX_VALID_FIRST_HASH_ELEMENT){     //controllo se i primi 4 bit (del primo uint_32) sono diversi da 0
        block_to_mine -> nonce ++;          // incremento del valore di 'nonce' fino a trovare quello corretto, in base alle condizione di hash scelte
        // block_to_mine -> hash = funzione calcolo hash(char *prevhash, int trans_din_bit, char *trans, char *nonce); tutto nello heap
    }

    block_to_mine -> creation_time = time(NULL);      // info mm/gg/yy (data) - h:min:sec (ora) sulla creazione del nuovo blocco
}


/*Funzione: get_str_creation_time
 *-------------------------------
 *converte la struttura del tempo di creazione di un blocco in una stringa leggibile
 *
 *creation_time: struttura di tipo time_t contenente le info del tempo di creazione
 *string: puntatore alla stringa di caratteri in cui trascrivere i dati temporali
 *
 *return: true se la stringa viene scritta correttamente, altrimenti false
 */

bool get_str_creation_time(time_t creation_time, char *string) {
    struct tm *timeinfo;

    timeinfo = localtime(&creation_time);
    if(strftime(string, TIMEINFO_STR_LEN, "%F %T", timeinfo) == 0)
	return false;
    else
	return true;
}
