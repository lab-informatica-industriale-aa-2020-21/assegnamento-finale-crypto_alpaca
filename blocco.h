/*  Di seguito viene riportato l'header file per la gestione dei blocchi 
    di transazione da inserire nella blockchain */

// Struttura del blocco di transazioni:
//Aggiunto messaggio di prova 1
//Aggiunto ulteriore commento di prova 2
#ifndef blocco_h
#define blocco_h

typedef struct
{
    uint32_t *prev_hash;            // puntatore a 'hash' del blocco precedente
    uint32_t hash[6];               // 'hash' del blocco corrente  
    uint32_t nonce;                 
    trans *head;                    // puntatore alla testa della lista 
    time_t creation_time;           // tempo per la creazione del blocco 
    uint index;                     // indice numerico del blocco
} block;

// Funzione per la creazione di uno nuovo blocco di transazioni della blockchain
block *new_block( block *tail, trans *head);

#endif
