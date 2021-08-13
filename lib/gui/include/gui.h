#ifndef GUI_H
#define GUI_H

#include <ncurses.h>

#define MAX_ROWS 24
#define MAX_COLS 80
#define MAX_STR_LEN (MAX_COLS - 4)
#define MAX_ITEMS (MAX_ROWS - 2 - 3)
#define UNUSABLE_ROWS 3
#define UNAVAILABLE "(unavailable)"

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

void set_colors(void);

void print_selections(WINDOW *w, int *tmp, char *title, int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int *invisible);

void user_selection(WINDOW *w, int *tmp, int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int *invisible);

int selection_box(char *title, int num_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int num_unselect, ...);

#endif