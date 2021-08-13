#include <ncurses.h>
#include <string.h>
#include <stdargs.h>

#include "gui.h"

int saturate(int value, int max_value){
    if (value > max_value)
        return max_value;
    else
        return value;
}


void set_colors(void){
    if (has_colors()){
        start_color();
        init_pair(TITLE_COLOR, COLOR_GREEN, COLOR_BLACK);
        init_pair(QUIT_COLOR, COLOR_RED, COLOR_BLACK);
        init_pair(INVISIBLE_COLOR, COLOR_MAGENTA, COLOR_BLACK);
    }
}


void print_selections(WINDOW *w, int *tmp, char *title, int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int *invisible){
    char item [MAX_STR_LEN + 1];

    //stampa titolo
    wattron(w, A_BOLD | A_UNDERLINE | COLOR_PAIR(TITLE_COLOR));
    sprintf(item, "%-*s", (int)(sizeof(title) - sizeof(char)), title);
    mvwprintw(w, 1, 2, "%s", item);
    wattrset(w, A_NORMAL);


    //stampa selezioni
    for (int i = 0; i < n_items; i++){
        if (invisible [i + 1] == 0 && *tmp == -1){
            wattron(w, A_STANDOUT);
            *tmp = i;
        }
        else
            wattroff(w, A_STANDOUT);

        if (invisible [i + 1]){
            wattron(w, COLOR_PAIR(INVISIBLE_COLOR));
            sprintf(item, "%-*s", MAX_STR_LEN - (int)strlen(UNAVAILABLE), selections[i]);
            mvwprintw(w, i + UNUSABLE_ROWS, 2, "%s%s", item, UNAVAILABLE);
        }
        else{
            sprintf(item, "%-*s", MAX_STR_LEN, selections[i]);
            mvwprintw(w, i + UNUSABLE_ROWS, 2, "%s", item);
        }

        wattrset(w, A_NORMAL);
    }

    //stampa "QUIT"
    wattron(w, COLOR_PAIR(QUIT_COLOR));
    sprintf(item, "%-*s", MAX_STR_LEN, "QUIT");
    mvwprintw(w, MAX_ITEMS + UNUSABLE_ROWS, 2, "%s", item);
    wattrset(w, A_NORMAL);

}


void user_selection(WINDOW *w, int *tmp, int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int *invisible){
    char item [MAX_STR_LEN + 1];
    int input = 0;

    noecho();
    keypad(w, TRUE);
    curs_set(0);

    while((input = wgetch(w)) != '\n'){
        if(*tmp != n_items){
            sprintf(item, "%-*s", MAX_STR_LEN, selections[*tmp]);
            mvwprintw(w, *tmp + UNUSABLE_ROWS, 2, "%s", item);
        }
        else{
            wattron(w, COLOR_PAIR(QUIT_COLOR));
            sprintf(item, "%-*s", MAX_STR_LEN, "QUIT");
            mvwprintw(w, MAX_ITEMS + UNUSABLE_ROWS, 2, "%s", item);
            wattroff(w, COLOR_PAIR(QUIT_COLOR));
        }

        wattron(w, A_STANDOUT);

        switch(input){
            case KEY_UP:
                *tmp = *tmp -1;

                while (invisible [*tmp + 1])
                    *tmp = *tmp - 1;

                *tmp = (*tmp < 0) ? n_items : *tmp;

                while (invisible [*tmp + 1])
                    *tmp = *tmp - 1;

                break;

            case KEY_DOWN:
                *tmp = *tmp + 1;

                while (invisible [*tmp + 1])
                    *tmp = *tmp + 1;

                *tmp = (*tmp > n_items) ? 0 : *tmp;

                while (invisible [*tmp + 1])
                    *tmp = *tmp + 1;

                break;
        }

        if(*tmp != n_items){
            sprintf(item, "%-*s", MAX_STR_LEN, selections[*tmp]);
            mvwprintw(w, *tmp + UNUSABLE_ROWS, 2, "%s", item);
        }
        else{
            wattron(w, COLOR_PAIR(QUIT_COLOR));
            sprintf(item, "%-*s", MAX_STR_LEN, "QUIT");
            mvwprintw(w, MAX_ITEMS + UNUSABLE_ROWS, 2, "%s", item);
            wattroff(w, COLOR_PAIR(QUIT_COLOR));
        }

        wattroff(w, A_STANDOUT);
    }
}


int selection_box(char *title, int num_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int num_unselect, ...){
    int invisible [MAX_ITEMS + 2] = {0};
    int tmp = -1;

    int n_items = saturate(num_items, MAX_ITEMS);
    int n_unselect = saturate(num_unselect, MAX_ITEMS - 1);

    //gestione input argomenti variabili
    va_list unselectable;
    va_start(unselectable, num_unselect);
    for (int i = 0; i < n_unselect; i++)
        invisible [va_arg(unselectable, int) + 1] = 1;
    va_end(unselectable);

    //inizializzazione
    initscr();

    //inizializzazione colori
    set_colors();

    //inizializzazione finestra
    WINDOW *w;
    w = newwin(MAX_ROWS, MAX_COLS, 0, 0);
    box(w, 0, 0);

    //stampa tutte le selezioni
    print_selections(w, &tmp, title, num_items, selections, invisible);

    //selezione dell'utente salvata in tmp
    user_selection(w, &tmp, n_items, selections, invisible);

    //chiusura finestra
    delwin(w);
    endwin();

    //return
    if(tmp == n_items)
        return -1;
    else
        return tmp;
}