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


/*Funzione: new_block
* ---------------------------------------------------------------------------------
* Crea un nuovo blocco di transazioni che successivamente verrà minato;
* ---------------------------------------------------------------------------------
* *head_block: puntatore al blocco di testa (ultimo blocco aggiunto)
* *first: puntatore al primo blocco della chain
*
* return: ritorna il nuovo blocco con i relativi campi (hash, hash precedente, nonce ecc..) inseriti 
*/
block *new_block(block *const head_block){

    block *tmp_block = malloc(sizeof(block));

    // Controllo funzionamento della malloc()
    if(tmp_block == NULL){
        printf("Error: malloc() failure");
        exit(EXIT_FAILURE);
    }

    if( head_block == NULL){
        tmp_block -> count_block = 0;
        tmp_block -> prev_hash = NULL;
    }
    else{
        tmp_block -> count_block = head_block -> count_block +1;
        tmp_block -> prev_hash = head_block -> hash;
    }
    
    &(tmp_block -> hash) = 0xFFFFFFFF;
    tmp_block -> nonce = 0;
    tmp_block -> first_trans = NULL;
    tmp_block -> head_trans = NULL;
    tmp_block -> num_trans = 0;
    tmp_block -> next_block = NULL;

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
