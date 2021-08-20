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
#define TRANS_ROWS 3
#define SENDER "Sender (DEC):"
#define RECEIVER "Receiver (DEC):"
#define AMOUNT "Amount (DEC):"

#define MAX_TRANS_TO_ADD 5000000

//colori
#define TITLE_COLOR 1
#define QUIT_COLOR 2
#define INVISIBLE_COLOR 3

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

int selection_box(char *title, int num_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int input_index, uint32_t *input_uint, int num_unselect, ...);

int transaction_box(char *title, uint32_t *sender, uint32_t *receiver, uint32_t *amount);

void block_box(char *title, block block_to_print);

void title_box(char *title, int num_rows, char descriptions [MAX_ITEMS][MAX_STR_LEN + 1]);

void mining_box(void);


//funzioni interne

int saturate(int value, int max_value);

WINDOW *new_window(void);

void set_colors(void);

void keyboard_input(WINDOW *w, int *input, int *tmp, int n_items, int input_index, uint32_t *input_uint, char *str_input, int *invisible);

void keyboard_trans_input(WINDOW *w, int *input, int *tmp, uint32_t *sender, uint32_t *receiver, uint32_t *amount, char *str_sender, char *str_receiver, char *str_amount);

void print_selection(WINDOW *w, int *tmp, int n_items, int input_index, char *str_input, char selections [MAX_ITEMS][MAX_STR_LEN + 1]);

void print_transaction(WINDOW *w, int *tmp, char *str_sender, char *str_receiver, char *str_amount, char selections [MAX_ITEMS][MAX_STR_LEN + 1]);

void print_selection_box(WINDOW *w, int *tmp, char *title, int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int input_index, int *invisible);

void print_transaction_box(WINDOW *w, char *title, char selections [MAX_ITEMS][MAX_STR_LEN + 1]);

void user_selection(WINDOW *w, int *tmp, int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int input_index, uint32_t *input_uint, int *invisible);

void user_trans_input(WINDOW *w, int *tmp, char selections [MAX_ITEMS][MAX_STR_LEN + 1], uint32_t *sender, uint32_t *receiver, uint32_t *amount);



//Funzioni menu applicazione

void print_menu(chain *chain_to_edit);
void print_manual_menu(chain *chain_to_edit, unsigned int *const trans_counter);
void print_automatic_menu(chain *chain_to_edit, unsigned int *const trans_counter);
void print_exit_warning(chain *chain_to_free, const unsigned int trans_counter);
int print_new_trans_menu(uint32_t *const sender, uint32_t *const receiver, uint32_t *const amount);
void make_random_trans(chain *chain_to_edit, const int num_trans);
uint32_t get_random_number(uint32_t lower, uint32_t upper);


#endif