// File.c per la creazione di una nuova blockchain:

#include "block.h"
#include "chain.h"
#include "transaction.h"
#include <stdint.h>

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

/* Funzione: new_chain
*---------------------------------------------------------------------------------------------------------------
* Creazione di una nuova blockchain.
* Con questa funzione è possibile creare più linee di chain
*---------------------------------------------------------------------------------------------------------------
*
* *new_chain: puntatore alla testa della chain (ultima catena creata)
* 
*/
void *new_chain(chain *head_chain)
{
    head_chain -> head_block = NULL;        // spostamento della testa della catena
    // gestione della testa della head_chain (aggiungere)
}


