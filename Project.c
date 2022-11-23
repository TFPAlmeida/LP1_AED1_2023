//
// Created by tiago on 19/11/2022.
//

#include "Project.h"

#define NLINES 10
#define NCOLUMNS 10

int main_project(int argc, const char *argv[]) {
    int i = 0;
    short **matrix_pubs = alloc_matrix_int(NLINES, NCOLUMNS);
    short **matrix_privs = alloc_matrix_int(NLINES, NCOLUMNS);
    short **matrix_rle = alloc_matrix_int(NLINES, NCOLUMNS);
    while(i < NLINES){
        unsigned long long key2 = new_public_key_int();
        printf("%llu\n",key2);
        unsigned long long privtkey = calc_private_key_int(key2);
        unsigned long long rle = calc_runlength_int(privtkey);
        printf("%llu = ", rle);
        unsigned long long key = private_key_from_runlength_int(rle);
        printf("%llu\n", key);
        i++;
    }

    /**---------------------------------------------------------------------------------------------------------------*/
    char **matrix_chars = alloc_matrix_char(NLINES, NCOLUMNS);
    return 0;
}


unsigned long long new_public_key_int(void) {
    //srand(time(NULL));
    unsigned long long key = rand() % 3000 + 1;
    return key;
}

short *key_long_2_digits_int(unsigned long long key) {
    unsigned long long mod = 0, mod1 = 0, n = 0;
    int count = init_size(key);
    short *aux = (short *) malloc((count) * sizeof(short));
    short *key1 = (short *) malloc((count + 1) * sizeof(short));
    int j = count - 1;
    for (int i = 0; i < count; i++) {
        mod = key % 10;
        *(aux + i) = mod;
        *(key1 + j) = *(aux + i);
        key = key / 10;
        j--;
    }
    *(key1 + count) = -1;
    /*for(int i = 0; i < count + 1; i++){
        printf("%d ", *(key1 + i));
    }*/




    return key1;
}


unsigned long long key_digits_2_long_int(short *keydigits) {
    unsigned long long key = 0;

    for (int i = 0; *(keydigits + i + 1) != -1; i++) {
        //printf("%llu ",*(keydigits + i));
        key = key * 10 + *(keydigits + i);
    }
    return key;
}

int verify_private_key(const short *privtkey) {
    int count = countDistinct(privtkey);
    int a = ascending(privtkey);
    int d = descending(privtkey);

    if (count == 2 && a == 1 || count == 2 && d == 1) {
        return 1;
    }
    return 0;
}

int descending(const short *privtkey) {
    int d = 1;

    for (int i = 0; *(privtkey + i + 1) != -1; i++) {
        if (*(privtkey + i) < *(privtkey + i + 1) && *(privtkey + i + 1) != -1) {
            d = 0;
        }
    }
    return d;
}

int ascending(const short *privtkey) {
    int c = 1;

    for (int i = 0; *(privtkey + i + 1) != -1; i++) {
        if (*(privtkey + i) > *(privtkey + i + 1) && *(privtkey + i + 1) != -1) {
            c = 0;
        }
    }
    return c;
}

int countDistinct(const short *privkey) {
    int res = 1;
    int j = 0;

    for (int i = 1; *(privkey + i) != -1; i++) {

        for (j = 0; j < i; j++)

            if (*(privkey + i) == *(privkey + j))
                break;

        if (i == j)
            res++;
    }

    return res;
}

int init_size(unsigned long long key) {
    int count = 0;
    unsigned long long aux = key;
    while (aux != 0) {
        aux = aux / 10;
        count++;
    }
    return count;
}

unsigned long long calc_private_key_int(unsigned long long pubkey) {
    unsigned long long privkey = 0;
    unsigned long long max = ULLONG_MAX;
    short *aux;
    for (int i = 2; (privkey * i) < max / 2; i++) {
        privkey = pubkey * i;
        aux = key_long_2_digits_int(privkey);

        if (verify_private_key(aux) == 1) {
            break;
        } else {
            privkey = 0;
        }
    }
    return privkey;
}

unsigned long long calc_runlength_int(unsigned long long privtkey) {
    unsigned long long privtkey_rle = 0;
    int count = 1;
    int j = 0;
    short aux3 = 0;
    short *aux = key_long_2_digits_int(privtkey);
    short *aux1 = (short *) malloc(7 * sizeof(short));
    for (int i = 0; *(aux + i) != -1; i++) {
        if (*(aux + i) == *(aux + i + 1)) {
            count++;
        } else {
            if (count >= 10) {
                *(aux1 + j) = count / 10;
                *(aux1 + j + 1) = count % 10;
                *(aux1 + j + 2) = *(aux + i);
                j += 3;
                count = 1;

            } else {
                *(aux1 + j) = 0;
                *(aux1 + j + 1) = count;
                *(aux1 + j + 2) = *(aux + i);
                j += 3;
                count = 1;
            }
        }
    }
    *(aux1 + j + 1) = -1;
    privtkey_rle = key_digits_2_long_int(aux1);
    return privtkey_rle;
}

unsigned long long private_key_from_runlength_int(unsigned long long runlengthkey) {
    unsigned long long privtkey = 0;
    int count = init_size(runlengthkey);
    int aux1 = 0, aux2 = 0;
    short *array = key_long_2_digits_int(runlengthkey);
    switch (count) {
        case 4:
            aux1 = *(array + 0);
            privtkey = concatenar_key(aux1, *(array + 1), privtkey);
            aux2 = *(array + 2);
            privtkey = concatenar_key(aux2, *(array + 3), privtkey);
            break;
        case 5:
            for (int i = 0; i < 2; i++) {
                aux1 = aux1 * 10 + *(array + i);
                aux2 = aux2 * 10 + *(array + i + 2);
            }
            if (aux1 >= 19) {
                aux1 = *array;
                privtkey = concatenar_key(aux1, *(array + 1), privtkey);
                privtkey = concatenar_key(aux2, *(array + 4), privtkey);
            } else if (aux2 >= 19) {
                aux2 = *(array + 3);
                privtkey = concatenar_key(aux1, *(array + 2), privtkey);
                privtkey = concatenar_key(aux2, *(array + 4), privtkey);
            } else {
                privtkey = concatenar_key(aux1, *(array + 1), privtkey);
                privtkey = concatenar_key(aux2, *(array + 4), privtkey);
            }
            break;
        case 6:
            for (int i = 0; i < 2; i++) {
                aux1 = aux1 * 10 + *(array + i);
                aux2 = aux2 * 10 + *(array + i + 3);
            }
            if (aux1 + aux2 <= 20) {
                privtkey = concatenar_key(aux1, *(array + 2), privtkey);
                privtkey = concatenar_key(aux2, *(array + 5), privtkey);
            }
            break;
        default:
            break;
    }
    return privtkey;
}

unsigned long long concatenar_key(int aux, short key, unsigned long long privtkey) {
    unsigned long long a = 1;
    if (key == 0) {
        for (int i = 0; i < aux; i++) {
            a *= 10;
        }
        privtkey = privtkey * a;
    } else {
        for (int i = 0; i < aux; i++) {
            privtkey = privtkey * 10 + key;
        }
    }

    return privtkey;
}


short **alloc_matrix_int(int nlines, int ncolumns) {

    short **matrix = (short **) malloc(nlines * sizeof(short *));
    for (int i = 0; i < nlines; i++) {
        *(matrix + i) = (short *) malloc(NCOLUMNS * sizeof(short));
    }
    return matrix;
}

void store_key_int(short **matrix, int lines, unsigned long long key) {

}

/**-------------------------------------------------------------------------------------------------------------------*/

char **alloc_matrix_char(int nlines, int ncolumns) {
    char **matrix = (char **) malloc(nlines * sizeof(char *));

    for (int i = 0; i < nlines; i++) {
        *(matrix + i) = (char *) malloc(NCOLUMNS * sizeof(char));
    }
    return matrix;
}