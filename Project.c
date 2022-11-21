//
// Created by tiago on 19/11/2022.
//

#include "Project.h"

#define NLINES 20
#define NCOLUMNS 20

int main_project(int argc, const char *argv[]) {
    int i = 0;
    short **matrix_ints = alloc_matrix_int(NLINES, NCOLUMNS);
    //key_long_2_digits_int(1234);
    calc_private_key_int(251);
    /**---------------------------------------------------------------------------------------------------------------*/
    char **matrix_chars = alloc_matrix_char(NLINES, NCOLUMNS);
    return 0;
}

unsigned long long new_public_key_int(void) {
    srand(time(NULL));
    unsigned long long key = rand() % 10000 + 1;
    return key;
}

short *key_long_2_digits_int(unsigned long long key) {
    int count = 0, mod = 0, mod1 = 0, n = 0;
    unsigned long long aux = key;
    while (aux != 0) {
        aux = aux / 10;
        count++;
    }
    short *key1 = (short *) malloc(count * sizeof(short));

    for (int i = 0; i < count; i++) {
        mod = key % 10;
        n = n * 10 + mod;
        key = key / 10;
    }


    for (int i = 0; i < count; i++) {
        mod1 = n % 10;
        *(key1 + i) = mod1;

        n = n / 10;
    }

    return key1;
}

unsigned long long key_digits_2_long_int(short *keydigits) {
    unsigned long long key = 0;
    int n = sizeof(keydigits) / sizeof(short);
    for (int i = 0; i < n; i++) {
        key = key * 10 + *(keydigits + i);
    }
    return key;
}

int verify_private_key(short *privkey) {
    int count = countDistinct(privkey);
    int a = ascending(privkey);
    int d = descending(privkey);

    if (count == 2 && a == 1 || count == 2 && d == 1) {
        return 1;
    }
    return 0;
}

int descending(short *privkey) {
    int d = 1;
    int n = sizeof(privkey) / sizeof(short);

    for (int i = 0; i < n-1; i++) {
        if (*(privkey + i) < *(privkey + i + 1)) {
            d = 0;
        }
    }
    return d;
}

int ascending(short *privkey) {
    int c = 1;
    int n = sizeof(privkey) / sizeof(short);

    for (int i = 0; i < n-1; i++) {
        if (*(privkey + i) > *(privkey + i + 1)) {
            c = 0;
        }
    }
    return c;
}

int countDistinct(short *privkey) {
    int res = 1;
    int j = 0;
    short n = sizeof(privkey) / sizeof(short);



    for (int i = 1; i < n; i++) {

        for (j = 0; j < i; j++)

            if (*(privkey + i) == *(privkey + j))
                break;

        if (i == j)
            res++;
    }
    return res;
}

unsigned long long calc_private_key_int(unsigned long long pubkey) {
    unsigned long long privkey = 0;
    short *aux;
    for (int i = 2; i < pubkey; i++) {
        privkey = pubkey * i;
        aux = key_long_2_digits_int(privkey);

        if (verify_private_key(aux)) {
            break;
        }
    }
    printf("%llu ",sizeof(aux) / sizeof(short));
    printf("%llu", privkey);
    return privkey;
}

short **alloc_matrix_int(int nlines, int ncolumns) {

    short **matrix = (short **) malloc(nlines * sizeof(short *));
    for (int i = 0; i < nlines; i++) {
        *(matrix + i) = (short *) malloc(NCOLUMNS * sizeof(short));
    }
    return matrix;
}

/**-------------------------------------------------------------------------------------------------------------------*/

char **alloc_matrix_char(int nlines, int ncolumns) {
    char **matrix = (char **) malloc(nlines * sizeof(char *));
    for (int i = 0; i < nlines; i++) {
        *(matrix + i) = (char *) malloc(NCOLUMNS * sizeof(char));
    }
    return matrix;
}