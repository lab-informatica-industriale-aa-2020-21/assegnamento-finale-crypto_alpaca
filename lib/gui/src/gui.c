#include <ncurses.h>
#include <string.h>


#include "gui.h"
#include "format_string.h"
#include "blockchain.h"


//  !!! IMPORTANTE PER NON PERDERSI! !!!

//funzioni da utilizzare (non interne):
//-selection_box
//-title_box
//-block_box
//-mining_box


/* Funzione: 'mining_box' 
*-------------------------------------------------------------------------------------------
*  Stampa su terminale una schermata di caricamento durante il 'mining'.
*  (La finestra va inizializzata e chiusta direttamene nella funzione 'mine' in
*  'blockchain.h')
*-------------------------------------------------------------------------------------------
* 
* args:         void
* return:       void
*/
void mining_box(void){
    //vengono definiti i comportamenti della finestra agli input
    noecho();
    keypad(w, TRUE);
    curs_set(0);

    //stampa schermata di mining
    char matrix [MINE_ROWS][MAX_STR_LEN_MINE + 1] = {"        ______TT______       ",
                                                     "       /______________\\      ",
                                                     "              ||             ",
                                                     "              ||             ",
                                                     "              ||             ",
                                                     "              ||             ",
                                                     "              ||             ",
                                                     "              \\/             ",
                                                     "              °°            ",
                                                     "                             ",
                                                     "           Mining...         "};
    
    //stampa schermata
    for (int i = 0; i < MINE_ROWS; i++)
        mvwprintw(w, MINE_ROWS/2 + i, MAX_STR_LEN/2 - MAX_STR_LEN_MINE/2 + 2, "%s", matrix [i]);
}


/* Funzione: 'block_box' 
*-------------------------------------------------------------------------------------------
*  Stampa su terminale una schermata con titolo e informazioni di un blocco spacificato
*  negli argomenti; l'hash sarà stampato in verde se il blocco è minato, in rosso se non
*  lo è ancora.
*-------------------------------------------------------------------------------------------
* 
* args:         *title          -> stringa contenente il titlo (dim<MAX_STR_LEN)
*               *block_to_print -< puntatore al blocco da stampare
* return:       void
*/
void block_box(char *title, block block_to_print){
    //inizializzazione matrice con informazioni sul blocco
    char block_matrix [BLOCK_LINES][LINE_LENGTH + 1];
    block_header_matrix (block_to_print, block_matrix);

    //inizializzazione ncurses
    initscr();

    //inizializzazione colori
    set_colors();

    //inizializzazione finestra
    WINDOW *w = new_window();

    //vengono definiti i comportamenti della finestra agli input
    noecho();
    keypad(w, TRUE);
    curs_set(0);

    //stampa titolo
        //attivazione attributi; args: *w, attributi | ...
    wattron(w, A_BOLD | A_UNDERLINE | COLOR_PAIR(TITLE_COLOR));
        //stampa del titolo a schermo
    mvwprintw(w, 1, 2, "%s", title);
        //ripristino attributi normali
    wattrset(w, A_NORMAL);

    //stampa blocco
    for (int i = 0; i < BLOCK_LINES; i++){
        if (i > 1 && i < 10){   //indici delle informazioni di hash
            if (block_to_print -> hash [0] > MAX_VALID_FIRST_HASH_ELEMENT)  //condizione blocco non minato
                wattron(w, COLOR_PAIR(UNMINED_COLOR));
                mvwprintw(w, UNUSABLE_ROWS + i, 2, "%s", block_matrix [i]); //stampa rosso
                wattroff(w, COLOR_PAIR(UNMINED_COLOR));
            else                                                            //condizione blocck minato
                wattron(w, COLOR_PAIR(MINED_COLOR));
                mvwprintw(w, UNUSABLE_ROWS + i, 2, "%s", block_matrix [i]); //stampa verde
                wattroff(w, COLOR_PAIR(MINED_COLOR));
        else
            mvwprintw(w, UNUSABLE_ROWS + i, 2, "%s", block_matrix [i]);     //stampa altre informazioni
    }

    //stampa "Press ENTER"
    mvwprintw(w, MAX_ITEMS + UNUSABLE_ROWS, 2, "%*s", MAX_STR_LEN, "Press ENTER");

    //sttesa input ENTER
    while(wgetch(w) != '\n'){};

    //chiusura finestra
    delwin(w);
    endwin();
}


/* Funzione: 'title_box' 
*-------------------------------------------------------------------------------------------
*  Stampa su terminale una schermata di avvio con titolo e desctrizione.
*-------------------------------------------------------------------------------------------
* 
* args:         *title          -> stringa contenente il titlo (dim<MAX_STR_LEN)
*               num_rows        -> numero di righe della descrizione
*               descriptions    -> matrice di stringhe contenente le righe della
*                                  descrizione
* return:       void
*/
void title_box(char*title, int num_rows, char descriptions [MAX_ITEMS][MAX_STR_LEN + 1]){
    //saturazione di num_rows entro i limiti
    int n_rows = saturate(num_rows, MAX_ITEMS);

    //inizializzazione ncurses
    initscr();

    //inizializzazione colori
    set_colors();

    //inizializzazione finestra
    WINDOW *w = new_window();

    //vengono definiti i comportamenti della finestra agli input
    noecho();
    keypad(w, TRUE);
    curs_set(0);

    //stampa titolo
        //attivazione attributi; args: *w, attributi | ...
    wattron(w, A_BOLD | A_UNDERLINE | COLOR_PAIR(TITLE_COLOR));
        //stampa del titolo a schermo
    mvwprintw(w, 1, 2, "%s", title);
        //ripristino attributi normali
    wattrset(w, A_NORMAL);

    //stampa descrizione
    for (int i = 0; i < n_rows; i++)
        mvwprintw(w, UNUSABLE_ROWS + i, 2, "%s", descriptions [i]);

    //stampa "Press ENTER"
    mvwprintw(w, MAX_ITEMS + UNUSABLE_ROWS, 2, "%*s", MAX_STR_LEN, "Press ENTER");

    //sttesa input ENTER
    while(wgetch(w) != '\n'){};

    //chiusura finestra
    delwin(w);
    endwin();
}


/* Funzione: 'selection_box' 
*-------------------------------------------------------------------------------------------
*  Formatta su terminale una finestra di selezione, completa di titolo, selezioni, e
*  selezione di uscita 'QUIT'. Ritorna l'indice di selezione (corrispondente a quello
*  della matrice 'selections') e, in caso si selezione 'QUIT', ritorna "-1".
*  Può stampare delle selezioni "non selezionabili" per eventuali schermate in cui sia
*  utile mostrare delle funzioni che si attiveranno nello sviluppo del programma.
*  Se necessario, può implementare una selezione speciale con la possibilità aggiuntiva
*  di inserire un input di tipo 'uint' da tastiera che sarà ritornato con un puntatore.
*
*  Dimensioni massime stringhe:
*  titolo e selezioni "normali" -> MAX_STR_LEN + 1
*  selezioni non disponibili e con input 'uint' -> MAX_STR_LEN - 14 + 1
*
*  Esempio finestra di selezione:
*
*  --------------------------------------------------------------------------------
*  | Titolo:                                                                      |
*  | selezione 1                                                                  | <- return 0
*  | selezione 2                                                                  | <- return 1
*  | non disponibile 1                                             (unavailable!) | <- no return
*  | selezione 3                                                                  | <- return 3
*  | selezione con input 'uint'                                    Press space... | <- return 4 & 'uint'
*  | non disponibile 2                                             (unavailable!) | <- no return
*  | non disponibile 3                                             (unavailable!) | <- no return
*  | selezione 4                                                                  | <- return 7
*  | non disponibile 4                                             (unavailable!) | <- no return
*  |                                                                              |
*  |                                                                              |
*  |                                                                              |
*  |                                                                              |
*  |                                                                              |
*  |                                                                              |
*  |                                                                              |
*  |                                                                              |
*  |                                                                              |
*  |                                                                              |
*  |                                                                              |
*  | QUIT                                                                         | <- return -1
*  --------------------------------------------------------------------------------
*
*-------------------------------------------------------------------------------------------
* 
* args:         *title          -> stringa contenete il titolo della schermata
*               num_items       -> numero delle selezioni TOTALI (comprese le non
*                                  selezionabili e l'eventuale selezione con input, esclusi
*                                  titolo e 'QUIT')
*               *selections     -> puntatore alla matrice contenente le 'num_items'
*                                  selezioni, minori di 'MAX_ITEMS' nel formato di stringa
*                                  (comprese le non selezionabili e l'eventuale selezione
*                                  con input, esclusi titolo e 'QUIT')
*               input_index     -> indice della riga della matrice corrispondente alla
*                                  selezione che necessita di un input 'uint' da tastiera
*                                  (=-1 se non si necessita di tale funzione)
*               *input_uint     -> puntatore in cui viene salvato il numero digitato
*                                  dall'utente (=NULL se non si necessita di tale funzione)
*               num_unselect    -> numero di selezioni che si vogliono rendere "non
*                                  selezionabili"
*               ...             -> indici delle eventuali selezioni "non selezionabili"
*                                  separati da virgole e corrispondenti alle righe della
*                                  matrice 'selections'
* return:       selection_box   -> numero relativo alla selezione dell'utente,
*                                  corrispondente alla riga di indice 'i' della matrice
*                                  'selections'
*/
int selection_box(char *title, int num_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int input_index, uint32_t *input_uint, int num_unselect, ...){
    //vettore inizializzato con tutti "0",
    //saranno "1" solamente gli elementi di indici 'i' corrispondenti alle
    //righe della matrice 'selections' non selezionabili nella schermata.
    int invisible [MAX_ITEMS + 2] = {0};

    //tmp è la variabile che la funzione ritornerà, corrispondente alla
    //selezione fatta a schermo dall'utente.
    //inizializzata a "-1", verà posta a ad un valore '>=0' nel momento
    //in cui verrà stampata la prima selezione "selezionabile".
    //(vedi 'print_selection_box')
    int tmp = -1;

    //se troppo grande, il numero di elementi nella selection_box viene
    //saturato a MAX_ITEMS. Il numero di elementi non selezionabili non
    //può superare il numero totale di elementi.
    int n_items = saturate(num_items, MAX_ITEMS);
    int n_unselect = saturate(num_unselect, n_items);

    //gestione input argomenti variabili
    va_list unselectable;
    va_start(unselectable, num_unselect);
    //viene compilato il vettore 'invisible'
    for (int i = 0; i < n_unselect; i++)
        invisible [va_arg(unselectable, int) + 1] = 1;
        //gli indici del vettore sono 'shiftati' di +1 rispetto
        //agli indici della matrice 'selections' affinche ci sia
        //del "margine" alla testa e alla coda del vettore;
        //se le funzioni successive dovessero accedere all'elemento
        //"-1" o l'elemento "MAX+1", leggerebbero uno '0' sicuramente
    va_end(unselectable);

    //inizializzazione ncurses
    initscr();

    //inizializzazione colori
    set_colors();

    //inizializzazione finestra
    WINDOW *w = new_window();

    //viene stampata la schermata
    print_selection_box(w, &tmp, title, n_items, selections, input_index, invisible);

    //ciclo while che gestisce la selezione dell'utente
    //salva la selezione in 'tmp' e l'intero in input in 'input_uint'
    user_selection(w, &tmp, n_items, selections, input_index, input_uint, invisible);

    //chiusura finestra
    delwin(w);
    endwin();

    //return
    if(tmp == n_items)  //return = -1 in caso di selezione "QUIT"
        return -1;
    else
        return tmp;     //return = indice corrispondente alla riga della matrice 'selections'
}


/* Funzione: 'saturate' 
*-------------------------------------------------------------------------------------------
*  Ritorna il valore inserito solo se esso è contenuto in un limite scelto, se il valore
*  eccede, la funzione ritorna il massimo accettabile.
*-------------------------------------------------------------------------------------------
* 
* args:         value           -> valore da saturare
*               max_value       -> valore di saturazione
* return:       saturate        -> valore saturato
*/
int saturate(int value, int max_value){
    if (value > max_value)
        return max_value;
    else
        return value;
}


/* Funzione: 'new_window' 
*-------------------------------------------------------------------------------------------
*  Crea una finestra della libreria 'ncurses' e ritorna un puntatore ad essa.
*-------------------------------------------------------------------------------------------
* 
* args:         void
* return:       *new_vindow     -> puntatore alla nuova finestra
*/
WINDOW *new_window(void){
    WINDOW *w;      //puntatore WINDOW per il return
    w = newwin(MAX_ROWS, MAX_COLS, 0, 0);       //creazione finestra
    box(w, 0, 0);   //creazione limite esterno visibile della finestra
    wrefresh(w);    //rende visibile il tutto
    return w;
}


/* Funzione: 'set_colors' 
*-------------------------------------------------------------------------------------------
*  Inizializza i 'COLOR_PAIR()' della libreria 'ncurses' se il terminale li supporta,
*  essi vengono poi associati a delle macro richiamabili quando necessario.
*-------------------------------------------------------------------------------------------
* 
* args:         void
* return:       void
*/
void set_colors(void){
    if (has_colors()){  //controllo supporto colori del terminale
        start_color();  //inizializzazione colori libreria 'ncurses'

        //inizializzazione COLOR_PAIR()
        init_pair(TITLE_COLOR, COLOR_GREEN, COLOR_BLACK);   //args: macro per richiamo, colore carattere, colore sfondo
        init_pair(QUIT_COLOR, COLOR_RED, COLOR_BLACK);
        init_pair(INVISIBLE_COLOR, COLOR_MAGENTA, COLOR_BLACK);
        init_pair(MINED_COLOR, COLOR_GREEN, COLOR_BLACK);
        inti_pair(UNMINED_COLOR, COLOR_RED, COLOR_BLACK);
    }
}


/* Funzione: '' 
*-------------------------------------------------------------------------------------------
*  Gestisce l'input da tastiera durante la selezione modificando 'tmp', che corrisponde
*  alla posizione in tempo reale della selezione dell'utente; è in grado di gestire anche
*  gli eventiali elementi non selezionabili.
*  Nel caso sia presente la selezione con possibilità di input 'uint', modifica anche
*  'input_uint' e 'str_input' in base al numero inserito dall'utente.
*-------------------------------------------------------------------------------------------
* 
* args:         *w              -> puntatore ad una finestra precedentemente inizializzata
*               *input          -> puntatore alla variabile 'int' in cui vengono salvati
*                                  gli input da tastiera dell'utente
*               *tmp            -> puntatore a tmp, la variabile che contiene la selezione
*                                  istantanea dell'utente che verra ritornata dalla
*                                  funzione madre 'selection_box' dopo la pessione del
*                                  tasto 'ENTER'
*               n_items         -> numero delle selezioni TOTALI (comprese le non
*                                  selezionabili e l'eventuale selezione con input, esclusi
*                                  titolo e 'QUIT')
*               input_index     -> indice della riga della matrice corrispondente alla
*                                  selezione che necessita di un input 'uint' da tastiera
*                                  (=-1 se non si necessita di tale funzione)
*               *input_uint     -> puntatore in cui viene salvato il numero digitato
*                                  dall'utente (=NULL) se non si necessita di tale funzione
*               *str_input      -> puntatore alla stringa su cui viene formattato l'input
*                                  'uint' dell'utente
*               *invisible      -> puntatore al vettore contenente le informazioni sulle
*                                  selezioni "non selezionabili"; ad ogni stringa di indice
*                                  'i' della matrice 'selections' che si vuole rendere non
*                                  selezionabile (ma visibile) dall'utente corrisponde
*                                  invisible[i+1] = 1 (gli altri elementi sono '0')
*                                  (è spiegato in selection_box perche 'i+1')
* return:       void
*/
void keyboard_input(WINDOW *w, int *input, int *tmp, int n_items, int input_index, uint32_t *input_uint, char *str_input, int *invisible){
    switch(*input){
            case KEY_UP:    //caso freccia su
                *tmp = *tmp -1;         //decremento 'tmp'

                while (invisible [*tmp + 1])
                    *tmp = *tmp - 1;    //gestione elementi non selezionabili

                *tmp = (*tmp < 0) ? n_items : *tmp; //condizione di lista ciclica

                while (invisible [*tmp + 1])
                    *tmp = *tmp - 1;    //gestione elementi non selezionabili

                break;

            case KEY_DOWN:  //caso freccia giù
                *tmp = *tmp + 1;        //incremento 'tmp'

                while (invisible [*tmp + 1])
                    *tmp = *tmp + 1;    //gestione elementi non selezionabili

                *tmp = (*tmp > n_items) ? 0 : *tmp; //condizione di lista ciclica

                while (invisible [*tmp + 1])
                    *tmp = *tmp + 1;    //gestione elementi non selezionabili

                break;

                case ' ':   //caso 'spazio' -> modalità di inserimento 'uint'
                if (*tmp == input_index){
                    //solo se la selezione attuale è sull'elemento con possibilità di input 'uint'
                    mvwprintw(w, *tmp + UNUSABLE_ROWS, MAX_COLS - (int)strlen(INPUT) - 2, "%-*s", (int)sizeof(INPUT) - 1, "type n: ...");
                    wscanw(w, "%u", input_uint);    //input
                    //formattazione di 'input_uint' in str_input
                    sprintf(str_input, "n: %*u", (int)sizeof(INPUT) - 4, *input_uint);
                    break;
                }
                else
                    break;
        }
}


/* Funzione: 'print_selecrion' 
*-------------------------------------------------------------------------------------------
*  Stampa a schermo la selezione di indice 'tmp'. Viene utilizzata nella funzione
*  'user_selection'.
*-------------------------------------------------------------------------------------------
* 
* args:         *w              -> puntatore ad una finestra precedentemente inizializzata
*               *tmp            -> puntatore a tmp, la variabile che contiene la selezione
*                                  istantanea dell'utente che verra ritornata dalla
*                                  funzione madre 'selection_box' dopo la pessione del
*                                  tasto 'ENTER'
*               n_items         -> numero delle selezioni TOTALI (comprese le non
*                                  selezionabili e l'eventuale selezione con input, esclusi
*                                  titolo e 'QUIT')
*               input_index     -> indice della riga della matrice corrispondente alla
*                                  selezione che necessita di un input 'uint' da tastiera
*                                  (=-1 se non si necessita di tale funzione)
*               *str_input      -> puntatore alla stringa su cui viene formattato l'input
*                                  'uint' dell'utente
*               *selections     -> puntatore alla matrice contenente le 'n_items' selezioni,
*                                  minori di 'MAX_ITEMS' nel formato di stringa
*                                  (comprese le non selezionabili e l'eventuale selezione
*                                  con input, esclusi titolo e 'QUIT')
* return:       void
*/
void print_selection(WINDOW *w, int *tmp, int n_items, int input_index, char *str_input, char selections [MAX_ITEMS][MAX_STR_LEN + 1]){
    //stringa temporanea in cui formattare i dati da stampare
    char item [MAX_STR_LEN + 1];
    
    //stampa di una selezione normale
    if(*tmp != n_items && *tmp != input_index){
        sprintf(item, "%-*s", MAX_STR_LEN, selections[*tmp]);
        mvwprintw(w, *tmp + UNUSABLE_ROWS, 2, "%s", item);
    }
    //stampa dell'eventuale selezione con input 'uint'
    else if (*tmp == input_index && *tmp != n_items){
        sprintf(item, "%-*s", MAX_STR_LEN - (int)strlen(INPUT), selections[*tmp]);
        mvwprintw(w, *tmp + UNUSABLE_ROWS, 2, "%s", item);

        mvwprintw(w, *tmp + UNUSABLE_ROWS, MAX_COLS - (int)strlen(INPUT) - 2, "%-s", str_input);
    }
    //stampa di 'QUIT'
    else{
        wattron(w, COLOR_PAIR(QUIT_COLOR));
        sprintf(item, "%-*s", MAX_STR_LEN, "QUIT");
        mvwprintw(w, MAX_ITEMS + UNUSABLE_ROWS, 2, "%s", item);
        wattroff(w, COLOR_PAIR(QUIT_COLOR));
    }
}


/* Funzione: 'print_selection_box' 
*-------------------------------------------------------------------------------------------
*  Stampa a terminale in una finestra in ordine: titolo, selezioni ('QUIT' compreso).
*  Serve per poter leggere la schermata delle selezioni prima che l'utenete inizi ad
*  interagire con il terminale; durante l'interazione la GUI sarà gestita dalla funzione
*  'user_selection'.
*  !! vedere decrizione 'selection_box' !!
*-------------------------------------------------------------------------------------------
* 
* args:         *w              -> puntatore ad una finestra precedentemente inizializzata
*               *title          -> stringa contenete il titolo della schermata
*               n_items         -> numero delle selezioni TOTALI (comprese le non
*                                  selezionabili e l'eventuale selezione con input, esclusi
*                                  titolo e 'QUIT')
*               *selections     -> puntatore alla matrice contenente le 'n_items' selezioni,
*                                  minori di 'MAX_ITEMS' nel formato di stringa
*                                  (comprese le non selezionabili e l'eventuale selezione
*                                  con input, esclusi titolo e 'QUIT')
*               input_index     -> indice della riga della matrice corrispondente alla
*                                  selezione che necessita di un input 'uint' da tastiera
*                                  (=-1 se non si necessita di tale funzione)
*               *invisible      -> puntatore al vettore contenente le informazioni sulle
*                                  selezioni "non selezionabili"; ad ogni stringa di indice
*                                  'i' della matrice 'selections' che si vuole rendere non
*                                  selezionabile (ma visibile) dall'utente corrisponde
*                                  invisible[i+1] = 1 (gli altri elementi sono '0')
*                                  (è spiegato in selection_box perche 'i+1')
* return:       void
*/
void print_selection_box(WINDOW *w, int *tmp, char *title, int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int input_index, int *invisible){
    //stringa temporanea in cui formattare i dati da stampare
    char item [MAX_STR_LEN + 1];

    //stampa titolo
        //attivazione attributi; args: *w, attributi | ...
    wattron(w, A_BOLD | A_UNDERLINE | COLOR_PAIR(TITLE_COLOR));
        //formattazione titolo in 'item' e successiva stampa a schermo
    sprintf(item, "%-*s", (int)(sizeof(title) - sizeof(char)), title);
    mvwprintw(w, 1, 2, "%s", item);
        //ripristino attributi normali
    wattrset(w, A_NORMAL);

    //stampa selezioni
    for (int i = 0; i < n_items; i++){
        //controllo se non ho ancora stampato il primo elemento selezionabile
        if (invisible [i + 1] == 0 && *tmp == -1){
            //imposto l'attributo A_STANDOUT per il primo elemento selezionabile
            wattron(w, A_STANDOUT);
            //tmp viene assegnata ad un valore '>=0' corrispondente al primo
            //elemento selezionabile, ciò è utile affinchè la selezione inizi
            //da un elemento selezionabile (il primo), ma svolge la fuzione
            //anche di 'flag' di avvenuta stampa del primo elemento
            *tmp = i;
        }
        else
            //si rimuove l'attributo A_STANDOUT per i successivi elementi
            wattroff(w, A_STANDOUT);


        if (invisible [i + 1]){
            //si formattano e stampano gli elementi non selezionabili con gli opportuni attributi
            wattron(w, COLOR_PAIR(INVISIBLE_COLOR));
            sprintf(item, "%-*s", MAX_STR_LEN - (int)strlen(UNAVAILABLE), selections[i]);
            mvwprintw(w, i + UNUSABLE_ROWS, 2, "%s%s", item, UNAVAILABLE);
        }
        else if (i == input_index){
            //si formatta e stampa l'eventuale selezione con input 'uint'
            sprintf(item, "%-*s", MAX_STR_LEN - (int)strlen(INPUT), selections[i]);
            mvwprintw(w, i + UNUSABLE_ROWS, 2, "%s", item);

            //si stampa la casella di inserimento 'uint'
            mvwprintw(w, i + UNUSABLE_ROWS, 2 + (int)strlen(item), "%-s", INPUT);
        }
        else{
            //si stampano le selezioni normali
            sprintf(item, "%-*s", MAX_STR_LEN, selections[i]);
            mvwprintw(w, i + UNUSABLE_ROWS, 2, "%s", item);
        }

        //si ripristinano gli attributi
        wattrset(w, A_NORMAL);
    }

    //stampa "QUIT"
    wattron(w, COLOR_PAIR(QUIT_COLOR));     //attributi "QUIT"
    //formattazione e stampa della selezione "QUIT" nell'ultima riga disponibile
    sprintf(item, "%-*s", MAX_STR_LEN, "QUIT");
    mvwprintw(w, MAX_ITEMS + UNUSABLE_ROWS, 2, "%s", item);
    wattrset(w, A_NORMAL);                  //rimozione attributi
}


/* Funzione: 'user_selection' 
*-------------------------------------------------------------------------------------------
*  Gestisce il momento in cui l'utenete ineragisce con il terminale: salva un valore di
*  'tmp' che corrisponde alla slezione dell'utente e gestisce anche l'eventuale input 'uint'
*-------------------------------------------------------------------------------------------
* 
* args:         *w              -> puntatore ad una finestra precedentemente inizializzata
*               *tmp            -> puntatore a tmp, la variabile che contiene la selezione
*                                  istantanea dell'utente che verra ritornata dalla
*                                  funzione madre 'selection_box' dopo la pessione del
*                                  tasto 'ENTER'
*               n_items         -> numero delle selezioni TOTALI (comprese le non
*                                  selezionabili e l'eventuale selezione con input, esclusi
*                                  titolo e 'QUIT')
*               *selections     -> puntatore alla matrice contenente le 'n_items' selezioni,
*                                  minori di 'MAX_ITEMS' nel formato di stringa
*                                  (comprese le non selezionabili e l'eventuale selezione
*                                  con input, esclusi titolo e 'QUIT')
*               input_index     -> indice della riga della matrice corrispondente alla
*                                  selezione che necessita di un input 'uint' da tastiera
*                                  (=-1 se non si necessita di tale funzione)
*               *invisible      -> puntatore al vettore contenente le informazioni sulle
*                                  selezioni "non selezionabili"; ad ogni stringa di indice
*                                  'i' della matrice 'selections' che si vuole rendere non
*                                  selezionabile (ma visibile) dall'utente corrisponde
*                                  invisible[i+1] = 1 (gli altri elementi sono '0')
*                                  (è spiegato in selection_box perche 'i+1')
* return:       void
*/
void user_selection(WINDOW *w, int *tmp, int n_items, char selections [MAX_ITEMS][MAX_STR_LEN + 1], int input_index, uint32_t *input_uint, int *invisible){
    //stringa in cui verrà formattato l''uint' inserito da tastiera
    //per la stampa nella finestra
    char str_input [(int)sizeof(INPUT) + 1] = INPUT;

    //intero in cui vengono salvati gli input da tastiera
    int input = 0;

    //vengono definiti i comportamenti della finestra agli input
    noecho();
    keypad(w, TRUE);
    curs_set(0);

    //ciclo di selezione (input dell'utente)
    //il ciclo termina alla pressione di 'ENTER'
    while((input = wgetch(w)) != '\n'){

        //dopo l'input dell'utente, l'elemento precedentemente selezionato
        //viene ristampato senza l'attributo A_STANDOUT
        print_selection(w, tmp, n_items, input_index, str_input, selections);

        //viene modificata 'tmp' in relazione all'input dell'utente
        //(gestisce anche eventualmente l'input dell''uint')
        keyboard_input(w, &input, tmp, n_items, input_index, input_uint, str_input, invisible);

        //l'elemento ora selezionato viene ristampato con l'attributo A_STANDOUT 
        wattron(w, A_STANDOUT);
        print_selection(w, tmp, n_items, input_index, str_input, selections);
        wattroff(w, A_STANDOUT);
    }
}