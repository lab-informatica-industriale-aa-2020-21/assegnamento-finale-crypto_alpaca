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





