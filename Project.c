//
// Created by tiago on 19/11/2022.
//

#include "Project.h"

#define NLINES 200
#define NCOLUMNS 200

int main_project(int argc, const char *argv[]) {

    /**--------------------------------------------------------------------------------------------------------------**/
    //int lines = 8;

    //char file_INFO_TXT_INT[] = "C:\\Users\\tiago\\CLionProjects\\LP1_AED1_2023\\INFO_TXT_INT";
    //char file_LOAD_TXT_INT[] = "C:\\Users\\tiago\\CLionProjects\\LP1_AED1_2023\\KEYS_INT";

    //short **matrix_pubs_int = alloc_matrix_int(NLINES, NCOLUMNS);
    //short **matrix_priv_int = alloc_matrix_int(NLINES, NCOLUMNS);
    //short **matrix_rle_int = alloc_matrix_int(NLINES, NCOLUMNS);

    //bulk_populate_public_keys_int(matrix_pubs_int, lines);
    //bulk_compute_private_keys_int(matrix_pubs_int, matrix_priv_int, lines);
    //bulk_compute_runlengths_int(matrix_priv_int, matrix_rle_int, lines);

    //delete_key_int(matrix_pubs_int, matrix_priv_int, matrix_rle_int, lines, 335);
    //delete_key_int(matrix_pubs_int, matrix_priv_int, matrix_rle_int, lines, 468);
    //int n1 = lines_matriz(file_LOAD_TXT_INT);
    //lines = n1;
    //load_txt_keys_int(matrix_pubs_int, matrix_priv_int, matrix_rle_int, lines, file_LOAD_TXT_INT);
    //list_keys_int(matrix_pubs_int, matrix_priv_int, matrix_rle_int, lines, 1);
    //save_txt_keys_int(matrix_pubs_int, matrix_priv_int, matrix_rle_int, lines, file_INFO_TXT_INT);
    /**---------------------------------------------------------------------------------------------------------------*/
    /*char file_INFO_TXT_CHAR[] = "C:\\Users\\tiago\\CLionProjects\\LP1_AED1_2023\\INFO_TXT_CHAR";
    char file_LOAD_TXT_CHAR[] = "C:\\Users\\tiago\\CLionProjects\\LP1_AED1_2023\\KEYS_CHAR";

    char **matrix_pubs_char = alloc_matrix_char(NLINES, NCOLUMNS);
    char **matrix_priv_char = alloc_matrix_char(NLINES, NCOLUMNS);
    char **matrix_rle_char = alloc_matrix_char(NLINES, NCOLUMNS);

    bulk_populate_public_keys_char(matrix_pubs_char, lines);
    bulk_compute_private_keys_char(matrix_pubs_char, matrix_priv_char, lines);
    bulk_compute_runlengths_char(matrix_priv_char, matrix_rle_char, lines);

    load_txt_keys_char(matrix_pubs_char, matrix_priv_char, matrix_rle_char, lines, file_LOAD_TXT_CHAR);
    list_keys_char(matrix_pubs_char, matrix_priv_char, matrix_rle_char, lines, 1);
    save_txt_keys_char(matrix_pubs_char, matrix_priv_char, matrix_rle_char, lines, file_INFO_TXT_CHAR);*/

    /**---------------------------------------------------------------------------------------------------------------*/
    return 0;
}

int lines_matriz(char filename[]){
    FILE *arquivoINFO = NULL;
    if ((arquivoINFO = fopen(filename, "r")) == NULL) {
        fprintf(stdout, "ERRO\n");
        return 0;
    }
    char aux[100];
    int n1 = 0;
    fgets(aux, 100, arquivoINFO);
    n1 = atoi(aux);
    fclose(arquivoINFO);
    return n1;
}

unsigned long long new_public_key_int(void) {

    unsigned long long key = rand() % 300 + 1;
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
    short **matrix = (short **) malloc(nlines* sizeof(short *));

    for (int i = 0; i < nlines; i++) {
        *(matrix + i) = (short *) malloc(ncolumns * sizeof(short));
    }
    return matrix;
}

void store_key_int(short **matrix, int lines, unsigned long long key) {
    int count = init_size(key);
    short *key_matrix = key_long_2_digits_int(key);

    for (int i = 0; i < count; i++) {
        *(*(matrix + i) + lines) = *(key_matrix + i);
    }
    *(*(matrix + count) + lines) = -1;
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
    short *key = (short *) malloc(21 * sizeof(short));
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

void copy_matrix(short **matrix, short **aux, int lines, const int *id) {
    int n = 0;
    for (int k = 0; k < lines; k++) {
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
    mergeSort(key, id, 0, lines - 1, order);
    int n = 0;
    for (int i = 0; i < lines; i++) {
        copy_matrix(matrix, aux, lines, id);
    }

    for (int i = 0; i < lines; i++) {
        for (n = 0; *(*(aux + n) + i) != -1; n++) {
            *(*(matrix + n) + i) = *(*(aux + n) + i);

        }
        *(*(matrix + n) + i) = -1;
    }

}


void merge(unsigned long long *key, int *id, int mid, int low, int high, int order) {
    int i, j, k;
    unsigned long long B[100];
    int A[100];
    i = low;
    j = mid + 1;
    k = low;
    if (order == 1) {
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
            *(key + i) = B[i];
            *(id + i) = A[i];
        }
    } else {
        while (i <= mid && j <= high) {
            if (*(key + i) > *(key + j)) {
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
            *(key + i) = B[i];
            *(id + i) = A[i];
        }
    }


}

void mergeSort(unsigned long long *key, int *id, int low, int high, int order) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;
        mergeSort(key, id, low, mid, order);
        mergeSort(key, id, mid + 1, high, order);
        merge(key, id, mid, low, high, order);
    }
}

void sort_all_matrices_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, int order) {
    sort_matrix_int(matrix_kpub, lines, order);
    sort_matrix_int(matrix_kpriv, lines, order);
    sort_matrix_int(matrix_kcod, lines, order);
}

void list_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, int order) {
    sort_all_matrices_int(matrix_kpub, matrix_kpriv, matrix_kcod, lines, order);
    printf("------------------------------------------------------------------\n");
    print_key_int(matrix_kpub, lines);
    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("\n");
    print_key_int(matrix_kpriv, lines);
    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("\n");
    print_key_int(matrix_kcod, lines);
    printf("\n");
}

void save_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]) {
    FILE *arquivoINFO = NULL;

    if ((arquivoINFO = fopen(filename, "w")) == NULL) {
        fprintf(stdout, "ERRO\n");
        return;
    }

    for (int i = 0; i < lines; i++) {
        for (int n = 0; *(*(matrix_kpub + n) + i) != -1; n++) {
            fprintf(arquivoINFO, "%d ", *(*(matrix_kpub + n) + i));
        }
        fprintf(arquivoINFO, "\n ");
    }

    fprintf(arquivoINFO, "/*------------------------------------------*/\n");
    fprintf(arquivoINFO, "\n ");

    for (int i = 0; i < lines; i++) {
        for (int n = 0; *(*(matrix_kpriv + n) + i) != -1; n++) {
            fprintf(arquivoINFO, "%d ", *(*(matrix_kpriv + n) + i));
        }
        fprintf(arquivoINFO, "\n ");
    }

    fprintf(arquivoINFO, "/*------------------------------------------*/\n");
    fprintf(arquivoINFO, "\n ");

    for (int i = 0; i < lines; i++) {
        for (int n = 0; *(*(matrix_kcod + n) + i) != -1; n++) {
            fprintf(arquivoINFO, "%d ", *(*(matrix_kcod + n) + i));
        }
        fprintf(arquivoINFO, "\n ");
    }

}

void load_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]) {
    FILE *arquivoINFO;

    if ((arquivoINFO = fopen(filename, "r")) == NULL) {
        fprintf(stdout, "ERRO\n");
        return;
    }
    char aux[100];
    int i = 1, x = 0, y = 0, z = 0, n1 = 0, n2 = 0, n3 = 0, k = 0;
    while (!feof(arquivoINFO)) {

// Lê uma linha (inclusive com o '\n')
        fgets(aux, 100, arquivoINFO);  // o 'fgets' lê até 99 caracteres ou até o '\n'
        if (i == 1) {
            n1 = atoi(aux);
        } else if (i == n1 + 2) {
            n2 = atoi(aux);
        } else if (i == n1 + n2 + 3) {
            n3 = atoi(aux);
        }

        if (i <= n1 + 1 && i != 1) {
            unsigned long long key = atoi(aux);
            short *arr = key_long_2_digits_int(key);
            for (k = 0; *(arr + k) != -1; k++) {
                *(*(matrix_kpub + k) + x) = *(arr + k);
            }
            *(*(matrix_kpub + k) + x) = -1;
            x++;
        } else if (i <= n1 + n2 + 2 && i != 1 && i != n1 + 2) {
            unsigned long long key = atoi(aux);
            short *arr = key_long_2_digits_int(key);
            for (k = 0; *(arr + k) != -1; k++) {
                *(*(matrix_kpriv + k) + y) = *(arr + k);
            }
            *(*(matrix_kpriv + k) + y) = -1;
            y++;
        } else if (i <= n1 + n2 + n3 + 3 && i != 1 && i != n1 + n2 + 3 && i != n1 + 2) {
            unsigned long long key = atoi(aux);
            short *arr = key_long_2_digits_int(key);
            for (k = 0; *(arr + k) != -1; k++) {
                *(*(matrix_kcod + k) + z) = *(arr + k);
            }
            *(*(matrix_kcod + k) + z) = -1;
            z++;
        }
        i++;

    }


}

/**-------------------------------------------------------------------------------------------------------------------*/

char *key_long_2_digits_char(unsigned long long key) {
    unsigned long long mod = 0;
    int count = init_size(key);
    char *aux = (char *) malloc(count + 1 * sizeof(char));
    char *key1 = (char *) malloc(count + 1 * sizeof(char));
    int j = count - 1, i = 0;
    for (i = 0; i < count; i++) {
        mod = key % 10;
        *(aux + i) = mod + '0';
        *(key1 + j) = *(aux + i);
        key = key / 10;
        j--;
    }
    *(key1 + i) = '\0';
    return key1;
}

unsigned long long key_digits_2_long_char(char *keydigits) {
    unsigned long long key = 0;

    for (int i = 0; *(keydigits + i) != '\0'; i++) {
        key = (key * 10 + *(keydigits + i)) - '0';
    }
    return key;
}

unsigned long long calc_private_key_char(unsigned long long pubkey) {
    unsigned long long privkey = calc_private_key_int(pubkey);
    return privkey;
}

unsigned long long calc_runlength_char(unsigned long long privkey) {
    unsigned long long privtkey_rle = calc_runlength_int(privkey);
    return privtkey_rle;
}

unsigned long long private_key_from_runlength_char(unsigned long long runlengthkey) {
    unsigned long long privtkey = private_key_from_runlength_int(runlengthkey);
    return privtkey;
}

char **alloc_matrix_char(int nlines, int ncolumns) {
    char **matrix = (char **) malloc(nlines * sizeof(char *));

    for (int i = 0; i < nlines; i++) {
        *(matrix + i) = (char *) malloc(ncolumns * sizeof(char));
    }
    return matrix;
}

void store_key_char(char **matrix, int lines, unsigned long long key) {
    char *key_matrix = key_long_2_digits_char(key);

    int i = 0;
    for (i = 0; *(key_matrix + i) != '\0'; i++) {
        *(*(matrix + i) + lines) = *(key_matrix + i);
    }
    *(*(matrix + i) + lines) = '\0';

}

int exists_key_char(char **matrix, int lines, unsigned long long key) {
    char *key_matrix = key_long_2_digits_char(key);
    int count = 0, n = 0;
    for (int i = 0; i < lines; i++) {
        for (n = 0; *(key_matrix + n) != '\0'; n++) {
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

unsigned long long get_private_key_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long pubkey) {
    int h1 = exists_key_char(matrix_kpub, lines, pubkey);
    unsigned long long privkey = calc_private_key_char(pubkey);
    int h2 = exists_key_char(matrix_kpriv, lines, privkey);

    if (h1 == 1 && h2 == 1) {
        return privkey;
    }
    return 0;
}

unsigned long long get_runlength_char(char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long privkey) {
    int h1 = exists_key_char(matrix_kpriv, lines, privkey);
    unsigned long long codkey = calc_runlength_char(privkey);
    int h2 = exists_key_char(matrix_kcod, lines, codkey);

    if (h1 == 1 && h2 == 1) {
        return codkey;
    }
    return 0;
}

int find_key_char(char **matrix, int lines, unsigned long long key) {
    char *key_matrix = key_long_2_digits_char(key);
    int count = 0, n = 0;

    for (int i = 1; i <= lines; i++) {
        for (n = 0; *(*(matrix + n) + i) != '\0'; n++) {
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
delete_key_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long pubkey) {

    int h1 = exists_key_char(matrix_kpub, lines, pubkey);
    unsigned long long privkey = calc_private_key_char(pubkey);
    int h2 = exists_key_char(matrix_kpriv, lines, privkey);
    unsigned long long codkey = calc_runlength_char(privkey);
    int h3 = exists_key_char(matrix_kcod, lines, codkey);
    int i = 0, n = 0, j = 0, k = 0;
    if (h1 == 1) {
        i = find_key_char(matrix_kpub, lines, pubkey);
        strcpy(*(matrix_kpub) + i, "\0");
    }
    if (h2 == 1) {
        n = find_key_char(matrix_kpriv, lines, privkey);
        strcpy(*(matrix_kpriv) + n, "\0");
    }
    if (h3 == 1) {
        j = find_key_char(matrix_kcod, lines, codkey);
        strcpy(*(matrix_kcod) + j, "\0");
    }

    return pubkey;
}

void print_key_char(char **matrix, int lines) {

    for (int i = 0; i < lines; i++) {
        for (int n = 0; *(*(matrix + n) + i) != '\0'; n++) {
            printf("%c ", *(*(matrix + n) + i));
        }
        if (*(*(matrix + 0) + i) != '\0') {
            printf("\n");
        }
    }
}

void bulk_populate_public_keys_char(char **matrix_kpub, int lines){
    for(int i = 0; i < lines; i++){
        unsigned long long pubkey = new_public_key_int();
        store_key_char(matrix_kpub, i, pubkey);
    }
}

char *array_key_char(char **matrix, int i) {
    int n = 0;
    char *key = (char *) malloc(20 * sizeof(char));
    for (n = 0; *(*(matrix + n) + i) != '\0'; n++) {
        *(key + n) = *(*(matrix + n) + i);
    }

    *(key + n) = '\0';
    return key;
}

void bulk_compute_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines){
    char *key = NULL;
    for(int i = 0; i < lines; i++){
        key = array_key_char(matrix_kpub, i);
        unsigned long long pubkey = key_digits_2_long_char(key);
        unsigned long long privkey = calc_private_key_char(pubkey);
        store_key_char(matrix_kpriv, i, privkey);
    }
}

void bulk_compute_runlengths_char(char **matrix_kpriv, char **matrix_kcod, int lines){
    char *key = NULL;
    for(int i = 0; i < lines; i++){
        key = array_key_char(matrix_kpriv, i);
        unsigned long long privkey = key_digits_2_long_char(key);
        unsigned long long codkey = calc_runlength_char(privkey);
        store_key_char(matrix_kcod, i, codkey);
    }
}

unsigned long long *array_key_char_v2(char **matrix, int *id, int lines) {

    unsigned long long *key = (unsigned long long *) malloc(lines * sizeof(unsigned long long));

    char *aux = NULL;
    for (int i = 0; i < lines; i++) {
        aux = array_key_char(matrix, i);
        *(id + i) = i;
        *(key + i) = key_digits_2_long_char(aux);
    }
    return key;
}

void copy_matrix_char(char **matrix, char **aux, int lines, const int *id) {
    int n = 0;
    for (int k = 0; k < lines; k++) {
        for (n = 0; *(*(matrix + n) + *(id + k)) != '\0'; n++) {
            *(*(aux + n) + k) = *(*(matrix + n) + *(id + k));
        }
        *(*(aux + n) + k) = '\0';
    }
}

void sort_matrix_char(char **matrix, int lines, int order){
    int *id = (int *) malloc(lines * sizeof(int));
    unsigned long long *key = array_key_char_v2(matrix, id, lines);
    char **aux = alloc_matrix_char(NLINES, NCOLUMNS);
    mergeSort(key, id, 0, lines - 1, order);
    int n = 0;
    for (int i = 0; i < lines; i++) {
        copy_matrix_char(matrix, aux, lines, id);
    }

    for (int i = 0; i < lines; i++) {
        for (n = 0; *(*(aux + n) + i) != '\0'; n++) {
            *(*(matrix + n) + i) = *(*(aux + n) + i);
        }
        *(*(matrix + n) + i) = '\0';
    }
}

void sort_all_matrices_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){
    sort_matrix_char(matrix_kpub, lines, order);
    sort_matrix_char(matrix_kpriv, lines, order);
    sort_matrix_char(matrix_kcod, lines, order);
}

void list_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order){
    sort_all_matrices_char(matrix_kpub, matrix_kpriv, matrix_kcod, lines, order);
    printf("------------------------------------------------------------------\n");
    print_key_char(matrix_kpub, lines);
    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("\n");
    print_key_char(matrix_kpriv, lines);
    printf("\n");
    printf("------------------------------------------------------------------\n");
    printf("\n");
    print_key_char(matrix_kcod, lines);
    printf("\n");
}

void save_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    FILE *arquivoINFO = NULL;

    if ((arquivoINFO = fopen(filename, "w")) == NULL) {
        fprintf(stdout, "ERRO\n");
        return;
    }

    for (int i = 0; i < lines; i++) {
        for (int n = 0; *(*(matrix_kpub + n) + i) != '\0'; n++) {
            fprintf(arquivoINFO, "%d ", *(*(matrix_kpub + n) + i) - '0');
        }
        fprintf(arquivoINFO, "\n ");
    }

    fprintf(arquivoINFO, "/*------------------------------------------*/\n");
    fprintf(arquivoINFO, "\n ");

    for (int i = 0; i < lines; i++) {
        for (int n = 0; *(*(matrix_kpriv + n) + i) != '\0'; n++) {
            fprintf(arquivoINFO, "%d ", *(*(matrix_kpriv + n) + i) - '0');
        }
        fprintf(arquivoINFO, "\n ");
    }

    fprintf(arquivoINFO, "/*------------------------------------------*/\n");
    fprintf(arquivoINFO, "\n ");

    for (int i = 0; i < lines; i++) {
        for (int n = 0; *(*(matrix_kcod + n) + i) != '\0'; n++) {
            fprintf(arquivoINFO, "%d ", *(*(matrix_kcod + n) + i) - '0');
        }
        fprintf(arquivoINFO, "\n ");
    }
}

void load_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]){
    FILE *arquivoINFO;

    if ((arquivoINFO = fopen(filename, "r")) == NULL) {
        fprintf(stdout, "ERRO\n");
        return;
    }
    char aux[100];
    int i = 1, x = 0, y = 0, z = 0, n1 = 0, n2 = 0, n3 = 0, k = 0;
    while (!feof(arquivoINFO)) {

// Lê uma linha (inclusive com o '\n')
        fgets(aux, 100, arquivoINFO);  // o 'fgets' lê até 99 caracteres ou até o '\n'
        if (i == 1) {
            n1 = atoi(aux);
        } else if (i == n1 + 2) {
            n2 = atoi(aux);
        } else if (i == n1 + n2 + 3) {
            n3 = atoi(aux);
        }

        if (i <= n1 + 1 && i != 1) {
            unsigned long long key = atoi(aux);
            char *arr = key_long_2_digits_char(key);
            for (k = 0; *(arr + k) != '\0'; k++) {
                *(*(matrix_kpub + k) + x) = *(arr + k);
            }
            *(*(matrix_kpub + k) + x) = '\0';
            x++;
            //strcpy(aux, "");
        } else if (i <= n1 + n2 + 2 && i != 1 && i != n1 + 2) {

            unsigned long long key = atoi(aux);
            char *arr = key_long_2_digits_char(key);
            for (k = 0; *(arr + k) != '\0'; k++) {
                *(*(matrix_kpriv + k) + y) = *(arr + k);
            }
            *(*(matrix_kpriv + k) + y) = '\0';
            y++;
        } else if (i <= n1 + n2 + n3 + 3 && i != 1 && i != n1 + n2 + 3 && i != n1 + 2) {
            unsigned long long key = atoi(aux);
            char *arr = key_long_2_digits_char(key);
            for (k = 0; *(arr + k) != '\0'; k++) {
                *(*(matrix_kcod + k) + z) = *(arr + k);
            }
            *(*(matrix_kcod + k) + z) = '\0';
            z++;
        }
        i++;

    }
}




