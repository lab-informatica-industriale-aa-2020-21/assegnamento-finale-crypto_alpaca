/**
 * @mainpage Blockchain Demo
 * Questa è la pagina principale del progetto.
 * 
 * 1. Vengono richiamate le funzioni principali per la gestione della GUI.
 * 2. Vengono richiamate le funzioni per la creazione di una o più blockchain.
 * 
 * @authors Andrea Binotto
 * @authors Filippo Toffano
 * @authors Alberto Trabacchin
 * @authors Emanuele Zanoni
 */


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdint.h>

#include "blockchain.h"
#include "file_IO.h"

// Funzioni modalità di inserimento delle funzioni:
void manual_trans(chain *head_chain);
void automatic_trans(chain *head_chain, uint32_t trans_to_generate);

// Funzioni modalità di funzionamento:
void manual_mode(void);
void auto_mode(void);
void end_mode(chain *chain_to_mine);


int main()
{
    // Pulizia del terminale 
    system("clear");
    
    // Dichiarazioni e iniziallizazione delle variabili:
    uint8_t work_type = 0;
    char input_choice;
    uint8_t mine_choice;

    /*------------------------------------------------------------------------------
    *
    * Introduzione al programma implementato e messaggio di benvenuto
    * Interfacciamento con l'utente
    *
    *--------------------------------------------------------------------------------*/ 
    printf("\n\nBenvenuto! \n"
           "Questo programma simula l'algoritmo di gestione di una blockchain"
           "Sei pronto a scoprirlo? Premi ENTER per continuare...  :)\n");
        
    while (getchar()!='\n'){};// attesa di input  'ENTER' da tastiera per continuare l'esecuzione del programma

    do{
        printf("\n\nE' possibile creare le transazioni oppure fare in modo che il programma le crei in automatico.\n"
           "Inserisci:\n"
           "1 -> transazione manuale\n"
           "2 -> transazione automatica\n");

        scanf("%u", &work_type); // lettura scelta di modalità di lavoro 
        
        if(work_type != 1 && work_type != 1){
            printf("\n\nIl valore inserito non è valido!\n"
                    " Inserisci '0' o '1'");
        }
    }
    while(work_type != 1 && work_type != 2);

    insert_trans: // etichetta per tornare alla creazione delle transazioni
    
    if(work_type == 1){
        manual_mode();
    }
    else{
        auto_mode();
    }
    
    
   /*-------------------------------------------------------------------------------
   * Se si decide di terminare il programma, inserendo 'q', i dati creati vengono 
   * salvati utilizzando la funzione save_chain(chain). Successivamente viene 
   * deallocata la memoria occupata dalla chain creata richiamando la funzione 
   * free_chain(chain).
   * E' possibile trovare la stampa dei dati nel file BLOCKCHAIN_TXT   
   *--------------------------------------------------------------------------------*/
    // Richiesta scelta se terminare o continuare il programma 
   do
   {
       while (getchar()!='\n'){};
        printf("\nSi vuole terminare qui in programma?\n"
            "Si inserisca:\n"
            "q -> USCITA/EXIT\n"
            "c -> Continue\n");
        scanf("%c", input_choice);
        // Controllo inserimento carattere corretto per l'uscita o la comtinuazione del programma
        if(input_choice != 'q' && input_choice != 'Q' && input_choice != 'c' && input_choice != 'C'){
            printf("\n\nInserisci un carattere valido tra quelli elencati");
        }
   } while( input_choice != 'q' && input_choice != 'Q' && input_choice == 'c' && input_choice == 'C');
   
    
    if(input_choice == 'q' || input_choice == 'Q'){ // scelta di terminare
       end_mode(chain_1);
    }
    else if(input_choice == 'c' || input_choice == 'C'){ // scelta di continuare
        goto insert_trans; 
    }
}

/*----------------------------------------------------------------------------------
**************************** IMPLEMENTAZIONI FUNZIONI ******************************
------------------------------------------------------------------------------------*/

// Funzione per l'esecuzione del programma manuale
void manual_mode(void){
    // MANUAL MODE
        uint8_t input_choice;
        chain *chain_1 = new_chain(NULL);
        printf("\nSi è scelta la modalità di inserimento manuale\n");
           
        do{
            manual_trans(chain_1); // richiamo funzione per l'inserimento manuale delle transazioni
            while (getchar()!='\n'){};
            printf("\nVuoi aggiungere un'altra transazone? (Y/N)");
            scanf("%c", &input_choice);
            // Controllo inserimento caratteri corretti 
            while(input_choice != 'Y' && input_choice != 'y' && input_choice != 'N' && input_choice != 'n'){
                printf("\nL'inserimento non è valido. \n Inserisci uno tra i caratteri indicati");
                printf("\nVuoi aggiungere un'altra transazone? (Y//N)");
                while (getchar()!='\n'){};
                scanf("%c", &input_choice);
            }

            /*------------------------------------------------------------------------------
            *  Finita la creazione delle transazioni ,esse vengono aggiunte in un blocco.
            *  Successivamente e' possibile scegliere se:
            * 1- il blocco appena creato venga minato e aggiunto alla blockchain;
            * 2- continuare ad aggiungere transazioni alla stesso blocco.
            *-------------------------------------------------------------------------------
            */
            if(input_choice == 'y' || input_choice == 'Y'){
                while (getchar()!='\n'){};
                printf("Vuoi fare il mining del blocco oppure continuare a inserire le transazioni nello stesso blocco?\n"
                        "Inserisci: \n"
                        "1- MINING\n"
                        "2- CONTINUE\n");
                scanf("%u", &mine_choice);

                while(mine_choice != 2 && mine_choice != 1){
                    printf("\nL'inserimento non è valido. \n Inserisci uno tra i caratteri indicati");
                    printf("Inserisci: \n"
                        "1- MINING\n"
                        "2- CONTINUE\n");
                    scanf("%u", &mine_choice);
                };
                if(mine_choice == 1){
                    mine(chain_1);
                }
            }
            
            // Controllo di conclusione di inserimento delle transazioni 
            if(input_choice == 'N' || input_choice == 'n'){
                printf("L'inserimento delle transazioni è terminato!\n"
                        "Ora il programma precede alla creazione e all'inserimento in un blocco e"
                        "infine a svolgere l'operazione di mining di quest'ultimo .");
                mine(chain_1);
            }
        
        }while(input_choice == 'y' || input_choice == 'Y');
}

// Funzione per l'esecuzione del programma automatico
void auto_mode(void){
    // ATOMATIC MODE
        chain *chain_1 = new_chain(NULL);
        uint32_t num_trans_to_generate = 0;
        printf("\nSi è scelta la modalità di inserimento automatica");
        printf("\n Quante transazioni si vogliono generare?"); // Richiesta numero di transazioni che si vogliono generare
        scanf("%u", & num_trans_to_generate);

        // Controllo che il numero di transazioni che si vuole creare sia valido 
        while(num_trans_to_generate <= 0){
            printf("\nIl numero inserito non è valido!"
                    "Si inserisca un valore maggiore di 0");
            printf("\n Quante transazioni si volgiono generare?");
            scanf("%u", &num_trans_to_generate);
        }

        // Richiamo della funzione per la creazione automatica delle transazioni
        automatic_trans(chain_1, num_trans_to_generate);
}

// Funzione per terminare il programma 
void end_mode(chain *chain_to_mine){
    save_chain(chain_1, BLOCKCHAIN_TXT);
    free_chain(chain_1);
    printf("\n\nIl programma termina qui!\n\n");
    return 0; // chiusura dell'esecuzione del programma 
}

/*------------------------------------------------------------------------
* Funzione inserimento transazioni manuale
* Vengono generati in modo casuale gli identificativi di mittente (sender) e 
* e ricevente (receiver) e anche dell'importo (amount) della transazione
*-------------------------------------------------------------------------*/ 
void manual_trans(chain *head_chain)
{
    uint32_t sender, receiver, amount;
    
    printf("\n");
    printf("Inserisci i dati richiesti: \n");
    printf("\nSender (formato DEC_INT): ");
    scanf("%u", &sender);
    printf("\nReceiver (formato DEC_INT): ");
    scanf("%u", &receiver);
    printf("\nImporto della transazione (formato DEC_INT): ");
    scanf("%u", &amount);
    while (getchar()!='\n');
    input_trans(sender, receiver, amount, head_chain); // richiamo funzione per la creazione della transazione
}


/*------------------------------------------------------------------------
* Funzione inserimento transazioni automatico
* Vengono inseriti in maniera casuale gli identificativi del mittente 
* (sender), destinatario (receiver) e dell'importo della transazioni.
* Successivamente questi dati vengono passati alla funzione che si occupa
* della creazione della transazione
*-------------------------------------------------------------------------*/
void automatic_trans(chain *head_chain, uint32_t trans_to_generate)
{
    uint32_t sender, receiver, amount;

    /*--------------------------------------------------------------------
    * Generazione di un numero random da assegnare come indentificativo  
    * al mittente e al destinatario.
    * Il numero max assegnabile corrisponde a 2^32 = 4.294.967.296
    * Eseguendo 4*rand()*rand() il numero max raggiungibile è 4.294.705.156,
    * ovvero 4 * 32767 * 32767 (max numero raggiungibile in c)
    * L'importo può variare tra 1€ e 3276700€ (32767*100)
    * 
    * rand(): funzione che genera numeri random contenuta nella libreria 
    * standard <stdlib.h>
    *---------------------------------------------------------------------*/

    for(uint32_t i = 0; i < trans_to_generate; i++){
        
        sender = 4 * rand() * rand(); // assegnazione identificativo casuale al mittente (sender)
        receiver = 4 * rand() * rand(); // assegnazione identificativo casuale al destinatario (receiver)
        amount = 1 + rand() * 100; // assegnazione di importo (amount) causale

        input_trans(sender, receiver, amount, head_chain); // richiamo funzione per la creazione della transazione
        }
}