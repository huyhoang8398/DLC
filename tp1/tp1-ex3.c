#include "gmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    FILE *fpkey,*fpcipher,*fpplain;
    fpkey = fopen("./Ressources-TP1/private_key.txt","r");
    if (fpkey == NULL){
        printf("Error! opening key file");

        // Program exits if the file pointer returns NULL.
        return 0;
    }
    fpcipher = fopen("./Ressources-TP1/ciphertext.txt","r");
    if (fpcipher == NULL){
        printf("Error! opening cipher file");

        // Program exits if the file pointer returns NULL.
        return 0;
    }

    mpz_t n,d,c,m,truem;
    mpz_inits(n,d,c,m,truem,NULL);

    gmp_fscanf(fpkey,"%*3c %Zx\n%*3c %Zx",n,d);
    gmp_printf("n= %Zx\nd= %Zx\n",n,d);
    gmp_fscanf(fpcipher,"%*3c %Zx",c);
    gmp_printf("c= %Zx\n",c);

    int maxdlen = 2 + mpz_sizeinbase(d,2);
    char d_in_bin[maxdlen] ;
    mpz_get_str(d_in_bin, 2, d);
    long dlen = strlen(d_in_bin);
    //    printf("d in binary: %s\n", d_in_bin);

    mpz_mod(c,c,n);
    mpz_set_ui(m,1);

    for (int i = 0; i < dlen; ++i) {
        mpz_mul(m,m,m);
        mpz_mod(m,m,n);
        if (d_in_bin[i] == '1') {
            mpz_mul(m,m,c);
            mpz_mod(m,m,n);
        }
    }

    gmp_printf("Calculated M = \n%Zx\n",m);

    fpplain = fopen("./Ressources-TP1/plaintext.txt","r");
    if (fpplain == NULL){
        printf("Error! opening plaintext file");
        return 0;
    }

    gmp_fscanf(fpplain,"%*3c %Zx",truem);
    gmp_printf("True M = \n%Zx\n",truem);

    if (mpz_cmp(m,truem) == 0) {
        printf("Calculation is right !!!\n");
    } else {
        printf("Calculation is wrong :( \n");
    }

    mpz_clears(n,d,c,m,truem,NULL);

    fclose(fpkey);
    fclose(fpcipher);
    fclose(fpplain);
    return 0;
}

