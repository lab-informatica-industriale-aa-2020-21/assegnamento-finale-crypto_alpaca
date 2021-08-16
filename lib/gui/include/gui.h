#ifndef GUI_H
#define GUI_H

#include <ncurses.h>

//costanti
#define MAX_ROWS 24
#define MAX_COLS 80
#define MAX_STR_LEN (MAX_COLS - 4)
#define MAX_ITEMS (MAX_ROWS - 2 - 3)
#define UNUSABLE_ROWS 3
#define MAX_UINT32 4294967295
#define UNAVAILABLE "(unavailable!)"
#define INPUT "Press space..."

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

int saturate(int value, int max_value);

WINDOW *new_window(void);

void set_colors(void);

void keyboard_input(WINDOW *w, int *input, int *tmp, int n_items, int input_index, uint32_t *input_uint, char *str_input, int *invisible);

void print_selection(WINDOW *w, int *tmp, int n_items, int input_index, char *str_input, char selections [MAX_ITEMS][MAX_STR_LEN + 1]);

void print_selection_box(WINDOW *w, int *tmp, char *title, int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int input_index, int *invisible);

void user_selection(WINDOW *w, int *tmp, int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int input_index, uint32_t *input_uint, int *invisible);

int selection_box(char *title, int num_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int input_index, uint32_t *input_uint, int num_unselect, ...);

#endif