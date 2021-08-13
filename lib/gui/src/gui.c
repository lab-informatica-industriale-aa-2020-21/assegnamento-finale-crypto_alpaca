#include <ncurses.h>
#include <stdint.h>

#include "gui.h"

uint8_t selection_box(int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1]){
    char item[MAX_STR_LEN + 1];
    int input = 0;
    uint8_t tmp = 0;
    
    initscr();
    WINDOW *w;
    w = newwin(MAX_ROWS, MAX_COLS, 0, 0);
    box(w, 0, 0);

    for (int i = 0; i < n_items; i++){
        if (i == 0)
            wattron(w, A_STANDOUT);
        else
            wattroff(w, A_STANDOUT);

        sprintf(item, "%-*s", MAX_STR_LEN + 2, selections[i]);
        mvwprintw(w, i + 1, 2, "%s", item);
    }

    wrefresh(w);

    noecho();
    keypad(w, TRUE);
    curs_set(0);


    while((input = wgetch(w)) != '\n'){
        sprintf(item, "%-*s", MAX_STR_LEN + 2, selections[tmp]);
        mvwprintw(w, tmp + 1, 2, "%s", item);
        wattron(w, A_STANDOUT);

        switch(input){
            case KEY_UP:
                tmp--;
                tmp = (tmp < 0) ? (n_items - 1) : tmp;
                break;
        
            case KEY_DOWN:
                i++;
                tmp = (tmp > (n_items - 1)) ? 0 : tmp;
                break;
        }

        sprintf(item, "%-*s", MAX_STR_LEN + 2, selections[tmp]);
        mvwprintw(w, tmp + 1, 2, "%s", item);
        wattroff(w, A_STANDOUT);
    }

    delwin(w);
    endwin();

    return tmp;
}