//
// Created by tiago on 29/11/2022.
//

#ifndef LP1_AED1_2023_MAIN_H
#define LP1_AED1_2023_MAIN_H

#include "Project.h"
typedef struct date{
    int dia;
    int mes;
    int ano;
    int hora;
    int min;
    int seg;
}DATE;

typedef struct key_holder{
    int lines;
    int columns;
    short **matrix_kpub_int;
    short **matrix_kpriv_int;
    short **matrix_kcod_int;
    char **matrix_kpub_char;
    char **matrix_kpriv_char;
    char **matrix_kcod_char;
}KEY_HOLDER;

typedef struct porta_chave{
    KEY_HOLDER *keyHolder;
    DATE geracao;
    DATE atualizacao;
    struct porta_chave *pdown;
}PORTA_CHAVE;

typedef struct porta_chaves{

    PORTA_CHAVE *ptop;
}PORTA_CHAVES;

typedef struct utilizador{
    char nome[100];
    char email[100];
    PORTA_CHAVES *portaChaves;
    struct utilizador *pdown;
}UTILIZADOR;

typedef struct utilizadores{
    UTILIZADOR *ptop;
}UTILIZADORES;

KEY_HOLDER *create_keyholder(int lines);
PORTA_CHAVES *criar_porta_chaves();
PORTA_CHAVE *criar_porta_chave(KEY_HOLDER *keyHolder);
void inserir_porta_chave(PORTA_CHAVES *portaChaves, PORTA_CHAVE *portaChave);
void remove_porta_chave(PORTA_CHAVES *portaChaves, PORTA_CHAVE *portaChave);
int find_key_porta_chave(PORTA_CHAVES *portaChaves, PORTA_CHAVE *portaChave, unsigned long long key);
UTILIZADORES *criar_utilizadores();
UTILIZADOR *criar_utilizador(char *nome, char *email);
void inserir_utilizador_cabeca(UTILIZADORES *utilizadores, UTILIZADOR *utilizador);
void inserir_utilizador_cauda(UTILIZADORES *utilizadores, UTILIZADOR *utilizador);
void inserir_ordenado_nome(UTILIZADORES *utilizadores, UTILIZADOR *utilizador);
UTILIZADOR *pesquisar_utilizador_nome(UTILIZADORES *utilizadores, char *nome);
void remover_utilizador(UTILIZADORES *utilizadores, UTILIZADOR *utilizador);
PORTA_CHAVE *inserir_portachave_no_utilizador(UTILIZADOR *utilizador, PORTA_CHAVE *portaChave);
void remover_portachave_no_utilizador(UTILIZADOR *utilizador, PORTA_CHAVE *portaChave);
void imprimir_utilizadores(UTILIZADORES *utilizadores);
void imprimir_portachaves(PORTA_CHAVES *portaChaves);
void escrever_ficheiro_txt(UTILIZADORES *utilizadores, char filename[]);
void load_portachaves_txt(PORTA_CHAVES *portaChaves, char filename[]);
#endif //LP1_AED1_2023_MAIN_H
