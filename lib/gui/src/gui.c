#include <ncurses.h>
#include <stdint.h>

#define MAX_ROWS 24
#define MAX_COLS 80
#define MAX_STR_LEN (MAX_COLS - 6)
#define MAX_ITEMS (MAX_ROWS - 2)


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


    while((ch = wgetch(w)) != '\n'){
        sprintf(item, "%-*s", MAX_STR_LEN + 2, selections[tmp]);
        mvwprintw(w, tmp + 1, 2, "%s", item);
        wattron(w, A_STANDOUT);

        switch(ch){
            case KEY_UP:
                i--;
                i = (i < 0) ? (n_items - 1) : i;
                break;
        
            case KEY_DOWN:
                i++;
                i = (i > (n_items - 1)) ? 0 : i;
                break;
        }

        sprintf(item, "%-*s", MAX_STR_LEN + 2, list[tmp]);
        mvwprintw(w, tmp + 1, 2, "%s", item);
        wattroff(w, A_STANDOUT);
    }

    return tmp;
}