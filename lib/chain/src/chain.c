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
        head_chain -> next_chain = *tmp_chain;
    }

    tmp_chain -> first_block = NULL;            
    tmp_chain -> head_block = NULL;              
    tmp_chain -> num_block = 0;  
}


/*Funzione: add_block
* ------------------------------------------------------------------------------------------------------
* Viene passata il puntatore alla lista delle transazioni che devono essere inserire nel blocco;
* Viene creato un nuovo blocco richiamando la funzione 'new_block';
* Successivamente il blocco viene minato attraverso l'esecuzione della funzione 'mine';
* ------------------------------------------------------------------------------------------------------
*  
* *head_block: puntatore al blocco di testa (ultimo blocco aggiunto)
* *head_trans: puntatore alla transazione di testa (ultima transazione creata)
*
*/
void add_block(block *const head_block, const trans *head_trans){
    
    // Creazione del blocco:
    block *block_to_mine =  new_block(head_block, head_block -> first_trans);
    
    // Il blocco creato viene minato (operazione di mining) 
    mine(block_to_mine);

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
        trans *next_free_trans = (chain -> next_free_block) -> first_trans;
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



