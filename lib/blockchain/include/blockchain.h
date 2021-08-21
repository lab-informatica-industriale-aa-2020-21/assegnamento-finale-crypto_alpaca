/*===========================================================================*/
/**
 * @file blockchain.h
 * @brief Header del modulo blockchain.
*/
/*===========================================================================*/


/*!
 * @def MAX_VALID_FIRST_HASH_ELEMENT
 * @brief Valore massimo che può assumere il primo elemento dell'hash.
 * 
 * La macro definisce il vincolo dell'hash durante il mining del blocco.
 * Se l'hash del blocco minato ha valore inferiore a quello imposto, ossia
 * ha almeno un certo numero di zeri in serie, allora il blocco è considerato
 * minato.
*/


/*!
 * @def TIMEINFO_STR_LEN
 * @brief Lunghezza della stringa che descrive il tempo di creazione.
 * 
 * La macro definisce la lunghezza della stringa che contiene le informazioni
 * temporali di quando un blocco viene minato e aggiunto alla blockchain.
*/


/*!
 * @def DIM_STR_TRANS
 * @brief Lunghezza della stringa che contiene le info della transazione.
 * 
 * La macro definisce la lunghezza della stringa che contiene le informazioni
 * del mittente, del destinatario e dell'importo della transazione.
*/


/*!
 * @def DIM_STR_HASH
 * @brief Lunghezza della stringa che contiene l'hash.
*/


#ifndef BLOCKCHAIN_H
#define BLOCKCHAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <time.h>


#define MAX_VALID_FIRST_HASH_ELEMENT 0x000FFFFF
#define TIMEINFO_STR_LEN 20
#define DIM_STR_TRANS (3 * HEX_NUMB_LENGTH)
#define DIM_STR_HASH (DIM_HASH * HEX_NUMB_LENGTH)


/**
 * @brief Struttura della Transazione
 * 
 * Nella struttura Transazione sono definiti gli attributi che compongono una
 * transazione elettronica.
 * L'oggetto transazione viene rappresentato come un elemento di una lista
 * concatenata unidirezionale, detta lista delle transazioni.
 */

struct Trans {
    struct Trans *next_trans;       ///< puntatore alla transazione successiva
    uint32_t sender;                ///< chiave pubblica del mittente
    uint32_t receiver;              ///< chiave pubblica del destinatario
    uint32_t amount;                ///< importo della transazione
    uint32_t count_trans;           ///< conteggio del numero di transazioni
};
typedef struct Trans trans;


/**
 * @brief Struttura del Blocco
 * 
 * Nella struttura Blocco vengono definiti gli attributi di un blocco che
 * viene aggiunto alla blockchain.
 * L'oggetto blocco viene rappresentato come un elemento di una lista
 * concatenata unidirezionale, detta lista dei blocchi, che andrà poi a comporre
 * la blockchain.
 */

struct Block {
    struct Block *next_block;       ///< puntatore al blocco successivo
    struct Trans *first_trans;      ///< puntatore alla prima transazione della lista per lettura 
    struct Trans *head_trans;       ///< puntatore alla transazione più recente della lista per scrittura
    uint32_t count_block;           ///< conteggio del numero di blocchi di una chain
    uint32_t *prev_hash;            ///< puntatore all' hash del blocco precedente
    uint32_t hash[8];               ///< hash del blocco corrente
    uint32_t nonce;                 ///< numero di nonce dell blocco
    uint32_t num_trans;             ///< numero di transazioni nel blocco
    time_t creation_time;           ///< tempo per la creazione del blocco
};
typedef struct Block block;


/**
 * @brief Struttura della Blockchain
 * 
 * Nella struttura Chain vengono definiti gli attributi di una blockchain
 * che contiene i blocchi minati volta per volta.
 * L'oggetto blockchain viene rappresentato come un elemento di una lista
 * concatenata unidirezionale, detta lista delle blockchain.
 * Questo tipo di struttura è predisposta per la gestione dei conflitti.
 */

struct Chain {
    struct Chain *next_chain;       ///< puntatore alla chain successiva
    struct Block *first_block;      ///< puntatore al primo blocco della chain
    struct Block *head_block;       ///< puntatore al blocco più recente della chain
    uint32_t num_block;             ///< numero di blocchi inseriti in una chain 
    uint32_t count_chain;           ///< conteggio del numero di chain 
};
typedef struct Chain chain;



trans *new_trans(const uint32_t sender, const uint32_t receiver, const uint32_t amount,
                trans *const head_trans);

chain *new_chain(chain *const head_chain);

block *new_block(block *const head_block);

bool get_str_creation_time(time_t creation_time, char *string);

void input_trans(uint32_t sender, uint32_t receiver, uint32_t amount, chain *in_chain);

void mine(chain *const chain_to_mine);

void free_chain(chain *chain);

#endif
