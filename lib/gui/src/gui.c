#include <ncurses.h>
#include <stdint.h>

#include "gui.h"

int selection_box(char *title,int num_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1]){
    char item[MAX_STR_LEN + 1];
    int n_items;
    int input = 0;
    int tmp = 0;

    //controllo num_items entro il limite massimo
    if (num_items > MAX_ITEMS)
        n_items = MAX_ITEMS;
    else
        n_items = num_items;

    //inizializzazione
    initscr();

    //inizializzazione colori
    if (has_colors()){
        start_color();
        init_pair(TITLE_COLOR, COLOR_GREEN, COLOR_BLACK);
    }

    //inizializzazione finestra
    WINDOW *w;
    w = newwin(MAX_ROWS, MAX_COLS, 0, 0);
    box(w, 0, 0);

    //stampa titolo
    wattron(w, A_BOLD | A_UNDERLINE);
    sprintf(item, "%-*s", (int)(sizeof(title) - sizeof(char)), title);
    mvwprintw(w, 1, 2, "%s", item);
    wattrset(w, A_NORMAL);


    //stampa selezioni
    for (int i = 0; i < n_items; i++){
        if (i == 0)
            wattron(w, A_STANDOUT);
        else
            wattroff(w, A_STANDOUT);

        sprintf(item, "%-*s", MAX_STR_LEN, selections[i]);
        mvwprintw(w, i + UNUSABLE_ROWS, 2, "%s", item);
        wattrset(w, A_NORMAL);
    }

    //stampa "QUIT"
    sprintf(item, "%-*s", MAX_STR_LEN, "QUIT");
    mvwprintw(w, MAX_ITEMS + UNUSABLE_ROWS, 2, "%s", item);

    wrefresh(w);

    //impostazioni visualizzazione finestra
    noecho();
    keypad(w, TRUE);
    curs_set(0);

    //ciclo while di selezione
    while((input = wgetch(w)) != '\n'){
        if(tmp != n_items){
            sprintf(item, "%-*s", MAX_STR_LEN, selections[tmp]);
            mvwprintw(w, tmp + UNUSABLE_ROWS, 2, "%s", item);
        }
        else{
            sprintf(item, "%-*s", MAX_STR_LEN, "QUIT");
            mvwprintw(w, MAX_ITEMS + UNUSABLE_ROWS, 2, "%s", item);
        }

        wattron(w, A_STANDOUT);

        switch(input){
            case KEY_UP:
                tmp--;
                tmp = (tmp < 0) ? (n_items) : tmp;
                break;

                case KEY_DOWN:
                    tmp++;
                    tmp = (tmp > (n_items)) ? 0 : tmp;
                    break;
        }

        if(tmp != n_items){
            sprintf(item, "%-*s", MAX_STR_LEN, selections[tmp]);
            mvwprintw(w, tmp + UNUSABLE_ROWS, 2, "%s", item);
        }
        else{
            sprintf(item, "%-*s", MAX_STR_LEN, "QUIT");
            mvwprintw(w, MAX_ITEMS + UNUSABLE_ROWS, 2, "%s", item);
        }

        wattroff(w, A_STANDOUT);
    }

    //chiusura finestra
    delwin(w);
    endwin();

    //return
    if(tmp == n_items)
        return -1;
    else
        return tmp;
}