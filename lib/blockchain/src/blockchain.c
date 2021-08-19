/*===========================================================================*/
/**
 * @file blockchain.c
 * @brief File sorgente del modulo blockchain.
 * 
 * Commento modulo blockchain...
 * 
 * @authors Filippo Toffano
 * @authors Emanuele Zanoni
 */
/*===========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>

#include "hash.h"
#include "format_string.h"
#include "file_IO.h"


/**
* Crea una nuova struttura 'trans' vuota; se nel blocco è già presente una lista
* di transazioni, verrà aggiunto un nuovo elemento ad essa, in caso contrario
* verrà creata una nuova lista.
*
* @param[in] sender chiave pubblica del mittente
* @param[in] receiver chiave pubblica del ricevente
* @param[in] amount importo della transazione
* @param[out] head_trans puntatore all' elemento più recente della lista di transazioni
* 
* @return Il puntatore alla nuova transazione creata
*/

trans *new_trans(const uint32_t sender, const uint32_t receiver, const uint32_t amount,
                trans *const head_trans){  
    // Allocazione di memoria per una transazione
    trans *tmp_trans = (trans *) malloc(sizeof(trans));

    // Controllo funzioanmento corretto di malloc():
    if(tmp_trans == NULL){
        printf("Error: malloc() failed");
        exit(EXIT_FAILURE);
    } 

    // Controllo se esiste una lista di transazioni:
    if(head_trans == NULL){
        tmp_trans -> count_trans = 1;
    }

    // Aggiunta di una transazione ad una lista esistente:
    else{
        tmp_trans -> count_trans = head_trans -> count_trans + 1;
        head_trans -> next_trans = tmp_trans;
    }
    
    // Inserimento dati della transazione vuota:
    tmp_trans -> sender = sender;       // inserimento della chiave pubblica del mittente 
    tmp_trans -> receiver = receiver;   // inserimenro della chiave pubblica del ricevente 
    tmp_trans -> amount = amount;       // inserimento dell'importo da trasferire nella transazione
    tmp_trans -> next_trans = NULL;     // puntatore al successivo della lista
    
    return tmp_trans;
}


/**
* Crea una nuova struttura 'block' vuota; se nella catena è già presente una
* lista di blocchi, verrà aggiunto un nuovo elemento ad essa, in caso contrario
* verrà creata una nuova lista. Il blocco creato non è 'minato'.
* 
* @param[in, out] head_block puntatore all' elemento più recente della lista di blocchi
* @return Il puntatore al nuovo blocco creato
*/

block *new_block(block *const head_block){
    // Allocazione di memoria per una transazione:
    block *tmp_block = (block *) malloc(sizeof(block));

    // Controllo funzionamento della malloc():
    if (tmp_block == NULL){
        printf("Error: malloc() failure");
        exit(EXIT_FAILURE);
    }

    // Controllo se esiste una lista di blocchi:
    if (head_block == NULL){
        tmp_block -> count_block = 1;
        tmp_block -> prev_hash = NULL;
    }

    // Aggiunta di un blocco ad una lista esistente:
    else{
        tmp_block -> count_block = head_block -> count_block + 1;
        tmp_block -> prev_hash = head_block -> hash;
        head_block -> next_block = tmp_block;
    }
    
    // Inserimento dati del blocco vuoto:
    *(tmp_block -> hash) = 0xFFFFFFFF;  //inserimeno del primo elemento di hash (non minato)
    for (int i = 1; i < DIM_HASH; i++)
        *(tmp_block -> hash + i) = 0;   //inserimento dei restanti elementi di hash (non minato)
    tmp_block -> nonce = 0;             //inserimento nonce nullo
    tmp_block -> first_trans = NULL;    //inserimento nonce NULL
    tmp_block -> head_trans = NULL;     //inserimento head_trans NULL
    tmp_block -> num_trans = 1;         //inderimento num_trans nullo
    tmp_block -> creation_time = (time_t)(0); //inserimento creation_time provvisoria
    tmp_block -> next_block = NULL;     //inserimento next_block NULL

    return tmp_block;
}


/**
* Crea una nuova struttura 'chain' vuota; se è già presente una lista di catene,
* verrà aggiunto un nuovo elemento ad essa, in caso contrario verrà creata una
* nuova lista.
* 
* @param[out] head_chain puntatore all' elemento più recente della lista di catene
* @return Il puntatore alla nuova catena creata
*
*/

chain *new_chain(chain *const head_chain)
{
    // Allocazione di memoria per una transazione:
    chain *tmp_chain = (chain *) malloc(sizeof(chain));

    // Controllo funzionamento della malloc():
    if(tmp_chain == NULL){
        printf("Error: malloc() failure");
        exit(EXIT_FAILURE);
    } 

    // Controllo se esiste una lista di catene:
    if(head_chain == NULL){
        tmp_chain -> count_chain = 1;
    }

    // Aggiunta di una catena ad una lista esistente:
    else{
        tmp_chain -> count_chain = head_chain -> count_chain + 1;
        head_chain -> next_chain = tmp_chain;
    }

    // Inserimento dati della lisa vuota:
    tmp_chain -> first_block = NULL;    //inserimento first_block NULL
    tmp_chain -> head_block = NULL;     //inserimento head_block NULL
    tmp_chain -> num_block = 1;         //inserimento num_block nullo
    tmp_chain -> next_chain = NULL;     //inserimento next_chain NULL

    return tmp_chain;
}


/**
* Converta la struttura del tempo di creazione di un blocco in una stringa
* leggibile.
* 
* @param[in] creation_time informazioni del tempo di creazione
* @param[out] string puntatore alla stringa in cui trascrivere i dati
* @return True se la stringa è scritta correttamente, False in caso contrario
*/

bool get_str_creation_time(time_t creation_time, char *string) {
    struct tm *timeinfo;

    timeinfo = gmtime(&creation_time);
    if(strftime(string, TIMEINFO_STR_LEN, "%F %T", timeinfo) == 0)
	return false;
    else
	return true;
}


/**
* Funzione per l'inserimento di una nuova transazione in una catena. La funzione
* è in grado di gestire autonomamente la scelta/creazione di un blocco e di una
* lista di transazioni in cui inserire i nuovi dati.
*  
* @param[in] sender chiave pubblica mittente
* @param[in] receiver chiave pubblica ricevente
* @param[in] amount importo transazione
* @param[out] in_chain puntatore alla chain in cui si vuole inserire la transazione
*/

void input_trans(uint32_t sender, uint32_t receiver, uint32_t amount, chain *in_chain){
    // Controllo se la chain è priva di una lista di blocchi:
    if (in_chain -> head_block == NULL){
        in_chain -> first_block = new_block(NULL);
        in_chain -> head_block = in_chain -> first_block;
        (in_chain -> head_block) -> count_block = get_prev_index(BLOCKCHAIN_TXT) + 1;

        // Creazione di una nuova tranzazione nel blocco 'head_block' della chain:
        (in_chain -> head_block) -> head_trans =
            new_trans(sender, receiver, amount, (in_chain -> head_block) -> head_trans);
        (in_chain -> head_block) -> first_trans = (in_chain -> head_block) -> head_trans;
    }

    // Controllo se il blocco più recente della chain è già 'minato':
    else if ((in_chain -> head_block) -> hash [0] <= MAX_VALID_FIRST_HASH_ELEMENT){
        in_chain -> head_block = new_block(in_chain -> head_block);

        // Creazione di una nuova tranzazione nel blocco 'head_block' della chain:
        (in_chain -> head_block) -> head_trans =
            new_trans(sender, receiver, amount, (in_chain -> head_block) -> head_trans);
        (in_chain -> head_block) -> first_trans = (in_chain -> head_block) -> head_trans;
    }

    // Si aggiunge una transazione ad una lista esistente
    else{
        (in_chain -> head_block) -> head_trans =
            new_trans(sender, receiver, amount, (in_chain -> head_block) -> head_trans);
    }

    //copia di parametri utili nelle struct
    (in_chain -> head_block) -> num_trans =
            ((in_chain -> head_block) -> head_trans) -> count_trans;

    in_chain -> num_block = (in_chain -> head_block) -> count_block;
}


/**
* Funzione per il 'mining' di un blocco: individua il blocco da 'minare' in una
* catena e ricava il valore di nonce tale da avere un hash corretto.
* 
* @param[in, out] chain_to_mine puntatore alla chain in cui è presente il blocco
*                               che necessita una operazione di mining
*/

void mine(chain *const chain_to_mine){
    // Formattazione della lista di transazioni in una stringa continua:
    char str_for_hash [DIM_STR_HASH + DIM_STR_TRANS *
                (chain_to_mine -> head_block) -> num_trans + HEX_NUMB_LENGTH + 1];

    format_data_for_hash(chain_to_mine -> head_block, str_for_hash);
    
    char nonce_str [HEX_NUMB_LENGTH + 1];
    uint32_to_stringHex((chain_to_mine -> head_block) -> nonce, nonce_str);
    strcat(str_for_hash, nonce_str);

    // Calcolo del primo hash:
    hash(str_for_hash, (chain_to_mine -> head_block) -> hash);
    
    // Ciclo di 'mine':
        //controllo se i primi 4 bit (del primo uint_32) dell'hash sono diversi da 0
    while ((chain_to_mine -> head_block) -> hash [0] > MAX_VALID_FIRST_HASH_ELEMENT) {
        // incremento del valore di 'nonce' fino a trovare quello corretto, in base alle condizione di hash scelte
        (chain_to_mine -> head_block) -> nonce ++;
        uint32_to_stringHex((chain_to_mine -> head_block) -> nonce, nonce_str);
        str_for_hash [DIM_STR_HASH + DIM_STR_TRANS *
                    (chain_to_mine -> head_block) -> num_trans + 1] = '\0';
        strcat(str_for_hash, nonce_str);

        hash(str_for_hash, (chain_to_mine -> head_block) -> hash);
    }

    (chain_to_mine -> head_block) -> creation_time = time(NULL);      // info mm/gg/yy (data) - h:min:sec (ora) sulla creazione del nuovo blocco
}


/**
* Funzione per deallocare la memoria precedentemente allocata per varie liste:
* - transazioni   (struct Trans)
* - blocchi       (struct Block)
* - catene        (struct Chain)
* 
* @param[out] chain_to_free puntatore alla catena da deallocare
*/

void free_chain(chain *chain_to_free){
    // Definizioni delle variabili:
    trans *tmp_pointer_trans;   // puntatore temporaneo per salvare il puntatore alla transazione successiva
    block *tmp_pointer_block;   // puntatore temporaneo per salvare il puntatore al blocco successivo

    // Blocco da deallocare:
    block *next_free_block = chain_to_free -> first_block;

    // Ciclo di deallocamento della memoria:
    do{
        trans *next_free_trans = next_free_block -> first_trans;
        do{
            tmp_pointer_trans = next_free_trans -> next_trans;  // salvataggio del puntatore alla successiva transazione
            free(next_free_trans);                              // deallocazione delle memoria
            next_free_trans = tmp_pointer_trans;                // passaggio alla successiva transazione
        }while(next_free_trans != NULL);                        // continua fino al termine della lista di transazioni
               
        tmp_pointer_block = next_free_block -> next_block;      // salvataggio del puntatore al successivo blocco 
        free(next_free_block);                                  // deallocazione della memoria occupata dal blocco
        next_free_block = tmp_pointer_block;                    // passaggio al blocco successivo
    }while(next_free_block != NULL );                           // continua fino al termine della lista di blocchi

    free(chain_to_free);
}
