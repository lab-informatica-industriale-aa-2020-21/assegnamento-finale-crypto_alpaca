// Di seguito viene riportato l'header file per la gestione della transazione

// Definizione della struttura della transazione

#ifndef transaction_h
#define transaction_h

#include<stdio.h>
#include<stdbool.h>

typedef struct 
{
    uint32_t sender;        // chiave pubblica del mittente 
    uint32_t receiver;      // chiave pubblica del destinatario
    uint32_t amount;        // importo della transazione
    trans *next;            // puntatore alla transazione successiva
} trans;

// Funzioni utili per la gestione delle transazioni:

// Creazione di una nuova transazione
trans *new_trans(int32_t public_key_sender, int32_t public_key_receiver, int32_t amount_transaction, int &count )

// Aggiunta transazione alla lista di transazioni 
<<<<<<< HEAD
bool add_trans(trans *head, trans *new_node);

// Conteggio numero di transazioni aggiunte 
uint get_count_trans();
=======
void add_trans(const uint32_t sender,const uint32_t receiver, const uint32_t amount, trans *head, int &count);
>>>>>>> a16df61194ea4309c71a3e7373c3eefe21eededa

#endif 