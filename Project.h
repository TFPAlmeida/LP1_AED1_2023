//
// Created by tiago on 19/11/2022.
//

#ifndef LP1_AED1_2023_PROJECT_H
#define LP1_AED1_2023_PROJECT_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct key_holder{
    int lines;
    int columns = 21;
    short **matrix_kpub_int;
    short **matrix_kpriv_int;
    short **matrix_kcod_int;
    char **matrix_kpub_char;
    char **matrix_kpriv_char;
    char **matrix_kcod_char;
}KEY_HOLDERE;

typedef struct porta_chaves{
    KEY_HOLDERE info;
    int geracao;
    int atualizacao;
    struct porta_chaves *pdown;
}PORTA_CHAVES;

typedef struct stack_porta_chaves{
    int nnodes;
    PORTA_CHAVES *ptop;
}STACK_PORTA_CHAVES;

typedef struct utilizador{
    char nome[100];
    char email[100];
    struct stack_porta_chaves info;
    struct utilizador *pdown;
}UTILIZADOR;

typedef struct stack_utilizadores{
    int nutilizadores;
    UTILIZADOR *ptop;
}STACK_UTILIZADOR;

/**-------------------------------------------------------------------------------------------------------------------*/

/**
 * Generate a random integer to be used as the public key.
 * @return random number representing a public key
 */
unsigned long long new_public_key_int(void);

/**
 * Create an array of digits for a given key.
* @param key - long key
 * @return address of array of digits for a given key
 */
short* key_long_2_digits_int(unsigned long long key);

/**
 * Receives an array of digits and returns the long key.
 * @param keydigits - array of digits of key
 * @return address of array of digits for a given key
 */
unsigned long long key_digits_2_long_int(const short* keydigits);

int verify_private_key(const short *privtkey);

int descending(const short *privtkey);

int ascending(const short *privtkey);

int countDistinct(const short *privtkey);

int init_size(unsigned long long key);


/**
 * Calculate the bipolar private key from a given public key (returns the bipolar private key).
 * @param pubkey - public key for which to calculate the private key
 * @return bipolar number representing the private key
 */
unsigned long long calc_private_key_int(unsigned long long pubkey);

/**
 * Calculate the run-length from a given private key.
 * @param privkey - private key for which to calculate the run-length
 * @return run-length number representing the private key
 */
unsigned long long calc_runlength_int(unsigned long long privtkey);

unsigned long long concatenar_key(int aux, short key, unsigned long long privtkey);

/**
 * Calculate the private key from a run-length.
 * @param runlengthkey - run-length for which to calculate the private key
 * @return private key that corresponds to the runlengthkey arg
 */
unsigned long long private_key_from_runlength_int(unsigned long long runlengthkey);

/**
 * Memory allocation for a int matrix with nlines and ncolumns
 * @param nlines - number of lines
 * @param ncolumns - number of columns
 * @return pointer to the allocated memory of the matrix
 */
short** alloc_matrix_int(int nlines, int ncolumns);

/**
 * Store a key (pub, priv or run-length) into the first available position of given matrix.
 * @param matrix - matrix to store the key
 * @param lines - matrix number of lines
 * @param key - key to be stored
 */
void store_key_int(short **matrix, int lines, unsigned long long key);

void print_key_int(short **matrix, int lines);

/**
 * Verify if a given key exists in the matrix.
 * @param matrix - matrix with keys
 * @param lines - matrix number of lines
 * @param key - key to check if it exists
 * @return 1 if it exists, 0 if it doesn't
 */
int exists_key_int(short **matrix, int lines, unsigned long long key);

int find_key_int(short **matrix, int lines, unsigned long long key);

/**
 * Returns the private key corresponding to the given public key
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param lines - matrix number of lines
 * @param pubkey - public key for which we want the private key
 * @return private key of the given pubkey
 */
unsigned long long get_private_key_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long pubkey);

/**
 * Returns the run-length key of a given private key
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param pubkey - public key for which we want the private key
 * @return private key runlength of the given pubkey
 */
unsigned long long get_runlength_int(short **matrix_kpriv, short **matrix_kcod, int lines, unsigned long long privkey);

/**
 * Delete a given public key (and corresponding priv and runlength keys) from all matrices.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param pubkey - public key to delete
 * @return pubkey that was deleted
 */
unsigned long long delete_key_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, short pubkey);

/**
 * Automatically generate and save a given amount (<lines>) of public keys.
 * @param matrix_kpub - public keys matrix
 * @param lines - matrix number of lines
 */
void bulk_populate_public_keys_int(short **matrix_kpub, int lines);

short* array_key(short **matrix, int i);

/**
 * Automatically calculate, generate and store all private keys for the existing public keys.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param lines - matrix number of lines
 */
void bulk_compute_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines);

/**
 * Automatically calculate and store all run-lengths for the existing private keys.
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 */
void bulk_compute_runlengths_int(short **matrix_kpriv, short **matrix_kcod, int lines);

/**
 * Return a list of all private keys matching a given partial public key.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param lines - matrix number of lines
 * @param partialpubkey - part of public key to filter the private keys
 * @return array of private keys matching the partialpubkey
 */
short** search_private_keys_int(short **matrix_kpub, short **matrix_kpriv, int lines, unsigned long long partialpubkey);
void copy_matrix(short **matrix, short **aux, int lines ,const int *id);
/**
 * Sort a matrix keys in ascending or descending order
 * @param matrix - matrix to be sorted
 * @param lines - matrix number of lines
 * @param order - order == 1 ? ascending : descending
 */
void sort_matrix_int(short **matrix, int lines, int order);

void merge(unsigned long long *key, int *id, int l, int m, int r, int order);
void mergeSort(unsigned long long *key, int *id, int l, int r, int orde);
/**
 * Sort all matrices keys in ascending or descending order
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param order - order == 1 ? ascending : descending
 */
void sort_all_matrices_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, int order);

/**
 * Print all keys on the console, sorted by pubkeys sizes (i.e. number of digits).
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param order - order == 0 ? current order : order == 1 ? ascending : descending
 */
void list_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, int order);

/**
 * Save all matrix data to a text file
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the text file where to store the data
 */
void save_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]);

/**
 * Loads data into the matrices from a text file.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the text file to load data from
 */
void load_txt_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]);

/**
 * Save all matrix data to a binary file
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the binary file where to store the data
 */
void save_bin_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]);

/**
 * Loads data into the matrices from a binary file.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename -name of the binary file to load data from
 */
void load_bin_keys_int(short **matrix_kpub, short **matrix_kpriv, short **matrix_kcod, int lines, char filename[]);

/**-------------------------------------------------------------------------------------------------------------------*/

/**
 * Create an array of digits in ascii i.e. chars for a given key.
* @param key - long key
 * @return address of array of digits in ascii for a given key
 */
char* key_long_2_digits_char(unsigned long long key);

/**
 * Receives an array of digits in ascii i.e. chars and returns the long key.
 * @param keydigits - array of digits of key
 * @return address of array of digits for a given key
 */
unsigned long long key_digits_2_long_char(char* keydigits);

/**
 * Calculate the bipolar private key from a given public key (returns the bipolar private key).
 * @param pubkey - public key for which to calculate the private key
 * @return bipolar number representing the private key
 */
unsigned long long calc_private_key_char(unsigned long long pubkey);

/**
 * Calculate the run-length from a given private key.
 * @param privkey - private key for which to calculate the run-length
 * @return run-length number representing the private key
 */
unsigned long long calc_runlength_char(unsigned long long privkey);

/**
 * Calculate the private key from a run-length.
 * @param runlengthkey - run-length for which to calculate the private key
 * @return private key that corresponds to the runlengthkey arg
 */
unsigned long long private_key_from_runlength_char(unsigned long long runlengthkey);

/**
 * Memory allocation for a char matrix with nlines and ncolumns
 * @param nlines - number of lines
 * @param ncolumns - number of columns
 * @return pointer to the allocated memory of the matrix
 */
char** alloc_matrix_char(int nlines, int ncolumns);

/**
 * Store a key (pub, priv or run-length) into the first available position of given matrix.
 * @param matrix - matrix to store the key
 * @param lines - matrix number of lines
 * @param key - key to be stored
 */
void store_key_char(char **matrix, int lines, unsigned long long key);

/**
 * Verify if a given key exists in the matrix.
 * @param matrix - matrix with keys
 * @param lines - matrix number of lines
 * @param key - key to check if it exists
 * @return 1 if it exists, 0 if it doesn't
 */
int exists_key_char(char **matrix, int lines, unsigned long long key);

/**
 * Returns the private key corresponding to the given public key
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param lines - matrix number of lines
 * @param pubkey - public key for which we want the private key
 * @return private key of the given pubkey
 */
unsigned long long get_private_key_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long pubkey);

/**
 * Returns the run-length key of a given private key
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param pubkey - public key for which we want the private key
 * @return private key runlength of the given pubkey
 */
unsigned long long get_runlength_char(char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long privkey);

/**
 * Delete a given public key (and corresponding priv and runlength keys) from all matrices.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param pubkey - public key to delete
 * @return pubkey that was deleted
 */

int find_key_char(char **matrix, int lines, unsigned long long key);
void print_key_char(char **matrix, int lines);
        unsigned long long delete_key_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, unsigned long long pubkey);

/**
 * Automatically generate and save a given amount (<lines>) of public keys.
 * @param matrix_kpub - public keys matrix
 * @param lines - matrix number of lines
 */
void bulk_populate_public_keys_char(char **matrix_kpub, int lines);

char *array_key_char(char **matrix, int i);

/**
 * Automatically calculate, generate and store all private keys for the existing public keys.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param lines - matrix number of lines
 */
void bulk_compute_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines);

/**
 * Automatically calculate and store all run-lengths for the existing private keys.
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 */
void bulk_compute_runlengths_char(char **matrix_kpriv, char **matrix_kcod, int lines);

/**
 * Return a list of all private keys matching a given partial public key.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param lines - matrix number of lines
 * @param partialpubkey - part of public key to filter the private keys
 * @return array of private keys matching the partialpubkey
 */
char** search_private_keys_char(char **matrix_kpub, char **matrix_kpriv, int lines, unsigned long long partialpubkey);

unsigned long long *array_key_char_v2(char **matrix, int *id, int lines);

void copy_matrix_char(char **matrix, char **aux, int lines, const int *id);

/**
 * Sort a matrix keys in ascending or descending order
 * @param matrix - matrix to be sorted
 * @param lines - matrix number of lines
 * @param order - order == 1 ? ascending : descending
 */
void sort_matrix_char(char **matrix, int lines, int order);

/**
 * Sort all matrices keys in ascending or descending order
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param order - order == 1 ? ascending : descending
 */
void sort_all_matrices_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order);

/**
 * Print all keys on the console, sorted by pubkeys sizes (i.e. number of digits).
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param order - order == 0 ? current order : order == 1 ? ascending : descending
 */
void list_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, int order);

/**
 * Save all matrix data to a text file
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the text file where to store the data
 */
void save_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);
int lines_matriz(char filename[]);
/**
 * Loads data into the matrices from a text file.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the text file to load data from
 */
void load_txt_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);

/**
 * Save all matrix data to a binary file
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename - name of the binary file where to store the data
 */
void save_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);

/**
 * Loads data into the matrices from a binary file.
 * @param matrix_kpub - public keys matrix
 * @param matrix_kpriv - private keys matrix
 * @param matrix_kcod - run-lengths matrix
 * @param lines - matrix number of lines
 * @param filename -name of the binary file to load data from
 */
void load_bin_keys_char(char **matrix_kpub, char **matrix_kpriv, char **matrix_kcod, int lines, char filename[]);


int main_project(int argc, const char *argv[]);

#endif //LP1_AED1_2023_PROJECT_H
