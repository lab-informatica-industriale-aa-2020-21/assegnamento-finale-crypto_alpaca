/*===========================================================================*/
/**
 * @file gui.h
 * @brief Header della libreria per la GUI.
*/
/*===========================================================================*/


/*!
 * @def MAX_ROWS
 * @brief Numero masssimo di righe del terminale.
 * 
 * La macro definisce la grandezza della schermata del terminale
 * insieme alla macro MAX_COLS.
*/

/*!
 * @def MAX_COLS
 * @brief Numero masssimo di colonne del terminale.
 * 
 * La macro definisce la grandezza della schermata del terminale
 * insieme alla macro MAX_ROWS.
*/

/*!
 * @def MAX_STR_LEN
 * @brief Lungheza massima di una stringa.
 * 
 * La macro definisce la lunghezza massima di una stringa
 * da stampare in una finestra di MAX_ROWS * MAX_COLS.
*/

/*!
 * @def MAX_ITEMS
 * @brief Massimo numero di elementi in una finestra.
 * 
 * La macro definisce il massimo numero di elementi
 * da stampare in una finestra di MAX_ROWS * MAX_COLS.
*/

/*!
 * @def UNUSABLE_ROWS
 * @brief Numero di righe non utilizzabili dall'alto.
 * 
 * La macro definisce il numero di righe a partire dall'alto
 * della finestra che sono occupate a eventuali margini e titoli.
*/

/*!
 * @def UNAVAILABLE
 * @brief Definizione descrizione elementi non disponibili.
 * 
 * La macro definisce la stringa contenente la descrizione degli
 * elementi non selezionabili dall'utente.
*/

/*!
 * @def INPUT
 * @brief Definizione descrizione elementi con input 'uint'.
 * 
 * La macro definisce la stringa contenente la descrizione degli
 * elementi con input 'uint'.
*/

/*!
 * @def BLOCK_LINES
 * @brief Numero di righe per la stampa dell'header di un blocco.
 * 
 * La macro definisce il numero di righe necessarie alla stampa
 * delle informazioni di un blocco.
*/

/*!
 * @def MINE_ROWS
 * @brief Righe della schermata 'mine'.
 * 
 * La macro definisce il numero di righe utilizzate
 * per generare la grafica ascii della schermata di caricamento
 * visualizzata durante l'operazione di 'mine'.
*/

/*!
 * @def MAX_STR_LEN_MINE
 * @brief Lunghezza massima delle stringhe schermata 'mine'.
 * 
 * La macro definisce la lunghezza massima delle stringhe utilizzate
 * per generare la grafica ascii della schermata di caricamento
 * visualizzata durante l'operazione di 'mine'.
*/

/*!
 * @def TRANS_ROWS
 * @brief Numero di righe di una schermata di input transazione.
 * 
 * La macro definisce il numero di righe necessarie per la
 * schermata che permette l'input di transazioni manuali.
*/

/*!
 * @def SENDER
 * @brief stringa da stampare alla vice di inserimento 'sender'.
 * 
 * La macro definisce la stringa che verrà sampata sulla selezione
 * dove sarà possibile inserire la chiave pubblica di 'sender'.
*/

/*!
 * @def RECEIVER
 * @brief stringa da stampare alla voce di inserimento 'receiver'.
 * 
 * La macro definisce la stringa che verrà sampata sulla selezione
 * dove sarà possibile inserire la chiave pubblica di 'receiver'.
*/

/*!
 * @def AMOUNT
 * @brief stringa da stampare alla voce di inserimento 'amount'.
 * 
 * La macro definisce la stringa che verrà sampata sulla selezione
 * dove sarà possibile inserire il valore di 'amount'.
*/

/*!
 * @def MAX_TRANS_TO_ADD
 * @brief numero massimo di transazioni da aggiungere.
 * 
 * La macro definisce il numero massimo di transazioni che è
 * possibile aggiungere ad un blocco.
*/

/*!
 * @def TITLE_COLOR
 * @brief Intero di riverimento per 'COLOR_PAIR()' del titolo.
 * 
 * La macro definisce l'intero di riferimeno con cui poi sarà
 * possibile, attraverso l'oggetto 'COLOR_PAIR()' di 'ncurses'
 * richiamare le impostazioni di colore del titolo.
*/

/*!
 * @def QUIT_COLOR
 * @brief Intero di riverimento per 'COLOR_PAIR()' della selezione 'QUIT'.
 * 
 * La macro definisce l'intero di riferimeno con cui poi sarà
 * possibile, attraverso l'oggetto 'COLOR_PAIR()' di 'ncurses'
 * richiamare le impostazioni di colore della selezione 'QUIT'.
*/

/*!
 * @def INVISIBLE_COLOR
 * @brief Intero di riverimento per 'COLOR_PAIR()' delle selezioni
 * non selezionabili.
 * 
 * La macro definisce l'intero di riferimeno con cui poi sarà
 * possibile, attraverso l'oggetto 'COLOR_PAIR()' di 'ncurses'
 * richiamare le impostazioni di colore delle selezioni non
 * selezionabili.
*/

/*!
 * @def MINED_COLOR
 * @brief Intero di riverimento per 'COLOR_PAIR()' del numero
 * di hash 'minato'.
 * 
 * La macro definisce l'intero di riferimeno con cui poi sarà
 * possibile, attraverso l'oggetto 'COLOR_PAIR()' di 'ncurses'
 * richiamare le impostazioni di colore del numero di hash 'minato'.
*/

/*!
 * @def UNMINED_COLOR
 * @brief Intero di riverimento per 'COLOR_PAIR()' del numero
 * di hash non 'minato'.
 * 
 * La macro definisce l'intero di riferimeno con cui poi sarà
 * possibile, attraverso l'oggetto 'COLOR_PAIR()' di 'ncurses'
 * richiamare le impostazioni di colore del numero di hash
 * non 'minato'.
*/

#ifndef GUI_H
#define GUI_H

#include <ncurses.h>
#include <blockchain.h>
#include <stdint.h>


//costanti
#define MAX_ROWS 24
#define MAX_COLS 80
#define MAX_STR_LEN (MAX_COLS - 4)
#define MAX_ITEMS (MAX_ROWS - 2 - 3)
#define UNUSABLE_ROWS 3
#define UNAVAILABLE "(unavailable!)"
#define INPUT "Press space..."
#define BLOCK_LINES 11
#define MINE_ROWS 11
#define MAX_STR_LEN_MINE 30
#define TRANS_ROWS 4
#define SENDER "Sender (DEC):"
#define RECEIVER "Receiver (DEC):"
#define AMOUNT "Amount (DEC):"

#define MAX_TRANS_TO_ADD 5000000

//colori
#define TITLE_COLOR 1
#define QUIT_COLOR 2
#define INVISIBLE_COLOR 3
#define MINED_COLOR 4
#define UNMINED_COLOR 5

/*
 * colori disponibili:
 * COLOR_BLACK
 * COLOR_RED
 * COLOR_GREEN
 * COLOR_YELLOW
 * COLOR_BLUE
 * COLOR_MAGENTA
 * COLOR_CYAN
 * COLOR_WHITE
 */


//funzioni esterne

int selection_box(const char *title, const int num_items,
                char selections [MAX_ITEMS][MAX_STR_LEN + 1],
                const int input_index, uint32_t * const input_uint,
                const int num_unselect, ...);

int transaction_box(const char *title, uint32_t * const sender,
                uint32_t * const receiver, uint32_t * const amount);

void welcome_box(void);

void block_box(const char *title, const block *block_to_print);

void title_box(const char *title, const int num_rows,
                char descriptions [MAX_ITEMS][MAX_STR_LEN + 1]);

void mining_box(WINDOW *w);


//funzioni interne

int saturate(const int value, const int max_value);

WINDOW *new_window(void);

void set_colors(void);

void keyboard_input(WINDOW *w, int * const input, int * const tmp,
                const int n_items, const int input_index,
                uint32_t * const input_uint, char * const str_input,
                const int *invisible);

void keyboard_trans_input(WINDOW *w, int * const input, int * const tmp,
                uint32_t * const sender, uint32_t * const receiver,
                uint32_t * const amount, char * const str_sender,
                char * const str_receiver, char * const str_amount);

void print_selection(WINDOW *w, const int * tmp, const int n_items,
                const int input_index, const char *str_input,
                char selections [MAX_ITEMS][MAX_STR_LEN + 1]);

void print_transaction(WINDOW *w, const int *tmp, const char *str_sender,
                const char *str_receiver, const char *str_amount,
                char selections [MAX_ITEMS][MAX_STR_LEN + 1]);

void print_selection_box(WINDOW *w, int * const tmp, const char *title,
                const int n_items,
                char selections [MAX_ITEMS][MAX_STR_LEN + 1],
                const int input_index, const int *invisible);

void print_transaction_box(WINDOW *w, const char *title,
                char selections [MAX_ITEMS][MAX_STR_LEN + 1]);

void user_selection(WINDOW *w, int * const tmp, const int n_items,
                char selections [MAX_ITEMS][MAX_STR_LEN + 1],
                const int input_index, uint32_t * const input_uint,
                const int *invisible);

void user_trans_input(WINDOW *w, int * const tmp,
                char selections [MAX_ITEMS][MAX_STR_LEN + 1],
                uint32_t * const sender, uint32_t * const receiver,
                uint32_t * const amount);



//Funzioni menu applicazione

void print_menu(chain *chain_to_edit);

void print_manual_menu(chain *chain_to_edit,
                unsigned int *const trans_counter);

void print_automatic_menu(chain *chain_to_edit,
                unsigned int *const trans_counter);

void print_exit_warning(chain *chain_to_free,
                const unsigned int trans_counter);

int print_new_trans_menu(uint32_t *const sender, uint32_t *const receiver,
                uint32_t *const amount);

void make_random_trans(chain *chain_to_edit, const int num_trans);

uint32_t get_random_number(uint32_t lower, uint32_t upper);

void clear_parameters(uint32_t *sender, uint32_t *receiver, uint32_t *amount);

#endif