#include <ncurses.h>
#include <stdint.h>

#include "gui.h"

int selection_box(int num_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1]){
    char item[MAX_STR_LEN + 1];
    int n_items;
    int input = 0;
    int tmp = 0;

    if (num_items > MAX_ITEMS)
        n_items = MAX_ITEMS;
    else
        n_items = num_items;

    initscr();
    WINDOW *w;
    w = newwin(MAX_ROWS, MAX_COLS, 0, 0);
    box(w, 0, 0);

    for (int i = 0; i < n_items; i++){
        if (i == 0)
            wattron(w, A_STANDOUT);
        else
            wattroff(w, A_STANDOUT);

        sprintf(item, "%-*s", MAX_STR_LEN, selections[i]);
        mvwprintw(w, i + 1, 2, "%s", item);
    }

    wrefresh(w);

    noecho();
    keypad(w, TRUE);
    curs_set(0);


    while((input = wgetch(w)) != '\n'){
        sprintf(item, "%-*s", MAX_STR_LEN, selections[tmp]);
        mvwprintw(w, tmp + 1, 2, "%s", item);
        wattron(w, A_STANDOUT);

        switch(input){
            case KEY_UP:
                tmp--;
                tmp = (tmp < 0) ? (n_items - 1) : tmp;
                break;

            case KEY_DOWN:
                tmp++;
                tmp = (tmp > (n_items - 1)) ? 0 : tmp;
                break;
        }

        sprintf(item, "%-*s", MAX_STR_LEN, selections[tmp]);
        mvwprintw(w, tmp + 1, 2, "%s", item);
        wattroff(w, A_STANDOUT);
    }

    delwin(w);
    endwin();

    return tmp;
}