// Di seguito viene riportato l'header file per la gestione della transazione

// Definizione della struttura della struttura della transazione

#ifndef transaction_h
#define transaction_h

typedef struct 
{
    uint32_t sender;        // chiave pubblica del mittente 
    uint32_t receiver;      // chiave pubblica del destinatario
    uint32_t amount;            // importo della transazione
    trans *next;            // puntatore alla transazione successiva
} trans;

// Funzioni utili per la gestione delle transazioni:

// Creazione di una nuova transazione
trans *new_trans(sender, receiver, amount);

// Aggiunta transazione alla lista di transazioni 
bool add_trans(trans *head, trans *new_node);

// Conteggio numero di transazioni aggiunte 
uint count_node(trans *head);


#endif 