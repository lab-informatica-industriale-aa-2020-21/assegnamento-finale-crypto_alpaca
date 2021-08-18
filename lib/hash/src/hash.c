#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>

#include "hash.h"
#include "string.h"
#include "format_string.h"


/*Funzioni elementari per hash
**  >> shift vs destra
**  ^  operatore di XOR
*/

/*sigma_0()
**Funzione che preleva in input una word a 32bit e restituisce il risultato dell'operazione indicata.
**(Rotazione di 7) XOR (Rotazione di 18) XOR (shift di 3 a dx)
*/
unsigned int sigma_0 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,7)) ^ (rotate(x,18)) ^ (x >> 3);
return num;
}

/*sigma_1()
**Funzione che preleva in input una word a 32bit e restituisce il risultato dell'operazione indicata.
**(Rotazione di 17) XOR (Rotazione di 19) XOR (shift di 10 a dx)
*/
unsigned int sigma_1 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,17)) ^ (rotate(x,19)) ^ (x >> 10);
return num;
}

/*usigma_0() 
**Funzione che preleva in input una word a 32bit e restituisce il risultato dell'operazione indicata.
**(Rotazione di 2) XOR (Rotazione di 13) XOR (Rotazione di 22)
*/
unsigned int usigma_0 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,2)) ^ (rotate(x,13)) ^ (rotate(x,22));
return num;
}

/*usigma_1()
**Funzione che preleva in input una word a 32bit e restituisce il risultato dell'operazione indicata.
**(Rotazione di 6) XOR (Rotazione di 11) XOR (Rotazione di 25)
*/
unsigned int usigma_1 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,6)) ^ (rotate(x,11)) ^ (rotate(x,25));
return num;
}

/*rotate()
**Funzione che preleva in input una word a 32bit ed effettua la rotazione della stessa
*/
unsigned int rotate (unsigned int x, int n_bit)
{
    unsigned int num=0;
    num = (x >> n_bit) | (x << (WORD_LEN-n_bit));
return num;
}

/*decimal_to_bin() : conversione decimale -> binario.
**Funzione che realizza la conversione da decimale a binaria. Viene utilizzata la convenzione BIG ENDIAN.
**
**Il formato BIG ENDIAN equivale a porre in v[0] = MSB; v[max] = LSB;
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

/*bin_to_decimal() : conversione binario -> decimale
**Funzione che realizza la conversione da bianario a decimale.
*/
unsigned int bin_to_decimal (bool *x, int len_x)
{
    unsigned int vett = 0;
        for (int i = len_x - 1; i >= 0; i--){
            vett = vett + x[i] * pow(2, len_x-1-i);
        }
return vett;
}

/*choice() : scelta()
**x, y, z := word a 32 bit passati alla funzione,
**num := word a 32 bit ritornata dalla funzione,
**
**In base al valore assunto da x[i], num[i] sarà uguale a y[i] oppure z[i].
*/
unsigned int choice (unsigned int x, unsigned int y, unsigned int z)
{
    bool x_bit[WORD_LEN] = {0};
    bool y_bit[WORD_LEN] = {0};
    bool z_bit[WORD_LEN] = {0};

    bool num[WORD_LEN] = {0};

    decimal_to_bin(x, x_bit, WORD_LEN);
    decimal_to_bin(y, y_bit, WORD_LEN);
    decimal_to_bin(z, z_bit, WORD_LEN);
 
    for (int i = 0; i < WORD_LEN; i++)
    {
        if(x_bit[i] == 0)
            num[i] = z_bit[i];
        else   
            num[i] = y_bit[i];
    }

return bin_to_decimal(num, WORD_LEN);
}

/*majority()
**x, y, z := word a 32 bit passati alla funzione,
**num := word a 32 bit ritornata dalla funzione,
**
**num[i] sarà pari al valore che è presente in maggioranza sulla colonna i-esima.
*/
unsigned int majority (unsigned int x, unsigned int y, unsigned int z)
{
    bool x_bit[WORD_LEN] = {0};
    bool y_bit[WORD_LEN] = {0};
    bool z_bit[WORD_LEN] = {0};

    bool num[WORD_LEN] = {0};

    decimal_to_bin(x, x_bit, WORD_LEN);
    decimal_to_bin(y, y_bit, WORD_LEN);
    decimal_to_bin(z, z_bit, WORD_LEN);

    for (int i = 0; i < WORD_LEN; i++){
        if((x_bit[i] && y_bit[i]) || (z_bit[i] && y_bit[i]) || (x_bit[i] && z_bit[i])) 
            num[i] = 1;
        else   
            num[i] = 0;
    }
    
return bin_to_decimal(num, WORD_LEN);
}


/*int_32_to_char ()
**Funzione che permette di convertire un unsigned int in un vettore di char che ne descriva le singole cifre in codice ASCII.
*/
char* int_32_to_char(unsigned int input) {
    char *string = malloc((HEX_NUMB_LENGTH + 1) * sizeof(char));
    uint32_to_stringDec(input, string);
    return string;

/*    //Sempre in BIG ENDIAN
    int i=10;                               //Offset per utilizzare l'ordine dei byte di tipo BIG ENDIAN
    char *digit_eff = NULL;

    digit_eff = (char *) calloc(N_CHAR_PER_UINT32, sizeof(char));         //Variabile che conterrà le cifre effettive.
    if(digit_eff == NULL){
        printf("Error: calloc() failure");
        exit(EXIT_FAILURE);
    }

    //Ricavo le cifre e le converto in char.
    while (input){
        digit_eff[--i] = input % 10 + '0';
        input /= 10;   
    }
return digit_eff; */
}

void shift_state_reg(unsigned int *vett, int len){
    for (int i = 1; i < len; i++)
        vett[len-i] = vett[len-i-1];
}

//Copia vett2[i] = vett1[i]
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

//Somma tra due vettori vett2[i] = vett2[i] + vett1[i]
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

uint32_t *make_msg_block(const char *const str_input, uint32_t *const n_blocks) {
    uint8_t free_bytes = get_free_bytes(str_input);

    if (free_bytes == 0) 
        *n_blocks = ceil((strlen(str_input) + 1 + MSG_INFO_LEN) / (double) MSG_BLOCK_LEN);
    else
        *n_blocks = ceil ((strlen(str_input) + MSG_INFO_LEN) / (double) MSG_BLOCK_LEN);
    
    uint32_t *msg_data = (uint32_t *) calloc(*n_blocks * MSG_BLOCK_LEN, sizeof(uint32_t));

    return msg_data;
}


void load_data(const char *const str_input, uint32_t *msg_data, uint32_t *const n_blocks) {
    uint64_t str_input_len = strlen(str_input);
    uint64_t msg_len = BIT_PER_CHAR * str_input_len;
    uint8_t free_bytes = get_free_bytes(str_input);
    uint32_t n_words_to_fill = ceil((double)str_input_len / CHARS_PER_WORD);

    for (uint64_t i = 0; i < n_words_to_fill; i++)
        for (uint8_t j = 0; j < CHARS_PER_WORD; j++) {
            uint32_t byte_to_write = (uint32_t) str_input[CHARS_PER_WORD * i + j];
            *(msg_data + i) += byte_to_write << (WORD_LEN - BIT_PER_CHAR * (1 + j));
        }
    
    if (free_bytes == 0)
        *(msg_data + (str_input_len / CHARS_PER_WORD)) = (1 << WORD_LEN - 1);
    else
        *(msg_data + (str_input_len / CHARS_PER_WORD)) += (1 << (free_bytes * BIT_PER_CHAR - 1));
    
    *(msg_data + *n_blocks * MSG_BLOCK_LEN - MSG_INFO_LEN) = (uint32_t) (msg_len >> WORD_LEN/2);
    *(msg_data + *n_blocks * MSG_BLOCK_LEN - MSG_INFO_LEN + 1) = (uint32_t) msg_len;
}


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
        //Devo farlo sempre?
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