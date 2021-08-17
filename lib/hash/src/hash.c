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
unsigned int maggiority (unsigned int x, unsigned int y, unsigned int z)
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


/*Creazione del messaggio a partire dai dati ricevuti dal blocco.
**list_trans_len := indica la dimensione in BIT dei dati che andranno a comporre il blocco
**DIM_PREV_HASH := lunghezza in bit del prev_hash. Come da definizione ha dimensione fissa pari a 256bit.
**dim_nonce := dimensione fissata a 10 caratteri (num max di cifre per numero uint32) char ovvero 80bit.
**
**Restituisce il block_data che dorvà essere processato dall'hash e il numero di blocchi da 512bit che sono presenti in esso.
*/
unsigned int* create_block(unsigned int list_trans_len, int *n_block)
{
    uint64_t dim_dati = 0;             //Dimensione in bit
    uint64_t dim_tot = 0;
    unsigned int *block_data = NULL;
    unsigned int dim_nonce = N_CHAR_PER_UINT32*8;       //N_CHAR_PER_UINT32 * 8bit = 80bit in totale. Ovvero dimensione per memorizzare il nonce convertito in char

    dim_dati = list_trans_len + DIM_PREV_HASH + dim_nonce;        

    //Calcolo dim totale del blocco da generare.
    if(dim_dati == 0)
        dim_tot = dim_dati + PCI_HASH - 1;      //Se non ho dati non dovrò nemmeno aggiungere il bit che separa i dati dal padding, perciò il -1.
    else   
        dim_tot = dim_dati + PCI_HASH;

    
    if(dim_tot <= DIM_BLOCK_HASH*WORD_LEN){     //Se la dimensione totale dei dati+pci è minore di 512 sarà sufficiente un blocco.
        *n_block = 1;
    }
    else{
        if (dim_tot % (DIM_BLOCK_HASH*WORD_LEN) != 0)
            *n_block = (dim_tot/(DIM_BLOCK_HASH*WORD_LEN))+1;       //Se la divisione produce un resto => troncamento. Perciò saranno necesari n+1 blocchi da 512bit.
        else
            *n_block = (dim_tot/(DIM_BLOCK_HASH*WORD_LEN));
    }    
         
    block_data = (unsigned int *) calloc((*n_block) * DIM_BLOCK_HASH, sizeof(unsigned int));    //Creo il blocco inizializzato a zero.
        
    // Controllo funzionamento di malloc()
    if(block_data == NULL){
        printf("Error: calloc() failure");
        exit(EXIT_FAILURE);
    } 
return block_data;
}

/*Caricamento dati nel blocco appena creato.
**
**Il caricamento viene suddiviso in 3 parti: caricamento prev_hash, caricamento list_trans e infine il nonce.
**
**1) Ogni componente del prev_hash verrà convertita in un'array di char[10] e salvato in prev_hash_part. Questo poi sarà salvato in prev_hash_tot che sarà un vett di 80celle char.
**2) Per caricare tutte le transazioni devo prima calcolare quante w32bit serviranno per memorizzarla. E' noto che la dimensione della lista sarà multipla di 24*8bit.
**   O meglio ogni transazione sarà rappresentabile attraverso 24 celle char. Questo semplifica il lavoro perchè n*24*8bit è sempre multiplo di 32bit (6w32 per ogni trans).
**3) Per memorizzare il nonce eseguo la sua conversione in char utilizzando 10 celle (uint_32 ha massimo 10 cifre). Eseguo il salvataggio di ciascuna cella in block_data.
**   Siccome sono 10 char saranno necessarie 2.5word a 32bit. Nell'ultima word vado ad aggiungere OFFSET_MOD_0 che corrisponde ad aggiungere un 1 (in binario) alla fine dei dati.
**
**Al termine di ciò andrò a salvare sulle ultime due celle di block data la dimensione dei dati contenuti nel blocco.
**Il padding è già presente dato che il block_data è generato attraverso una calloc().
**
*/

void loading_data (unsigned int* block_data, int n_block, const unsigned int* prev_hash, unsigned int nonce, char* list_trans, unsigned int list_trans_len)
{
    uint64_t dim_dati = 0;     //Dimensione blocco (dati) in bit.
    char *nonce_char = 0;
    unsigned int dim_nonce = N_CHAR_PER_UINT32*8;       //N_CHAR_PER_UINT32 * 8 = 80bit in totale.
    
    char *prev_hash_part = NULL;                        //Conterrà il vettore di char che corrisponde al uint convertito in char cifra per cifra.
    char *prev_hash_tot = NULL;
    unsigned int prev_hash_char_dim = 10;               //Varrà sempre 10 poichè un uint32 ha 10 cifre.Non di interesse poichè so che per ogni word da 32bit del hash devo avere una dim fissa.

    prev_hash_tot = (char *) malloc(sizeof(char)*80);   //80 poichè hash è costituito da 8 word a 32bit (uint32) che convertite in char saranno 8*10, dove 10 indica le cifre char necessarie a rappr. un unsigned int
    if(prev_hash_tot == NULL){
        printf("Error: malloc() failure while generating prev_hash_tot.");
        exit(EXIT_FAILURE);
    } 

    dim_dati = dim_nonce + DIM_PREV_HASH + list_trans_len;

    //Conversione prev_hash in char. Che poi verrà memorizzato in un vettore di 80char prev_hash_tot.
    for (int i = 0; i < 8; i++){                                               //Hash è costituito da 8 word da 32bit ciascuna.
        prev_hash_part = int_32_to_char(prev_hash[i]);
        for (int j = 0; j < (int)prev_hash_char_dim; j++){
            prev_hash_tot[N_CHAR_PER_UINT32*i+j] = prev_hash_part[j];          //E' un vettore contentente 80 celle char
        }  
    }
    //Codice per memorizzare dentro il block_data tutto il prev_hash in formato char.
    for(int j = 0; j < N_CHAR_PER_PREV_HASH; j++){                                      
        for (int i = 0; i < (int)(sizeof(unsigned int) / sizeof(char)); i++){     
            block_data[j] += prev_hash_tot[4*j+i] << (3-i)*8;
        }
    }
    
    //Memorizzazione list_trans nel block_data. 
    //NB: list_trans avrà un numero di celle char empre multiplo di 24. Quindi riuscirò sempre a riempire completamente 6*n word a 32bit.
    //list_trans_len/BIT_PER_CHAR := numero di celle in list_trans. Dividendo qst per 4 calcolo quante W32bit sono necessarie per la memorizz.
    unsigned int nword_per_list_trans = (list_trans_len/BIT_PER_CHAR) / (sizeof(unsigned int) / sizeof(char));        //numero W32bit per memorizzare tutto list_trans.
    for(int j = 0; j < (int)nword_per_list_trans; j++){    
        for (int i = 0; i < (int)(sizeof(unsigned int) / sizeof(char)); i++){              //4 char per ogni uint32.  
            block_data[j+N_CHAR_PER_PREV_HASH] += list_trans[4*j+i] << (3-i)*8;
        }
    }

    nonce_char = int_32_to_char(nonce);

    for (int j = 0; j < 3; j++){                                    //Hash è costituito da 8 word da 32bit ciascuna.
        for (int i = 0; i < (int)(sizeof(unsigned int) / sizeof(char)); i++){
            if(j == 2){
                block_data[j+ N_CHAR_PER_PREV_HASH + nword_per_list_trans] = (nonce_char[4*j+0] << 24) + (nonce_char[4*j+0] << 16) + (unsigned int)OFFSET_MOD_0;
            }else{
                block_data[j+ N_CHAR_PER_PREV_HASH + nword_per_list_trans] += nonce_char[4*j+i] << (3-i)*8;    
            }
        }  
    }
    
    //Le ultime due locazioni di 32 bit del blocco di hash dovranno contenera la dimensione dei dati in esso contenuti.
    block_data[(n_block * DIM_BLOCK_HASH) - 2] = (dim_dati) >> WORD_LEN;
    block_data[(n_block * DIM_BLOCK_HASH) - 1] = ((dim_dati) << WORD_LEN ) >> WORD_LEN ;

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


void hash_function (const unsigned int* prev_hash, unsigned int nonce, char* list_trans,
                    unsigned int list_trans_len, uint32_t *h_i)
{
    int n_block = 0;                                //Mi serve per capire quanti blocchi da 512 ci sono

    unsigned int *block_data = NULL;
    //unsigned int h_i[8] = {0};                    
    //unsigned int *h_i = NULL;                       //E' l'hash dell'i-esimo blocco. Composto da 8 word a 32bit come da definizione.
    unsigned int h_0[DIM_HASH] = {H_INIZIALI};      //State register h0 := valori iniziali dettati da delle costanti.
    unsigned int words[64] = {0};                   //conterrà le 64 word su cui l'hash dovrà operare. Le prime 16 sono prelevate dal block_data.
    
    unsigned int temp1, temp2;
    unsigned int k_constants[64] = {KI_INIZIALI};
    int offset = 16;                                //offset che mi permette di recuperare dal block_data word a 32bit in pacchetti di 16.

    block_data = create_block(list_trans_len, &n_block);
    loading_data(block_data, n_block, prev_hash, nonce, list_trans, list_trans_len);

    
    for (int j = 0; j < n_block; j++){ 
        //Devo farlo sempre?
        copy_vector(h_0, DIM_HASH, h_i, DIM_HASH);

        for (int k = 0; k < DIM_BLOCK_HASH; k++){
            words[k] = block_data[k+j*offset];      //Ogni volta che ho compresso un'intero blocco devo procedere con il prossimo e per prima cosa prelevo le 16word di partenza
        }
        for (int i = 0; i < 64; i++){               //Opero sulle 64 word. Le prime 16 note, le restanti calcolate come segue.    
            if (i >= DIM_BLOCK_HASH){               
                words[i] = sigma_1(i-2) + words[i-7] + sigma_0(i-15) + words[i-16];
            }

            temp1 = usigma_1(h_i[4]) + choice(h_i[4], h_i[5], h_i[6]) + h_i[7] + k_constants[i] + words[i];
            temp2 = usigma_0(h_i[0]) + maggiority(h_i[0], h_i[1], h_i[2]);

            shift_state_reg(h_i, 8);        //Sposto in basso in coeff. a->b, b->c etc.

            h_i[0] = temp1 + temp2;
            h_i[3] += temp1;    
        }

        sum_vector(h_0, DIM_HASH, h_i, DIM_HASH);       //Calcolo gli state register del blocco attuale definiti come h(i) = h(0) + h(i)    () := pedici
        copy_vector(h_i, DIM_HASH, h_0, DIM_HASH);      //Aggiorno gli status register di partenza in caso vi siano ulteriori blocchi (n_block > 0)
    }
}

//
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
























uint32_t *make_msg_block(const char *const str_input, uint32_t *n_blocks) {
    uint8_t free_bytes = strlen(str_input) % 4;

    if (free_bytes == 0) 
        *n_blocks = (strlen(str_input) + 1 + MSG_INFO_LEN) / MSG_BLOCK_LEN;
    else
        *n_blocks = (strlen(str_input) + MSG_INFO_LEN) / MSG_BLOCK_LEN;
    
    uint32_t *msg_data = (uint32_t *) calloc(*n_blocks * MSG_BLOCK_LEN, sizeof(uint32_t));

    return msg_data;
}




