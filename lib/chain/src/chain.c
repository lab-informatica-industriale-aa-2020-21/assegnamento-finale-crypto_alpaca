// File.c per la creazione di una nuova blockchain:

#include "block.h"
#include "chain.h"
#include "transaction.h"
#include <stdint.h>

/*  Funzione per la creazione di una nuova blockchain:
    Viene passata il puntatore alla lista delle transazioni che devono essere inserire nel blocco;
    Viene creato un nuovo blocco richiamando la funzione 'new_block';
    Successivamente il blocco viene minato attraverso l'esecuzione della funzione 'mine';
*/
void add_block(block *const head_block, const trans *head_trans){
    
    // Creazione del blocco:
    block *block_to_mine =  new_block(head_block, head_block -> first_trans);
    
    // Il blocco creato viene minato 
    mine(block_to_mine, &count_index);

}

/*  Creazione di una nuova blockchain (di una catena )
    Avendo più linee di 'catene' (blockchain) è necessaria una funzione che ne crei una nuova*/ 
chain *new_chain(const chain *head_chain)
{
    head_block = NULL;
    // gestione della testa della head_chain (aggiungere)
}

// Funzione per la creazione di un nuovo blocco della catena:
block *new_block(block *const head_block, const trans *head_trans)
{

    // Richiamo della funzione per aggiungere un nuovo blocco alla catena:
    add_block(head_block, head_trans);
}

