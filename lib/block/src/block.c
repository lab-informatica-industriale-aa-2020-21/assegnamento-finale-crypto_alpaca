/* -------------------------------------------------------------------------
*    File.c per le funzioni: 
*    - creazione di un nuovo blocco di transazioni; 
*    - operazione di 'mining' dei blocchi; 
   --------------------------------------------------------------------------*/ 

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <stdint.h>

#include "transaction.h"
#include "block.h"
#include "chain.h"
#include "hash.h"
#include "format_string.h"


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
    if (tmp_block == NULL){
        printf("Error: malloc() failure");
        exit(EXIT_FAILURE);
    }

    if (head_block == NULL){
        tmp_block -> count_block = 0;
        tmp_block -> prev_hash = NULL;
    }
    else{
        tmp_block -> count_block = head_block -> count_block +1;
        tmp_block -> prev_hash = head_block -> hash;
    }
    
    *tmp_block -> hash = 0xFFFFFFFF;
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
*/
void mine(chain *const chain_to_mine){
    char trans_str [DATA_TRANS * HEX_NUMB_LENGTH * (chain_to_mine -> head_block) -> num_trans + 1];
    format_data_for_hash(chain_to_mine -> head_block, trans_str);

    while ((chain_to_mine -> head_block) -> hash[0] > MAX_VALID_FIRST_HASH_ELEMENT){     //controllo se i primi 4 bit (del primo uint_32) sono diversi da 0
        (chain_to_mine -> head_block) -> nonce ++;          // incremento del valore di 'nonce' fino a trovare quello corretto, in base alle condizione di hash scelte
        //hash = funzione calcolo hash((chain -> head_block) -> prev_hash, ((chain -> head_block) -> num_trans) * BIT_PER_TRANS, trans_str, (chain -> head_block) -> nonce);
    }

    (chain_to_mine -> head_block) -> creation_time = time(NULL);      // info mm/gg/yy (data) - h:min:sec (ora) sulla creazione del nuovo blocco
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