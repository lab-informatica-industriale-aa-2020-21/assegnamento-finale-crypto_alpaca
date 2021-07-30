// File.c per la creazione di una nuova blockchain:

#include "block.h"
#include "chain.h"
#include<stdint.h>

/*  Funzione per la creazione di una nuova blockchain:
    Viene passata il puntatore alla lista delle transazioni che devono essere inserire nel blocco;
    Viene creato un nuovo blocco richiamando la funzione 'new_block';
    Successivamente il blocco viene minato attraverso l'esecuzione della funzione 'mine';
*/
void add_block(block *head_block, trans *head_trans){
    
    // Creazione del blocco:
    new_block(const block *head_block, const trans *first_trans);
    
    // Il blocco creato viene minato 
    mine(block *const block_to_mine, uint *const count_index);

}

/*  Creazione di una nuova blockchain (di una catena )
    Avendo più linee di 'catene' (blockchain) è necessaria una funzione che ne crei una nuova*/ 
chain *new_chain(const chain *head_chain, const block )

block *new_block(const block *head_block){

    *head_block = NULL;

    // Richiamo della funzione per aggiungere un nuovo blocco alla catena:
    add_block(block *head_block, trans *head_trans);
}

