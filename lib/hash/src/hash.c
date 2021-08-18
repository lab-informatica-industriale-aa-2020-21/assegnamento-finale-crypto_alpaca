/*===========================================================================*/
/**
 * @file hash.c
 * @brief File sorgente del modulo SHA-256
 * 
 * Questo modulo permette di implementare la funzione di hash secondo lo 
 * standard SHA256. Data una stringa di dati, restituisce una serie di
 * 256 bit generati da una funzione non invertibile.
 * 
 * @authors Andrea Binotto
 * @authors Alberto Trabacchin
 */
/*===========================================================================*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "hash.h"
#include "string.h"
#include "format_string.h"


/**
 * Esegue l'operazione indicata: ROTR(x,7) XOR ROTR(x,18) XOR SHIFTR(x,3).
 *
 * @param[in] x input su cui eseguire l'operazione
 * 
 * @return Il risultato dell'operazione
 */

unsigned int sigma_0 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,7)) ^ (rotate(x,18)) ^ (x >> 3);
return num;
}


/**
 * Esegue l'operazione indicata: ROTR(x,17) XOR ROTR(x,19) XOR SHIFTR(x,10).
 *
 * @param[in] x input su cui eseguire l'operazione
 * 
 * @return Il risultato dell'operazione
 */

unsigned int sigma_1 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,17)) ^ (rotate(x,19)) ^ (x >> 10);
return num;
}


/**
 * Esegue l'operazione indicata: ROTR(x,2) XOR ROTR(x,13) XOR ROTR(x,22).
 *
 * @param[in] x input su cui eseguire l'operazione
 * 
 * @return Il risultato dell'operazione
 */

unsigned int usigma_0 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,2)) ^ (rotate(x,13)) ^ (rotate(x,22));
return num;
}


/**
 * Esegue l'operazione indicata: ROTR(x,6) XOR ROTR(x,11) XOR ROTR(x,25)
 *
 * @param[in] x input su cui eseguire l'operazione
 * 
 * @return Il risultato dell'operazione
 */

unsigned int usigma_1 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,6)) ^ (rotate(x,11)) ^ (rotate(x,25));
return num;
}


/**
 * Ruota una word uint32, a destra di n_bit posizioni.
 *
 * @param[in] x word a cui applicare la rotazione
 * @param[in] n_bit numero di posizioni di cui eseguire la rotazione
 * 
 * @return La word che contiene l'input ruotato
 */

unsigned int rotate (unsigned int x, int n_bit)
{
    unsigned int num=0;
    num = (x >> n_bit) | (x << (WORD_LEN_BITS-n_bit));
return num;
}


/**
 * Realizza la conversione di un uint32 in forma binaria. Il formato è il
 * BIG ENDIAN, che equivale a porre: vett[0] = MSB, vett[max] = LSB.
 *
 * @param[in] x numero da convertire
 * @param[in] len_vett numero di bit necessari per la conversione da decimale a binario
 * @param[out] vett array in cui salvare la word in formato binario
 */

void decimal_to_bin (unsigned int x, bool *vett, int len_vett)
{ 
    for (int i = 0; i < len_vett; i++){
        vett[i] = 0;
    }
    
    for (int i = len_vett - 1; i >= 0 && x > 0 ; i--){
        vett[i] = x % 2;
        x = x / 2;
    }
}


/**
 * Converte un numero uint32 scritto in forma binaria nella
 * rispettiva versione in forma decimale.
 *
 * @param[in] x array di booleani che contiene i bit del numero da convertire
 * @param[in] len_x lunghezza dei bit della word da convertire
 * 
 * @return Il numero convertito in forma decimale
 */

unsigned int bin_to_decimal (bool *x, int len_x)
{
    unsigned int vett = 0;
        for (int i = len_x - 1; i >= 0; i--){
            vett = vett + x[i] * pow(2, len_x-1-i);
        }
return vett;
}


/**
 * Sceglie i bit di ogni posizione delle word y, z, in base
 * al contenuto della word x.
 *
 * @param[in] x word che determina la scelta
 * @param[in] y prima word sceglibile
 * @param[in] z seconda word sceglibile
 * 
 * @return La word con le scelte effettuate sui singoli bit
 */

unsigned int choice (unsigned int x, unsigned int y, unsigned int z)
{
    bool x_bit[WORD_LEN_BITS] = {0};
    bool y_bit[WORD_LEN_BITS] = {0};
    bool z_bit[WORD_LEN_BITS] = {0};

    bool num[WORD_LEN_BITS] = {0};

    decimal_to_bin(x, x_bit, WORD_LEN_BITS);
    decimal_to_bin(y, y_bit, WORD_LEN_BITS);
    decimal_to_bin(z, z_bit, WORD_LEN_BITS);
 
    for (int i = 0; i < WORD_LEN_BITS; i++)
    {
        if(x_bit[i] == 0)
            num[i] = z_bit[i];
        else   
            num[i] = y_bit[i];
    }

return bin_to_decimal(num, WORD_LEN_BITS);
}


/**
 * Determina quali bit prevalgono in ogni posizione delle word x, y, z.
 *
 * @param[in] x prima word da comparare
 * @param[in] y seconda word da comparare
 * @param[in] z terza word da comparare
 *
 * @return Il risultato delle comparazioni
 */

unsigned int majority (unsigned int x, unsigned int y, unsigned int z)
{
    bool x_bit[WORD_LEN_BITS] = {0};
    bool y_bit[WORD_LEN_BITS] = {0};
    bool z_bit[WORD_LEN_BITS] = {0};

    bool num[WORD_LEN_BITS] = {0};

    decimal_to_bin(x, x_bit, WORD_LEN_BITS);
    decimal_to_bin(y, y_bit, WORD_LEN_BITS);
    decimal_to_bin(z, z_bit, WORD_LEN_BITS);

    for (int i = 0; i < WORD_LEN_BITS; i++){
        if((x_bit[i] && y_bit[i]) || (z_bit[i] && y_bit[i]) || (x_bit[i] && z_bit[i])) 
            num[i] = 1;
        else   
            num[i] = 0;
    }
    
return bin_to_decimal(num, WORD_LEN_BITS);
}


/**
 * Converte un numero uint32 in un vettore di char che ne descrive
 * le singole cifre.
 *
 * @param[in] input numero da analizzare
 *
 * @return Il puntatore ad un array di char che contiene le cifre di input
 * codificate come caratteri ASCII.
 */

char* int_32_to_char(unsigned int input) {
    char *string = malloc((HEX_NUMB_LENGTH + 1) * sizeof(char));
    uint32_to_stringDec(input, string);
    return string;
}


/**
 * Esegue lo shift di un array, a destra di una posizione.
 *
 * @param[in, out] vett array da shiftare
 * @param[in] len lunghezza di vett
 */

void shift_state_reg(unsigned int *vett, int len){
    for (int i = 1; i < len; i++)
        vett[len-i] = vett[len-i-1];
}


/**
 * Copia un array in un altro.
 *
 * @param[in] vett1 array da copiare
 * @param[in] len1 lunghezza di vett1
 * @param[out] vett2: array in cui viene copiato vett1
 * @param[in] len2 lunghezza di vett2
 *
 * @return Uno 0 booleano se la copia avviene correttamente, altrimenti
 * comporta l'uscita dal programma con un errore.
 */

bool copy_vector(const unsigned int *vett1, uint32_t len1, unsigned int *vett2, uint32_t len2){
    if(len1 != len2){
        printf("Error: what to copy? Lengths are different");
        exit(EXIT_FAILURE);
    }
    else   
        for (uint32_t i = 0; i < len2; i++)
            vett2[i] = vett1[i];
return 0;
}


/**
 * Somma due array di lunghezza uguale.
 *
 * @param[in] vett1 primo array da sommare
 * @param[in] len1 lunghezza di vett1
 * @param[in, out] vett2 secondo array da sommare, su cui viene salvato il risultato
 * @param[in] len2 lunghezza di vett2
 *
 * @return Uno 0 booleano se la somma avviene correttamente, altrimenti
 * comporta l'uscita dal programma con un errore.
 */

bool sum_vector(const unsigned int *vett1, int len1, unsigned int *vett2, int len2){
    if(len1 != len2){
        printf("Error: what to sum? Lengths are different");
        exit(EXIT_FAILURE);
    }
    else   
        for (int i = 0; i < len2; i++)
            vett2[i] = vett2[i] + vett1[i];
return 0;
}


/**
 *Alloca la memoria necessaria per creare il blocco di dati
 *
 * @param[in] str_input stringa su cui viene eseguita la funzione di hash
 * @param[out] n_blocks numero di blocchi da allocare in memoria
 * 
 * @return Il puntatore al primo byte del blocco di dati
 */

uint32_t *make_msg_block(const char *const str_input, uint32_t *const n_blocks) {
    uint8_t free_bytes = get_free_bytes(str_input);

    if (free_bytes == 0) 
        *n_blocks = ceil((strlen(str_input) + sizeof(uint32_t) + MSG_INFO_LEN_BYTES) / (double) MSG_BLOCK_LEN_BYTES);
    else
        *n_blocks = ceil ((strlen(str_input) + MSG_INFO_LEN_BYTES) / (double) MSG_BLOCK_LEN_BYTES);
    
    uint32_t *msg_data = (uint32_t *) calloc(*n_blocks * 64, sizeof(uint32_t));

    return msg_data;
}


/**
 * Riempie il blocco di dati vuoto con il messaggio, il bit di offset e la
 * lunghezza del messaggio.
 *
 * @param[in] str_input stringa che contiene il messaggio da scrivere nel blocco di dati
 * @param[in] msg_data puntatore al primo byte del blocco di dati
 * @param[in] n_blocks numero di blocchi da allocare in memoria
 */

void load_data(const char *const str_input, uint32_t *msg_data, uint32_t *const n_blocks) {
    uint64_t str_input_len = strlen(str_input);
    uint64_t msg_len = BIT_PER_CHAR * str_input_len;
    uint8_t free_bytes = get_free_bytes(str_input);
    uint32_t n_words_to_fill = ceil((double)str_input_len / CHARS_PER_WORD);

    for (uint64_t i = 0; i < n_words_to_fill; i++)
        for (uint8_t j = 0; j < CHARS_PER_WORD; j++) {
            uint32_t byte_to_write = (uint32_t) str_input[CHARS_PER_WORD * i + j];
            *(msg_data + i) += byte_to_write << (WORD_LEN_BITS - BIT_PER_CHAR * (1 + j));

            if ((i == (n_words_to_fill - 1)) && (j == (CHARS_PER_WORD - free_bytes)))
                break;
        }
    
    if (free_bytes == 0)
        *(msg_data + (str_input_len / CHARS_PER_WORD)) = (1 << (WORD_LEN_BITS - 1));
    else
        *(msg_data + (str_input_len / CHARS_PER_WORD)) += (1 << (free_bytes * BIT_PER_CHAR - 1));
    
    *(msg_data + *n_blocks * MSG_BLOCK_LEN_WORDS - MSG_INFO_LEN_WORDS) = (uint32_t) (msg_len >> WORD_LEN_BITS/2);
    *(msg_data + *n_blocks * MSG_BLOCK_LEN_WORDS - MSG_INFO_LEN_WORDS + 1) = (uint32_t) msg_len;
}


/**
 * Calcola quanti byte sono rimasti liberi per la scrittura di informazioni
 * nell'ultima word in cui viene scritto l'ultimo gruppo di caratteri del
 * messaggio. Viene utilizzata per trascrivere correttamente l'1 di offset.
 *
 * @param[in] string stringa contenente il messaggio
 *
 * @return Il numero di byte liberi nell'ultima word
 */

uint8_t get_free_bytes(const char *const string) {
    switch (strlen(string) % 4) {
        case 0:
            return 0;
        case 1:
            return 3;
        case 2:
            return 2;
        case 3:
            return 1;
        default:
            exit(EXIT_FAILURE);
    } 
}


/**
 * Applica la funzione di hash a una determinata stringa.
 *
 * @param[in] str_input stringa che contiene il messaggio su cui operare l'hashing
 * @param[out] h_i array in cui viene salvato l'hash in gruppi di word a 32 bit
 */

void hash(const char *const str_input, uint32_t *const h_i) {
    uint32_t n_blocks;
    uint32_t h_0[DIM_HASH] = {H_INIZIALI};
    uint32_t k_constants[64] = {KI_INIZIALI};
    uint32_t words[64] = {0};
    uint32_t tmp1, tmp2;
    uint8_t offset = 16; //Si può dichiarare come macro

    uint32_t *msg_data = make_msg_block(str_input, &n_blocks);
    load_data(str_input, msg_data, &n_blocks);

    for (uint32_t j = 0; j < n_blocks; j++){ 
        copy_vector(h_0, DIM_HASH, h_i, DIM_HASH);

        //Message schedule
        for (int k = 0; k < DIM_BLOCK_HASH; k++){
            words[k] = msg_data[k+j*offset];      //Ogni volta che ho compresso un'intero blocco devo procedere con il prossimo e per prima cosa prelevo le 16word di partenza
        }

        for (int i = 0; i < 64; i++){               //Opero sulle 64 word. Le prime 16 note, le restanti calcolate come segue.    
            if (i >= DIM_BLOCK_HASH){               
                words[i] = sigma_1(words[i-2]) + words[i-7] + sigma_0(words[i-15]) + words[i-16];
            }

            tmp1 = usigma_1(h_i[4]) + choice(h_i[4], h_i[5], h_i[6]) + h_i[7] + k_constants[i] + words[i];
            tmp2 = usigma_0(h_i[0]) + majority(h_i[0], h_i[1], h_i[2]);

            shift_state_reg(h_i, 8);        //Sposto in basso in coeff. a->b, b->c etc.

            h_i[0] = tmp1 + tmp2;
            h_i[4] += tmp1;    
        }

        sum_vector(h_0, DIM_HASH, h_i, DIM_HASH);       //Calcolo gli state register del blocco attuale definiti come h(i) = h(0) + h(i)    () := pedici
        copy_vector(h_i, DIM_HASH, h_0, DIM_HASH);      //Aggiorno gli status register di partenza in caso vi siano ulteriori blocchi (n_block > 0)
    }

    free(msg_data);
}