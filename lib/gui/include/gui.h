#ifndef GUI_H
#define GUI_H

#include <ncurses.h>

#define MAX_ROWS 24
#define MAX_COLS 80
#define MAX_STR_LEN (MAX_COLS - 4)
#define MAX_ITEMS (MAX_ROWS - 2 - 3)
#define UNUSABLE_ROWS 3

//colori
#define TITLE_COLOR 1
#define SELECT_COLOR 2
#define NON_SELECT_COLOR 3
#define QUIT_COLOR 4

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

int selection_box(char *title, int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1]);

#endif