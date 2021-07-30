// Di seguito viene riportato l'header file per la gestione della transazione


#ifndef transaction_h
#define transaction_h

#include<stdbool.h>
#include<stdint.h>

// Definizione della struttura della transazione: 
typedef struct 
{
    uint32_t sender;        // chiave pubblica del mittente 
    uint32_t receiver;      // chiave pubblica del destinatario
    uint32_t amount;        // importo della transazione
    struct trans *next;            // puntatore alla transazione successiva
} trans;

// Funzioni utili per la gestione delle transazioni:

// Creazione di una nuova transazione
trans *new_trans(const int32_t public_key_sender, const int32_t public_key_receiver, const int32_t amount_transaction, int *const count );

// Aggiunta transazione alla lista di transazioni 
void add_trans(const uint32_t sender,const uint32_t receiver, const uint32_t amount, trans *head_trans, int *const count);

// Conteggio numero di transazioni aggiunte 
uint32_t get_count_trans();

// Indirizzo primo elemento della lista
uint32_t *get_first_trans();
#endif 