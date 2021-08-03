#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include "hash.h"

#define word_len 32
#define bit_per_char 8
#define dim_hash 8                      //L'hash avrà sempre dimensione pari a 256bit -> 8word
#define pci_hash 65                     //Dimensione info di ridondanza definite dall'algoritmo SHA-256
#define dim_block_hash 16               //Dimensione blocco hash in W32
#define val_max_32bit 2147483648
#define dim_prev_hash 640               //Dimesione hash sempre pari a 256, per definizione. Poichè la funz. hash accetta in input solo char a seguito della conversione risulta: 
                                        //8(uint32) * n_char_per_uint32 * 8bit(dimensione di un char) = 640.

#define n_char_per_uint32 10
#define n_char_per_prev_hash 20         //N celle char per memorizzare il prev hash 10char per ogni unsigned int, sapendo che l'hash è costituito da 8 unsigned int 

#define offset_mod_0 32768              //Separatore tra dati e padding in caso di list_trans_len % 4 == 0. 
#define offset_mod_1 128                //Separatore tra dati e padding in caso di list_trans_len % 4 == 1. 
#define offset_mod_2 2147483648         //Separatore tra dati e padding in caso di list_trans_len % 4 == 2. 
#define offset_mod_3 8388608            //Separatore tra dati e padding in caso di list_trans_len % 4 == 3. 


#define h_iniziali  0x6a09e667,\
                    0xbb67ae85,\
                    0x3c6ef372,\
                    0xa54ff53a,\
                    0x510e527f,\
                    0x9b05688c,\
                    0x1f83d9ab,\
                    0x5be0cd19

#define ki_iniziali 0x428a2f98,\
                    0x71374491,\
                    0xb5c0fbcf,\
                    0xe9b5dba5,\
                    0x3956c25b,\
                    0x59f111f1,\
                    0x923f82a4,\
                    0xab1c5ed5,\
                    0xd807aa98,\
                    0x12835b01,\
                    0x243185be,\
                    0x550c7dc3,\
                    0x72be5d74,\
                    0x80deb1fe,\
                    0x9bdc06a7,\
                    0xc19bf174,\
                    0xe49b69c1,\
                    0xefbe4786,\
                    0x0fc19dc6,\
                    0x240ca1cc,\
                    0x2de92c6f,\
                    0x4a7484aa,\
                    0x5cb0a9dc,\
                    0x76f988da,\
                    0x983e5152,\
                    0xa831c66d,\
                    0xb00327c8,\
                    0xbf597fc7,\
                    0xc6e00bf3,\
                    0xd5a79147,\
                    0x06ca6351,\
                    0x14292967,\
                    0x27b70a85,\
                    0x2e1b2138,\
                    0x4d2c6dfc,\
                    0x53380d13,\
                    0x650a7354,\
                    0x766a0abb,\
                    0x81c2c92e,\
                    0x92722c85,\
                    0xa2bfe8a1,\
                    0xa81a664b,\
                    0xc24b8b70,\
                    0xc76c51a3,\
                    0xd192e819,\
                    0xd6990624,\
                    0xf40e3585,\
                    0x106aa070,\
                    0x19a4c116,\
                    0x1e376c08,\
                    0x2748774c,\
                    0x34b0bcb5,\
                    0x391c0cb3,\
                    0x4ed8aa4a,\
                    0x5b9cca4f,\
                    0x682e6ff3,\
                    0x748f82ee,\
                    0x78a5636f,\
                    0x84c87814,\
                    0x8cc70208,\
                    0x90befffa,\
                    0xa4506ceb,\
                    0xbef9a3f7,\
                    0xc67178f2

/*  Per Binotto: le funzioni che avevi dichiarato sono state spostate nel file hash.h. 
    La libreria 'hash.h è stata inclusa sopra.
*/


int main (int argc, char ** argv){
    unsigned int input = 8432319;
    unsigned int prev_hash[8] = {1111111111, 2002222222, 3333333333, 1112222222, 1115555555, 1111666666, 1010777777 , 1112525252};
    
    unsigned int list_trans_len = 24*8;
    char list_trans[24] = {'a', 'b', 'c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x'};
    unsigned int *block_data = NULL;
    int n_block = 0;

    u_int8_t x[4] = {0};
    bool b_x[32] = {0};
    char *digit = NULL;          

    block_data = create_block(list_trans_len, &n_block);
    loading_data(block_data, n_block, prev_hash, 180, list_trans, list_trans_len);

    for (int i = 0; i < n_block*dim_block_hash; i++){
        printf("\n%d)\t%10u\t\t", i, block_data[i]);
        decimal_to_bin(block_data[i], b_x, word_len);
        for (int j = 0; j < word_len; j++){
            printf("%d", b_x[j]);
        }
            
    }
    
return 0;
}*/


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
    num = (x >> n_bit) | (x << (word_len-n_bit));
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
    for (int i = len_x - 1; i >= 0 && x > 0 ; i--){
        vett = vett + x[i] * pow(2, 31-i);
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
    bool x_bit[word_len] = {0};
    bool y_bit[word_len] = {0};
    bool z_bit[word_len] = {0};

    bool num[word_len] = {0};

    decimal_to_bin(x, x_bit, word_len);
    decimal_to_bin(y, y_bit, word_len);
    decimal_to_bin(z, z_bit, word_len);
 
    for (int i = 0; i < word_len; i++)
    {
        if(x_bit[i] == 0)
            num[i] = z_bit[i];
        else   
            num[i] = y_bit[i];
    }

return bin_to_decimal(num, word_len);
}

/*maggiority()
**x, y, z := word a 32 bit passati alla funzione,
**num := word a 32 bit ritornata dalla funzione,
**
**num[i] sarà pari al valore che è presente in maggioranza sulla colonna i-esima.
*/
unsigned int maggiority (unsigned int x, unsigned int y, unsigned int z)
{
    bool x_bit[word_len] = {0};
    bool y_bit[word_len] = {0};
    bool z_bit[word_len] = {0};

    bool num[word_len] = {0};

    decimal_to_bin(x, x_bit, word_len);
    decimal_to_bin(y, y_bit, word_len);
    decimal_to_bin(z, z_bit, word_len);

    for (int i = 0; i < word_len; i++){
        if((x_bit[i] && y_bit[i]) || (z_bit[i] && y_bit[i]) || (x_bit[i] && z_bit[i])) 
            num[i] = 1;
        else   
            num[i] = 0;
    }
    
return bin_to_decimal(num, word_len);
}


/*Creazione del messaggio a partire dai dati ricevuti dal blocco.
**list_trans_len := indica la dimensione in BIT dei dati che andranno a comporre il blocco
**dim_prev_hash := lunghezza in bit del prev_hash. Come da definizione ha dimensione fissa pari a 256bit.
**dim_nonce := dimensione fissata a 10 caratteri (num max di cifre per numero uint32) char ovvero 80bit.
**
**Restituisce il block_data che dorvà essere processato dall'hash e il numero di blocchi da 512bit che sono presenti in esso.
*/
unsigned int* create_block(unsigned int list_trans_len, int *n_block)
{
    u_int64_t dim_dati = 0;             //Dimensione in bit
    u_int64_t dim_tot = 0;
    unsigned int *block_data = NULL;
    unsigned int dim_nonce = n_char_per_uint32*8;       //n_char_per_uint32 * 8 = 80bit in totale.  

    dim_dati = list_trans_len + dim_prev_hash + dim_nonce;        

    //Calcolo dim totale del blocco da generare.
    if(dim_dati == 0)
        dim_tot = dim_dati + pci_hash - 1;      //Se non ho dati non dovrò nemmeno aggiungere il bit che separa i dati dal padding, perciò il -1.
    else   
        dim_tot = dim_dati + pci_hash;

    
    if(dim_tot <= dim_block_hash*word_len){
        *n_block = 1;
    }
    else{
        if (dim_tot % (dim_block_hash*word_len) != 0)
            *n_block = (dim_tot/(dim_block_hash*word_len))+1;
        else
            *n_block = (dim_tot/(dim_block_hash*word_len));
    }    
         
    block_data = malloc(sizeof(unsigned int) * (*n_block) * dim_block_hash);        
        
    // Controllo funzionamento di malloc()
    if(block_data == NULL){
        printf("Error: malloc() failure");
        exit(EXIT_FAILURE);
    } 
return block_data;
}

void loading_data (unsigned int* block_data, int n_block, const unsigned int* prev_hash, unsigned int nonce, char* list_trans, unsigned int list_trans_len)
{
    u_int64_t dim_dati = 0;     //Dimensione blocco (dati) in bit.
    char *nonce_char = 0;
    unsigned int dim_nonce = n_char_per_uint32*8;       //n_char_per_uint32 * 8 = 80bit in totale.
    
    char *prev_hash_part = NULL;                    //Conterrà il vettore di char che corrisponde al uint convertito in char cifra per cifra.
    char *prev_hash_tot = NULL;
    unsigned int prev_hash_char_dim = 10;           //Varrà sempre 10 poichè un uint32 ha 10 cifre.Non di interesse poichè so che per ogni word da 32bit del hash devo avere una dim fissa.

    prev_hash_tot = (char *) malloc(sizeof(char)*80);        //80 poichè hash è costituito da 8 word a 32bit (uint32) che convertite in char saranno 8*10, dove 10 indica le cifre char necessarie a rappr. un unsigned int
    if(prev_hash_tot == NULL){
        printf("Error: malloc() failure while generating prev_hash_tot.");
        exit(EXIT_FAILURE);
    } 

    dim_dati = dim_nonce + dim_prev_hash + list_trans_len;

    //Conversione prev_hash in char. Che poi verrà memorizzato in un vettore di 80char prev_hash_tot.
    for (int i = 0; i < 8; i++){                                               //Hash è costituito da 8 word da 32bit ciascuna.
        prev_hash_part = int_32_to_char(prev_hash[i]);
        for (int j = 0; j < prev_hash_char_dim; j++){
            prev_hash_tot[n_char_per_uint32*i+j] = prev_hash_part[j];          //E' un vettore contentente 80 celle char
        }  
    }
    //Codice per memorizzare dentro il block_data tutto il prev_hash in formato char.
    for(int j = 0; j < n_char_per_prev_hash; j++){                                      
        for (int i = 0; i < sizeof(unsigned int) / sizeof(char); i++){     
            block_data[j] += prev_hash_tot[4*j+i] << (3-i)*8;
        }
    }
    
    //block_data = block_data + n_char_per_prev_hash;
    //block_data = block_data + 20;
    
    //Memorizzazione list_trans nel block_data. 
    //NB: list_trans avrà un numero di celle char empre multiplo di 24. Quindi riuscirò sempre a riempire completamente 6*n word a 32bit.
    //list_trans_len/bit_per_char := numero di celle in list_trans. Dividendo qst per 4 calcolo quante W32bit sono necessarie per la memorizz.

    unsigned int nword_per_list_trans = (list_trans_len/bit_per_char) / (sizeof(unsigned int) / sizeof(char));        //numero W32bit per memorizzare tutto list_trans.
    for(int j = 0; j < nword_per_list_trans; j++){    
        for (int i = 0; i < sizeof(unsigned int) / sizeof(char); i++){              //4 char per ogni uint32.  
            block_data[j+n_char_per_prev_hash] += list_trans[4*j+i] << (3-i)*8;
        }
    }

    nonce_char = int_32_to_char(nonce);

    for (int j = 0; j < 3; j++){                                    //Hash è costituito da 8 word da 32bit ciascuna.
        for (int i = 0; i < sizeof(unsigned int) / sizeof(char); i++){
            if(j == 2){
                block_data[j+ n_char_per_prev_hash + nword_per_list_trans] = (nonce_char[4*j+0] << 24) + (nonce_char[4*j+0] << 16) + (unsigned int)offset_mod_0;
            }else{
                block_data[j+ n_char_per_prev_hash + nword_per_list_trans] += nonce_char[4*j+i] << (3-i)*8;    
            }
        }  
    }
    
    //Le ultime due locazioni di 32 bit del blocco di hash dovranno contenera la dimensione dei dati in esso contenuti.
    block_data[(n_block * dim_block_hash) - 2] = (dim_dati) >> word_len;
    block_data[(n_block * dim_block_hash) - 1] = ((dim_dati) << word_len ) >> word_len ;

}


void uint32_to_uint8 (unsigned int input, u_int8_t *n){
    n[0] = input; 
    n[1] = (input >> 8); 
    n[2] = (input >> 16); 
    n[3] = (input >> 24);  
}

/*int_32_to_char ()
**Funzione che permette di convertire un unsigned int in un vettore di char che ne descriva le singole cifre in codice ASCII.
*/
char* int_32_to_char(unsigned int input){
    //Sempre in BIG ENDIAN
    int i=10;                               //Offset per utilizzare l'ordine dei byte di tipo BIG ENDIAN
    char *digit_eff = NULL;

    digit_eff = (char *) calloc(n_char_per_uint32, sizeof(char));         //Variabile che conterrà le cifre effettive.
    if(digit_eff == NULL){
        printf("Error: calloc() failure");
        exit(EXIT_FAILURE);
    }

    //Ricavo le cifre e le converto in char.
    while (input){
        digit_eff[--i] = input % 10 + '0';
        input /= 10;   
    }
return digit_eff;  
}
