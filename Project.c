//
// Created by tiago on 19/11/2022.
//

#include "Project.h"

#define NLINES 5
#define NCOLUMNS 20

int main_project(int argc, const char *argv[]) {

    /**---------------------------------------------------------------------------------------------------------------*/
    //srand(time(NULL));
    short **matrix_pubs = alloc_matrix_int(NLINES, NCOLUMNS);
    short **matrix_privs = alloc_matrix_int(NLINES, NCOLUMNS);
    short **matrix_rle = alloc_matrix_int(NLINES, NCOLUMNS);

    bulk_populate_public_keys_int(matrix_pubs, NLINES);
    bulk_compute_private_keys_int(matrix_pubs, matrix_privs, NLINES);
    bulk_compute_runlengths_int(matrix_privs, matrix_rle, NLINES);

    //unsigned long long key = private_key_from_runlength_int(rle);
    //printf("%llu\n", key);
    //printf("%d ",i);

    //delete_key_int(matrix_pubs, matrix_privs, matrix_rle, i, 335);
    //delete_key_int(matrix_pubs, matrix_privs, matrix_rle, i, 468);


    print_key_int(matrix_pubs, NLINES);
    printf("\n");
    print_key_int(matrix_privs, NLINES);
    printf("\n");
    sort_matrix_int(matrix_privs, NLINES, 0);
    print_key_int(matrix_privs, NLINES);
    //print_key_int(matrix_rle, NLINES);
    //printf("\n");

    /**---------------------------------------------------------------------------------------------------------------*/
    //char **matrix_chars = alloc_matrix_char(NLINES, NCOLUMNS);
    /**---------------------------------------------------------------------------------------------------------------*/
    return 0;
}


unsigned long long new_public_key_int(void) {

    unsigned long long key = rand() % 3000 + 1;
    return key;
}

short *key_long_2_digits_int(unsigned long long key) {
    unsigned long long mod = 0;
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

    return key1;
}


unsigned long long key_digits_2_long_int(const short *keydigits) {
    unsigned long long key = 0;

    for (int i = 0; *(keydigits + i) != -1; i++) {
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
    int res = 1, j = 0;

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
    short *aux = NULL;

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
    *(aux1 + j) = -1;
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
    short **matrix = (short **) malloc(nlines * ncolumns * sizeof(short *));

    for (int i = 0; i < nlines * 2; i++) {
        *(matrix + i) = (short *) malloc(ncolumns * sizeof(short));
    }
    return matrix;
}

void store_key_int(short **matrix, int lines, unsigned long long key) {
    int count = init_size(key);
    short *key_matrix = key_long_2_digits_int(key);

    *(*(matrix + count) + lines) = -1;
    for (int i = 0; i < count; i++) {
        *(*(matrix + i) + lines) = *(key_matrix + i);
    }
}

void print_key_int(short **matrix, int lines) {

    for (int i = 0; i < lines; i++) {
        for (int n = 0; *(*(matrix + n) + i) != -1; n++) {
            printf("%d ", *(*(matrix + n) + i));
        }
        if (*(*(matrix + 0) + i) != -1) {
            printf("\n");
        }
    }
}

int exists_key_int(short **matrix, int lines, unsigned long long key) {
    short *key_matrix = key_long_2_digits_int(key);
    int count = 0, n = 0;
    for (int i = 0; i < lines; i++) {
        for (n = 0; *(key_matrix + n) != -1; n++) {
            if (*(*(matrix + n) + i) == *(key_matrix + n)) {
                count++;
            } else {
                count = 0;
                break;
            }
        }
        if (n == count && n != 0) {
            return 1;
        }
    }
    return 0;
}

int find_key_int(short **matrix, int lines, unsigned long long key) {
    short *key_matrix = key_long_2_digits_int(key);
    int count = 0, n = 0;

    for (int i = 1; i <= lines; i++) {
        for (n = 0; *(*(matrix + n) + i) != -1; n++) {
            if (*(*(matrix + n) + i) == *(key_matrix + n)) {
                count++;
            } else {
                count = 0;
                break;
            }
        }
        if (n == count && n != 0) {
            return i;
        }
    }
    return 0;
}

unsigned long long
get_private_key_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long pubkey) {
    int h1 = exists_key_int(matrix_kpub, lines, pubkey);
    unsigned long long privkey = calc_private_key_int(pubkey);
    int h2 = exists_key_int(matrix_kpriv, lines, privkey);

    if (h1 == 1 && h2 == 1) {
        return privkey;
    }
    return 0;
}

unsigned long long get_runlength_int(short **matrix_kpriv, short **matrix_kcod, int lines, unsigned long long privkey) {
    int h1 = exists_key_int(matrix_kpriv, lines, privkey);
    unsigned long long codkey = calc_runlength_int(privkey);
    int h2 = exists_key_int(matrix_kcod, lines, codkey);

    if (h1 == 1 && h2 == 1) {
        return codkey;
    }
    return 0;
}

unsigned long long
delete_key_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, short pubkey) {
    int h1 = exists_key_int(matrix_kpub, lines, pubkey);
    unsigned long long privkey = calc_private_key_int(pubkey);
    int h2 = exists_key_int(matrix_kpriv, lines, privkey);
    unsigned long long codkey = calc_runlength_int(privkey);
    int h3 = exists_key_int(matrix_kcod, lines, codkey);
    int i = 0, n = 0, j = 0, k = 0;

    if (h1 == 1) {
        i = find_key_int(matrix_kpub, lines, pubkey);
        *(*(matrix_kpub + k) + i) = -1;
    }
    if (h2 == 1) {
        n = find_key_int(matrix_kpriv, lines, privkey);
        *(*(matrix_kpriv + k) + n) = -1;
    }
    if (h3 == 1) {
        j = find_key_int(matrix_kcod, lines, codkey);
        *(*(matrix_kcod + k) + j) = -1;
    }

    return pubkey;
}

void bulk_populate_public_keys_int(short **matrix_kpub, int lines) {

    for (int i = 0; i < lines; i++) {
        unsigned long long pubkey = new_public_key_int();
        store_key_int(matrix_kpub, i, pubkey);
    }
}

short *array_key(short **matrix, int i) {
    int n = 0;
    short *key = (short *) malloc(20 * sizeof(short));
    for (n = 0; *(*(matrix + n) + i) != -1; n++) {
        *(key + n) = *(*(matrix + n) + i);
    }

    *(key + n) = -1;
    return key;
}

void bulk_compute_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines) {
    short *key = NULL;
    for (int i = 0; i < lines; i++) {
        key = array_key(matrix_kpub, i);
        unsigned long long pubkey = key_digits_2_long_int(key);
        unsigned long long privtkey = calc_private_key_int(pubkey);
        store_key_int(matrix_kpriv, i, privtkey);
    }
}

void bulk_compute_runlengths_int(short **matrix_kpriv, short **matrix_kcod, int lines) {
    short *key = NULL;
    for (int i = 0; i < lines; i++) {
        key = array_key(matrix_kpriv, i);
        unsigned long long privkey = key_digits_2_long_int(key);
        unsigned long long rlekey = calc_runlength_int(privkey);
        store_key_int(matrix_kcod, i, rlekey);
    }
}

short **
search_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long partialpubkey) {
    short **matrix_matching = alloc_matrix_int(NLINES, NCOLUMNS);

    return matrix_matching;
}

unsigned long long *array_key_v2(short **matrix, int *id, int lines) {

    unsigned long long *key = (unsigned long long *) malloc(lines * sizeof(unsigned long long));

    short *aux = NULL;
    for (int i = 0; i < lines; i++) {
        aux = array_key(matrix, i);
        *(id + i) = i;
        *(key + i) = key_digits_2_long_int(aux);
    }
    return key;
}

void copy_matrix(short **matrix, short **aux, int lines ,const int *id){
    int n = 0;
    for(int k = 0; k < lines;k++){
        for (n = 0; *(*(matrix + n) + *(id + k)) != -1; n++) {
            *(*(aux + n) + k) = *(*(matrix + n) + *(id + k));
        }
        *(*(aux + n) + k) = -1;
    }
}
void sort_matrix_int(short **matrix, int lines, int order) {
    int *id = (int *) malloc(lines * sizeof(int));
    unsigned long long *key = array_key_v2(matrix, id, lines);
    short **aux = alloc_matrix_int(NLINES, NCOLUMNS);
    mergeSort(key, id, 0, lines - 1);
    int n = 0;
    for(int i = 0; i < lines; i++){
        copy_matrix(matrix, aux, lines, id);

    }

    for (int i = 0; i < lines; i++) {
        for (n = 0; *(*(aux + n) + i) != -1; n++) {
            *(*(matrix + n) + i) = *(*(aux + n) + i);

        }
        *(*(matrix + n) + i) = -1;
    }

}


void merge( unsigned long long *key, int *id, int mid, int low, int high) {
    int i, j, k;
    unsigned long long B[100];
    int A[100];
    i = low;
    j = mid + 1;
    k = low;

    while (i <= mid && j <= high) {
        if (*(key + i) < *(key + j)) {
            B[k] = *(key + i);
            A[k] = *(id + i);
            i++;
            k++;
        } else {
            B[k] = *(key + j);
            A[k] = *(id + j);
            j++;
            k++;
        }
    }
    while (i <= mid) {
        B[k] = *(key + i);
        A[k] = *(id + i);
        k++;
        i++;
    }
    while (j <= high) {
        B[k] = *(key + j);
        A[k] = *(id + j);
        k++;
        j++;
    }
    for (i = low; i <= high; i++) {
        *(key +i) = B[i];
        *(id + i) = A[i];
    }

}

void mergeSort(unsigned long long *key, int *id, int low, int high) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        mergeSort(key, id, low, mid);
        mergeSort(key, id, mid + 1, high);
        merge(key, id, mid, low, high);
    }
}

/**-------------------------------------------------------------------------------------------------------------------*/

char **alloc_matrix_char(int nlines, int ncolumns) {
    char **matrix = (char **) malloc(nlines * sizeof(char *));

    for (int i = 0; i < nlines; i++) {
        *(matrix + i) = (char *) malloc(NCOLUMNS * sizeof(char));
    }
    return matrix;
}