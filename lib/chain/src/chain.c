// File.c per la creazione di una nuova blockchain:

#include "block.h"
#include "chain.h"
#include "transaction.h"

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Funzione: new_chain
*---------------------------------------------------------------------------------------------------------------
* Creazione di una nuova blockchain.
* Con questa funzione è possibile creare più linee di chain
*---------------------------------------------------------------------------------------------------------------
*
* *head_chain: puntatore alla testa della chain (ultima catena creata)
* 
*/
chain *new_chain(chain *const head_chain)
{
    chain *tmp_chain = malloc(sizeof(chain));
    if(tmp_chain == NULL){
        printf("Error: malloc() failure");
        exit(EXIT_FAILURE);
    }
    tmp_chain -> next_chain = NULL; 
          
    if(head_chain == NULL){
        tmp_chain -> count_chain = 0;
    }
    else{
        tmp_chain -> count_chain = head_chain -> count_chain + 1;
        head_chain -> next_chain = tmp_chain;
    }

    tmp_chain -> first_block = NULL;            
    tmp_chain -> head_block = NULL;              
    tmp_chain -> num_block = 0;

    return tmp_chain;
}

/* Funzione: free_chain
* ------------------------------------------------------------------------------------------
* Funzione per deallocare la memoria allocata con malloc() per:
* - transazioni (trans)
* - blocchi (block)
* - catene (chain)
* ------------------------------------------------------------------------------------------
*
* *chain: puntatore alla catena (chain) di cui si vuole deallocare la memoria 
*
*/
void free_chain(chain *chain){
    // Definizioni delle variabili
    trans *tmp_pointer_trans;   // puntatore temporaneo per salvare il puntatore alla transazione successiva
    block *tmp_pointer_block;   // puntatore temporaneo per salvare il puntatore al blocco successivo

    // Blocco successivo di cui deallocare la memoria
    block *next_free_block = chain -> first_block;

    // Ciclo di deallocamento della memoria
    do{
        trans *next_free_trans = (chain -> first_block) -> first_trans;
        do{
            tmp_pointer_trans = next_free_trans -> next_trans;  // salvataggio del puntatore alla successiva transazione
            free(next_free_trans);                              // deallocazione delle memoria
            next_free_trans = tmp_pointer_trans;                // passaggio alla successiva transazione
        }while(next_free_trans != NULL);                        // continuo fin tanto che non ho scorso tutta la lista di transazioni
               
        tmp_pointer_block = next_free_block -> next_block;      // salvataggio del puntatore al successivo blocco 
        free(next_free_block);                                  // deallocazione della memoria occupata dal blocco
        next_free_block = tmp_pointer_block;                    // passaggio al successivo blocco
    }while(next_free_block != NULL );                           // continuo fin tanto che non ho scorso tutta la lista di blocchi
}

