#ifndef GUI_H
#define GUI_H

#include <ncurses.h>

#define MAX_ROWS 24
#define MAX_COLS 80
#define MAX_STR_LEN (MAX_COLS - 6)
#define MAX_ITEMS (MAX_ROWS - 2)

int selection_box(int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1]);

#endif