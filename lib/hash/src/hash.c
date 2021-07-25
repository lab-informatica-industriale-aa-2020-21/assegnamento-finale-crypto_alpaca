#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>


#define word_len 32
#define dim_hash 8                      //L'hash avrà sempre dimensione pari a 256bit -> 8word
#define pci_hash 65                     //Dimensione info di ridondanza definite dall'algoritmo SHA-256
#define dim_block_hash 16               //Dimensione blocco hash in W32
#define val_max_32bit 2147483648


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

unsigned int rotate (unsigned int num, int n_bit);
unsigned int sigma_0 (unsigned int x);
unsigned int sigma_1 (unsigned int x);
unsigned int usigma_0 (unsigned int x);
unsigned int usigma_1 (unsigned int x);
unsigned int maggiority (unsigned int x, unsigned int y,  unsigned int z);
unsigned int choice ( unsigned int x, unsigned int y,  unsigned int z);
unsigned int bin_to_decimal (bool *x, int len_x);
void decimal_to_bin (unsigned int x, bool *vett, int len_vett);
void uint32_to_uint8 (unsigned int input, u_int8_t *n);


int main (int argc, char ** argv){
    unsigned int input = 2147483648;
    u_int8_t x[4] = {0};
    bool b_x[32] = {0};
    char out[10] = {0};
    int i=10;
    
    //uint32_to_uint8(input, x);

    decimal_to_bin(input, b_x, 32);
    for(int i = 0; i < 32; i++)
        printf("%d", b_x[i]);

    i = bin_to_decimal(b_x, 32);
    printf("\n\n%u", i);
    /*while (input){
        out [--i] = input % 10);
        input /= 10;   
    }*/
    
return 0;
}


/*Funzioni elementari per hash
**  >> shift vs destra
**  ^  operatore di XOR
*/
unsigned int sigma_0 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,7)) ^ (rotate(x,18)) ^ (x >> 3);
return num;
}

unsigned int sigma_1 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,17)) ^ (rotate(x,19)) ^ (x >> 10);
return num;
}

unsigned int usigma_0 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,2)) ^ (rotate(x,13)) ^ (rotate(x,22));
return num;
}

unsigned int usigma_1 (unsigned int x)
{
    unsigned int num=0;
    num = (rotate(x,6)) ^ (rotate(x,11)) ^ (rotate(x,25));
return num;
}

unsigned int rotate (unsigned int x, int n_bit)
{
    unsigned int num=0;
    num = (x >> n_bit) | (x << (word_len-n_bit));
return num;
}

//Il formato è BIG ENDIAN. v[0] = MSB; v[max] = LSB;
void decimal_to_bin (unsigned int x, bool *vett, int len_vett)
{ 
    for (int i = len_vett - 1; i >= 0 && x > 0 ; i--){
        vett[i] = x % 2;
        x = x / 2;
    }
}

unsigned int bin_to_decimal (bool *x, int len_x)
{
    unsigned int vett = 0;
    for (int i = len_x - 1; i >= 0 && x > 0 ; i--){
        vett = vett + x[i] * pow(2, 31-i);
    }
return vett;
}

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
**list_trans_len := indica la dimensione in W32 dei dati che andranno a comporre il blocco
**dim_hash := lunghezza in W32 del prev_hash, ha dimensione fissa (16word)
**nonce := ha dimensione fissa poichè è un unsigned int (1word)
**
**Restituisce il block_data che dorvà essere processato dall'hash e il numero di blocchi da 512bit che sono presenti in esso.
*/
unsigned int* create_block(unsigned int list_trans_len, int *n_block, const unsigned int* prev_hash, unsigned int dim_prev_hash, unsigned int nonce, unsigned int dim_nonce)
{
    u_int64_t dim_tot = 0;
    unsigned int *block_data = NULL;

    dim_tot = list_trans_len + dim_prev_hash + dim_nonce;     //Dimensione in bit.

    //Se non ho dati da inserire nel blocco di hash anche la dimensione dei dati sarà posta a 0.
    if (dim_tot != 0)
        dim_tot += pci_hash;

    if(dim_tot <= dim_block_hash*word_len){
        *n_block = 1;
    }
    else{
        if (dim_tot % (dim_block_hash*word_len) != 0)
            *n_block = (dim_tot/dim_block_hash)+1;
        else
            *n_block = (dim_tot/dim_block_hash);
    }    
         
    block_data = malloc(sizeof(unsigned int) * (*n_block) * dim_block_hash);        //fare controllo malloc
return block_data;
}

void loading_data (unsigned int* block_data, int n_block, const unsigned int* prev_hash, unsigned int dim_prev_hash, unsigned int nonce, unsigned int dim_nonce, unsigned int* list_trans, unsigned int list_trans_len)
{
    u_int64_t dim_dati = 0;     //Dimensione blocco (dati) in bit.
    int list_tran_index = 0;

    dim_dati = (dim_nonce + dim_prev_hash + list_trans_len) * word_len;
    
    for (int i = 0; i < dim_block_hash * n_block; i++){
        if (i < dim_prev_hash){
            block_data[i] = prev_hash[i];                       //Memorizzazione del previous_hash.
        }
        else if (i == dim_prev_hash && dim_nonce != 0){
            block_data[i] = nonce;                              //Memorizzazione del nonce.
        }
        else if (i < dim_prev_hash + dim_nonce + list_trans_len){
            block_data[i] = list_trans[list_tran_index];        //Memorizzazione delle transazioni
            list_tran_index++;
        }
        else if ((i == dim_prev_hash + dim_nonce + list_trans_len) &&  dim_dati != 0){
            block_data[i] = val_max_32bit;                      //Sarà il valor che mi permette di mettere un 1 per separare i dati dal padding. 
        }
        else {
            block_data[i] = 0;                                  //Imposto le restanti celle a zero.
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

