#include <stdio.h>
#include "main.h"

int aux = 0;

int main(int argc, const char *argv[]) {
    char file_INFO_TXT_LISTA_UTILIZADORES[] = "C:\\Users\\tiago\\CLionProjects\\LP1_AED1_2023\\INFO_TXT_LISTA_UTILIZADORES";
    char file_LOAD_TXT_LISTA_PORTACHAVES[] = "C:\\Users\\tiago\\CLionProjects\\LP1_AED1_2023\\INFO_TXT_PORTACHAVES";
    char file_INFO_BIN_LISTA_UTILIZADORES[] = "C:\\Users\\tiago\\CLionProjects\\LP1_AED1_2023\\INFO_BIN_LISTA_UTILIZADORES";
    /**--------------------------------------------------------------------------------------------------------------**/
    KEY_HOLDER *keyHolder1 = create_keyholder(10, 1);
    KEY_HOLDER *keyHolder2 = create_keyholder(10, 1);
    KEY_HOLDER *keyHolder3 = create_keyholder(10, 1);
    /**--------------------------------------------------------------------------------------------------------------**/
    UTILIZADORES *utilizadores = criar_utilizadores();
    UTILIZADOR *utilizador1 = criar_utilizador("Tiago", "tiago@gmail.com");
    UTILIZADOR *utilizador2 = criar_utilizador("Marcio", "marcio@gmail.com");
    //inserir_ordenado_nome(utilizadores, criar_utilizador("Maria", "maria@gmail.com"));
    //inserir_ordenado_nome(utilizadores, criar_utilizador("Jose", "jose@gmail.com"));
    //inserir_ordenado_nome(utilizadores, criar_utilizador("Carlos", "carlos@gmail.com"));
    //inserir_ordenado_nome(utilizadores, criar_utilizador("Beatriz", "biatriz@gmail.com"));
    /**--------------------------------------------------------------------------------------------------------------**/
    inserir_utilizador_cabeca(utilizadores, utilizador1);
    inserir_utilizador_cabeca(utilizadores, utilizador2);
    imprimir_utilizadores(utilizadores);
    /**--------------------------------------------------------------------------------------------------------------**/
    PORTA_CHAVE *portaChave1 = criar_porta_chave(keyHolder1);
    PORTA_CHAVE *portaChave2 = criar_porta_chave(keyHolder2);
    PORTA_CHAVE *portaChave3 = criar_porta_chave(keyHolder3);
    /**--------------------------------------------------------------------------------------------------------------**/
    inserir_portachave_no_utilizador(utilizador1, portaChave1);
    inserir_portachave_no_utilizador(utilizador1, portaChave2);
    aux = 0;
    inserir_portachave_no_utilizador(utilizador2, portaChave3);

    //remover_portachave_no_utilizador(utilizador, portaChave1);
    //imprimir_portachaves(utilizador1->portaChaves);
    escrever_ficheiro_txt(utilizadores, file_INFO_TXT_LISTA_UTILIZADORES);
    escrever_ficheiro_bin(utilizadores, file_INFO_BIN_LISTA_UTILIZADORES);
    /**--------------------------------------------------------------------------------------------------------------**/
    //PORTA_CHAVES *portaChaves = criar_porta_chaves();
    //load_portachaves_txt(portaChaves, file_LOAD_TXT_LISTA_PORTACHAVES);
    //imprimir_portachaves(portaChaves);
    return 0;
}

KEY_HOLDER *create_keyholder(int lines, int order) {
    srand(time(NULL));
    KEY_HOLDER keyHolder = {0, 0, NULL, NULL, NULL, NULL, NULL, NULL};
    KEY_HOLDER *keyHolder_n = (KEY_HOLDER *) malloc(sizeof(keyHolder));
    keyHolder_n->lines = lines;
    keyHolder_n->columns = 21;
    keyHolder_n->matrix_kpub_int = alloc_matrix_int(keyHolder_n->lines, keyHolder_n->columns);
    keyHolder_n->matrix_kpub_char = alloc_matrix_char(keyHolder_n->lines, keyHolder_n->columns);
    keyHolder_n->matrix_kpriv_int = alloc_matrix_int(keyHolder_n->lines, keyHolder_n->columns);
    keyHolder_n->matrix_kpriv_char = alloc_matrix_char(keyHolder_n->lines, keyHolder_n->columns);
    keyHolder_n->matrix_kcod_int = alloc_matrix_int(keyHolder_n->lines, keyHolder_n->columns);
    keyHolder_n->matrix_kcod_char = alloc_matrix_char(keyHolder_n->lines, keyHolder_n->columns);

    bulk_populate_public_keys_int(keyHolder_n->matrix_kpub_int, keyHolder_n->lines);
    bulk_compute_private_keys_int(keyHolder_n->matrix_kpub_int, keyHolder_n->matrix_kpriv_int, keyHolder_n->lines);
    bulk_compute_runlengths_int(keyHolder_n->matrix_kpriv_int, keyHolder_n->matrix_kcod_int, keyHolder_n->lines);
    sort_all_matrices_int(keyHolder_n->matrix_kpub_int,keyHolder_n->matrix_kpriv_int,keyHolder_n->matrix_kcod_int,keyHolder_n->lines,order);
    bulk_populate_public_keys_char(keyHolder_n->matrix_kpub_char, keyHolder_n->lines);
    bulk_compute_private_keys_char(keyHolder_n->matrix_kpub_char, keyHolder_n->matrix_kpriv_char, keyHolder_n->lines);
    bulk_compute_runlengths_char(keyHolder_n->matrix_kpriv_char, keyHolder_n->matrix_kcod_char, keyHolder_n->lines);
    sort_all_matrices_char(keyHolder_n->matrix_kpub_char,keyHolder_n->matrix_kpriv_char,keyHolder_n->matrix_kcod_char,keyHolder_n->lines,order);
    return keyHolder_n;
}

PORTA_CHAVES *criar_porta_chaves() {
    PORTA_CHAVES *portaChaves = malloc(sizeof(PORTA_CHAVES));
    portaChaves->ptop = NULL;
    return portaChaves;
}

PORTA_CHAVE *criar_porta_chave(KEY_HOLDER *keyHolder) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    PORTA_CHAVE *portaChave = malloc(sizeof(PORTA_CHAVE));
    DATE date = {0, 0, 0, 0, 0, 0};
    portaChave->atualizacao = date;
    portaChave->keyHolder = keyHolder;
    portaChave->geracao.ano = tm.tm_year + 1900;
    portaChave->geracao.mes = tm.tm_mon + 1;
    portaChave->geracao.dia = tm.tm_mday;
    portaChave->geracao.hora = tm.tm_hour;
    portaChave->geracao.min = tm.tm_min;
    portaChave->geracao.seg = tm.tm_sec;
    portaChave->pdown = NULL;
    return portaChave;
}

PORTA_CHAVE *load_porta_chave() {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    PORTA_CHAVE *portaChave = malloc(sizeof(PORTA_CHAVE));
    DATE date = {0, 0, 0, 0, 0, 0};
    portaChave->atualizacao = date;
    portaChave->keyHolder = NULL;
    portaChave->geracao.ano = tm.tm_year + 1900;
    portaChave->geracao.mes = tm.tm_mon + 1;
    portaChave->geracao.dia = tm.tm_mday;
    portaChave->geracao.hora = tm.tm_hour;
    portaChave->geracao.min = tm.tm_min;
    portaChave->geracao.seg = tm.tm_sec;
    portaChave->pdown = NULL;
    return portaChave;
}


void inserir_porta_chave(PORTA_CHAVES *portaChaves, PORTA_CHAVE *portaChave) {
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);
    portaChave->pdown = portaChaves->ptop;
    portaChave->atualizacao.ano = tm.tm_year + 1900;
    portaChave->atualizacao.mes = tm.tm_mon + 1;
    portaChave->atualizacao.dia = tm.tm_mday;
    portaChave->atualizacao.hora = tm.tm_hour;
    portaChave->atualizacao.min = tm.tm_min;
    portaChave->atualizacao.seg = tm.tm_sec;
    portaChaves->ptop = portaChave;
}

void remove_porta_chave(PORTA_CHAVES *portaChaves, PORTA_CHAVE *portaChave) {
    PORTA_CHAVE *pdwon = NULL;
    PORTA_CHAVE *pc = portaChaves->ptop;
    while (pc != NULL) {
        if (pc == portaChave) {
            if (pdwon == NULL)
                portaChaves->ptop = pc->pdown;
            else
                pdwon->pdown = pc->pdown;
            free(pc);
            break;
        }
        //incrementar
        pdwon = pc;
        pc = pc->pdown;
    }
}

int find_key_porta_chave(PORTA_CHAVES *portaChaves, PORTA_CHAVE *portaChave, unsigned long long key) {
    PORTA_CHAVE *pdwon = NULL;
    PORTA_CHAVE *pc = portaChaves->ptop;
    while (pc != NULL) {
        if (pc == portaChave) {
            if (exists_key_int(pc->keyHolder->matrix_kpub_int, pc->keyHolder->lines, key) == 1) {
                printf("Find key in matrix_kpub_int!\n");
                return 1;
            } else if (exists_key_int(pc->keyHolder->matrix_kpriv_int, pc->keyHolder->lines, key) == 1) {
                printf("Find key in matrix_kpriv_int!\n");
                return 1;
            } else if (exists_key_int(pc->keyHolder->matrix_kcod_int, pc->keyHolder->lines, key) == 1) {
                printf("Find key in matrix_kcod_int!\n");
                return 1;
            } else if (exists_key_char(pc->keyHolder->matrix_kpub_char, pc->keyHolder->lines, key) == 1) {
                printf("Find key in matrix_kpub_char!\n");
                return 1;
            } else if (exists_key_char(pc->keyHolder->matrix_kpriv_char, pc->keyHolder->lines, key) == 1) {
                printf("Find key in matrix_kpriv_char!\n");
                return 1;
            } else if (exists_key_char(pc->keyHolder->matrix_kcod_char, pc->keyHolder->lines, key) == 1) {
                printf("Find key in matrix_kcod_char!\n");
                return 1;
            }
        }
        //incrementar
        pdwon = pc;
        pc = pc->pdown;
    }
    return 0;
}

UTILIZADORES *criar_utilizadores() {
    UTILIZADORES *utilizadores = malloc(sizeof(UTILIZADORES));
    utilizadores->ptop = NULL;
    return utilizadores;
}

UTILIZADOR *criar_utilizador(char *nome, char *email) {
    UTILIZADOR *utilizador = malloc(sizeof(UTILIZADOR));
    strcpy(utilizador->nome, nome);
    strcpy(utilizador->email, email);
    utilizador->portaChaves = NULL;
    utilizador->pdown = NULL;
    return utilizador;
}

void inserir_utilizador_cabeca(UTILIZADORES *utilizadores, UTILIZADOR *utilizador) {
    utilizador->pdown = utilizadores->ptop;
    utilizadores->ptop = utilizador;
}

void inserir_utilizador_cauda(UTILIZADORES *utilizadores, UTILIZADOR *utilizador) {
    if (utilizadores->ptop == NULL) {
        utilizadores->ptop = utilizador;
        return;
    }
    UTILIZADOR *utilizador1 = utilizadores->ptop;
    while (utilizador1->pdown != NULL) {
        utilizador1 = utilizador1->pdown;
    }

    utilizador1->pdown = utilizador;
}

void inserir_ordenado_nome(UTILIZADORES *utilizadores, UTILIZADOR *utilizador) {
    if (utilizadores->ptop == NULL) {
        utilizadores->ptop = utilizador;
        return;
    }
    if (strcmp(utilizador->nome, utilizadores->ptop->nome) < 0) {
        utilizador->pdown = utilizadores->ptop;
        utilizadores->ptop = utilizador;
        return;
    }
    UTILIZADOR *ut = utilizadores->ptop;
    while (ut->pdown != NULL && strcmp(ut->pdown->nome, utilizador->nome) < 0) {
        ut = ut->pdown;
    }
    utilizador->pdown = ut->pdown;
    ut->pdown = utilizador;
}

UTILIZADOR *pesquisar_utilizador_nome(UTILIZADORES *utilizadores, char *nome) {
    UTILIZADOR *ut = utilizadores->ptop;
    while (ut != NULL) {
        if (strcmp(ut->nome, nome) == 0) {
            return ut;
        }
        ut = ut->pdown;
    }
    return NULL;
}

void remover_utilizador(UTILIZADORES *utilizadores, UTILIZADOR *utilizador) {
    UTILIZADOR *pdown = NULL;
    UTILIZADOR *ut = utilizadores->ptop;

    while (ut != NULL) {
        if (ut == utilizador) {
            if (pdown == NULL)
                utilizadores->ptop = ut->pdown;
            else
                pdown->pdown = ut->pdown;
        }
        pdown = ut;
        ut = ut->pdown;
    }
}

PORTA_CHAVE *inserir_portachave_no_utilizador(UTILIZADOR *utilizador, PORTA_CHAVE *portaChave) {
    if (aux == 0) {
        utilizador->portaChaves = criar_porta_chaves();
    }
    inserir_porta_chave(utilizador->portaChaves, portaChave);
    aux = 1;
    return portaChave;
}

void remover_portachave_no_utilizador(UTILIZADOR *utilizador, PORTA_CHAVE *portaChave) {
    remove_porta_chave(utilizador->portaChaves, portaChave);
}

void imprimir_utilizadores(UTILIZADORES *utilizadores) {

    UTILIZADOR *utilizador = utilizadores->ptop;
    while (utilizador != NULL) {
        printf("%-15s %s\n", utilizador->nome, utilizador->email);
        utilizador = utilizador->pdown;
    }
}

void imprimir_portachaves(PORTA_CHAVES *portaChaves) {
    PORTA_CHAVE *portaChave = portaChaves->ptop;
    while (portaChave != NULL) {
        list_keys_int(portaChave->keyHolder->matrix_kpub_int, portaChave->keyHolder->matrix_kpriv_int,
                      portaChave->keyHolder->matrix_kcod_int,
                      portaChave->keyHolder->lines, 1);
        list_keys_char(portaChave->keyHolder->matrix_kpub_char, portaChave->keyHolder->matrix_kpriv_char,
                       portaChave->keyHolder->matrix_kcod_char,
                       portaChave->keyHolder->lines, 1);
        portaChave = portaChave->pdown;
    }
}
/*
void escrever_ficheiro_txt(UTILIZADORES *utilizadores, char filename[]) {
    FILE *arquivoINFO = NULL;

    if ((arquivoINFO = fopen(filename, "w")) == NULL) {
        fprintf(stdout, "ERRO\n");
        return;
    }

    UTILIZADOR *utilizador = utilizadores->ptop;

    while (utilizador != NULL) {
        fprintf(arquivoINFO, "%-15s %s\n", utilizador->nome, utilizador->email);
        PORTA_CHAVE *portaChave = utilizador->portaChaves->ptop;
        while (portaChave != NULL) {

            fprintf(arquivoINFO, "Porta Chave criado em: %d/%d/%d  %d:%d:%d\n", portaChave->geracao.dia,
                    portaChave->geracao.mes, portaChave->geracao.ano, portaChave->geracao.hora,
                    portaChave->geracao.min, portaChave->geracao.seg);

            fprintf(arquivoINFO, "Porta Chave atualizado em: %d/%d/%d  %d:%d:%d\n", portaChave->atualizacao.dia,
                    portaChave->atualizacao.mes, portaChave->atualizacao.ano, portaChave->atualizacao.hora,
                    portaChave->atualizacao.min, portaChave->atualizacao.seg);

            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpub_int + j) + i) != -1; ++j) {
                    fprintf(arquivoINFO, "%d ", *(*(portaChave->keyHolder->matrix_kpub_int + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }

            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpriv_int + j) + i) != -1; ++j) {
                    fprintf(arquivoINFO, "%d ", *(*(portaChave->keyHolder->matrix_kpriv_int + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }

            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kcod_int + j) + i) != -1; ++j) {
                    fprintf(arquivoINFO, "%d ", *(*(portaChave->keyHolder->matrix_kcod_int + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }

            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpub_char + j) + i) != '\0'; ++j) {
                    fprintf(arquivoINFO, "%c ", *(*(portaChave->keyHolder->matrix_kpub_char + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }

            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpriv_char + j) + i) != '\0'; ++j) {
                    fprintf(arquivoINFO, "%c ", *(*(portaChave->keyHolder->matrix_kpriv_char + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }

            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kcod_char + j) + i) != '\0'; ++j) {
                    fprintf(arquivoINFO, "%c ", *(*(portaChave->keyHolder->matrix_kcod_char + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }

            portaChave = portaChave->pdown;
        }

        utilizador = utilizador->pdown;
    }
}

void load_portachaves_txt(PORTA_CHAVES *portaChaves, char filename[]) {
    FILE *arquivoINFO;

    if ((arquivoINFO = fopen(filename, "r")) == NULL) {
        fprintf(stdout, "ERRO\n");
        return;
    }
    char a[100];
    int i = 1, x1 = 0, y1 = 0, z1 = 0, x2 = 0, y2 = 0, z2 = 0, n1 = 0, n2 = 0, k = 0, q = 0;
    PORTA_CHAVE *portaChave = load_porta_chave();

    KEY_HOLDER *keyHolder_n = (KEY_HOLDER *) malloc(sizeof(KEY_HOLDER));

    while (!feof(arquivoINFO)) {
        if (i == 1) {
            fgets(a, 100, arquivoINFO);
            n1 = atoi(a);
        } else if (i == 2) {
            fgets(a, 100, arquivoINFO);
            n2 = atoi(a);
            keyHolder_n->lines = n2;
            keyHolder_n->columns = 21;
            keyHolder_n->matrix_kpub_int = alloc_matrix_int(keyHolder_n->lines, keyHolder_n->columns);
            keyHolder_n->matrix_kpub_char = alloc_matrix_char(keyHolder_n->lines, keyHolder_n->columns);
            keyHolder_n->matrix_kpriv_int = alloc_matrix_int(keyHolder_n->lines, keyHolder_n->columns);
            keyHolder_n->matrix_kpriv_char = alloc_matrix_char(keyHolder_n->lines, keyHolder_n->columns);
            keyHolder_n->matrix_kcod_int = alloc_matrix_int(keyHolder_n->lines, keyHolder_n->columns);
            keyHolder_n->matrix_kcod_char = alloc_matrix_char(keyHolder_n->lines, keyHolder_n->columns);
        } else {
            for (int j = 0; j < n1; j++) {
                while (q < n2 * 6) {
                    fgets(a, 100, arquivoINFO);
                    if (q >= 0 && q < n2) {
                        unsigned long long key = atoi(a);
                        short *arr = key_long_2_digits_int(key);
                        for (k = 0; *(arr + k) != -1; k++) {
                            *(*(keyHolder_n->matrix_kpub_int + k) + x1) = *(arr + k);
                            //printf("%d ", *(*(keyHolder_n->matrix_kpub_int + k) + x1));
                        }
                        //printf("\n");
                        *(*(keyHolder_n->matrix_kpub_int + k) + x1) = -1;
                        x1++;
                    } else if (q >= n2 && q < n2 * 2) {
                        unsigned long long key = atoi(a);
                        short *arr = key_long_2_digits_int(key);
                        for (k = 0; *(arr + k) != -1; k++) {
                            *(*(keyHolder_n->matrix_kpriv_int + k) + y1) = *(arr + k);
                            //printf("%d ", *(*(keyHolder_n->matrix_kpriv_int + k) + y1));
                        }
                        //printf("\n");
                        *(*(keyHolder_n->matrix_kpriv_int + k) + y1) = -1;
                        y1++;
                    } else if (q >= n2 * 2 && q < n2 * 3) {
                        unsigned long long key = atoi(a);
                        short *arr = key_long_2_digits_int(key);
                        for (k = 0; *(arr + k) != -1; k++) {
                            *(*(keyHolder_n->matrix_kcod_int + k) + z1) = *(arr + k);
                            //printf("%d ", *(*(keyHolder_n->matrix_kcod_int + k) + z1));
                        }
                        //printf("\n");
                        *(*(keyHolder_n->matrix_kcod_int + k) + z1) = -1;
                        z1++;
                    } else if (q >= n2 * 3 && q < n2 * 4) {
                        unsigned long long key = atoi(a);
                        char *arr = key_long_2_digits_char(key);
                        for (k = 0; *(arr + k) != '\0'; k++) {
                            *(*(keyHolder_n->matrix_kpub_char + k) + x2) = *(arr + k);
                            //printf("%c ", *(*(keyHolder_n->matrix_kpub_char + k) + x2));
                        }
                        //printf("\n");
                        *(*(keyHolder_n->matrix_kpub_char + k) + x2) = '\0';
                        x2++;
                    } else if (q >= n2 * 4 && q < n2 * 5) {
                        unsigned long long key = atoi(a);
                        char *arr = key_long_2_digits_char(key);
                        for (k = 0; *(arr + k) != '\0'; k++) {
                            *(*(keyHolder_n->matrix_kpriv_char + k) + y2) = *(arr + k);
                            //printf("%c ", *(*(keyHolder_n->matrix_kpriv_char + k) + y2));
                        }
                        //printf("\n");
                        *(*(keyHolder_n->matrix_kpriv_char + k) + y2) = '\0';
                        y2++;
                    } else if (q >= n2 * 5) {
                        unsigned long long key = atoi(a);
                        char *arr = key_long_2_digits_char(key);
                        for (k = 0; *(arr + k) != '\0'; k++) {
                            *(*(keyHolder_n->matrix_kcod_char + k) + z2) = *(arr + k);
                            //printf("%c ", *(*(keyHolder_n->matrix_kcod_char + k) + z2));
                        }
                        //printf("\n");
                        *(*(keyHolder_n->matrix_kcod_char + k) + z2) = '\0';
                        z2++;
                    }
                    q++;
                }
                portaChave->keyHolder = keyHolder_n;
                inserir_porta_chave(portaChaves, portaChave);
                i +=q;
            }
        }
        i++;
    }


}*/

void escrever_ficheiro_txt(UTILIZADORES *utilizadores, char filename[]) {
    FILE *arquivoINFO = NULL;

    if ((arquivoINFO = fopen(filename, "w")) == NULL) {
        fprintf(stdout, "ERRO\n");
        return;
    }
    int count1 = 0, count2 = 0, count3 = 0;

    UTILIZADOR *utilizador_count = utilizadores->ptop;

    while(utilizador_count != NULL){
        count1++;
        utilizador_count = utilizador_count->pdown;
    }

    UTILIZADOR *utilizador = utilizadores->ptop;
    fprintf(arquivoINFO, "Numero de utilizadores: %d\n", count1);
    while (utilizador != NULL) {
        fprintf(arquivoINFO, "Utilizador: %-10s %s\n", utilizador->nome, utilizador->email);
        PORTA_CHAVE *portaChave_count = utilizador->portaChaves->ptop;
        while (portaChave_count != NULL) {
            count2++;
            portaChave_count = portaChave_count->pdown;
        }
        PORTA_CHAVE *portaChave = utilizador->portaChaves->ptop;
        fprintf(arquivoINFO, "Numero de Porta Chaves do Utilizador: %d\n", count2);
        while (portaChave != NULL) {

            fprintf(arquivoINFO, "Porta Chave criado em: %d/%d/%d  %d:%d:%d\n", portaChave->geracao.dia,
                    portaChave->geracao.mes, portaChave->geracao.ano, portaChave->geracao.hora,
                    portaChave->geracao.min, portaChave->geracao.seg);

            fprintf(arquivoINFO, "Porta Chave atualizado em: %d/%d/%d  %d:%d:%d\n", portaChave->atualizacao.dia,
                    portaChave->atualizacao.mes, portaChave->atualizacao.ano, portaChave->atualizacao.hora,
                    portaChave->atualizacao.min, portaChave->atualizacao.seg);
            fprintf(arquivoINFO, "Numero de Linhas do Porta Chaves: %d\n", portaChave->keyHolder->lines);
            fprintf(arquivoINFO, "INT keys Publicas:\n");
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpub_int + j) + i) != -1; ++j) {
                    fprintf(arquivoINFO, "%d ", *(*(portaChave->keyHolder->matrix_kpub_int + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }
            fprintf(arquivoINFO, "INT keys Privadas:\n");
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpriv_int + j) + i) != -1; ++j) {
                    fprintf(arquivoINFO, "%d ", *(*(portaChave->keyHolder->matrix_kpriv_int + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }
            fprintf(arquivoINFO, "INT keys Codificadas:\n");
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kcod_int + j) + i) != -1; ++j) {
                    fprintf(arquivoINFO, "%d ", *(*(portaChave->keyHolder->matrix_kcod_int + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }
            fprintf(arquivoINFO, "CHAR keys Publicas:\n");
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpub_char + j) + i) != '\0'; ++j) {
                    fprintf(arquivoINFO, "%c ", *(*(portaChave->keyHolder->matrix_kpub_char + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }
            fprintf(arquivoINFO, "CHAR keys Privadas:\n");
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpriv_char + j) + i) != '\0'; ++j) {
                    fprintf(arquivoINFO, "%c ", *(*(portaChave->keyHolder->matrix_kpriv_char + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }
            fprintf(arquivoINFO, "CHAR keys Codificadas:\n");
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kcod_char + j) + i) != '\0'; ++j) {
                    fprintf(arquivoINFO, "%c ", *(*(portaChave->keyHolder->matrix_kcod_char + j) + i));
                }
                fprintf(arquivoINFO, "\n");
            }

            portaChave = portaChave->pdown;
        }

        utilizador = utilizador->pdown;
    }
}

void escrever_ficheiro_bin(UTILIZADORES *utilizadores, char filename[]){

    FILE *fileInfo = NULL;

    if ((fileInfo = fopen(filename, "wb")) == NULL) {
        printf("ERRO %s\n", filename);
        return;
    }

    int count1 = 0, count2 = 0;

    UTILIZADOR *utilizador_count = utilizadores->ptop;

    while(utilizador_count != NULL){
        count1++;
        utilizador_count = utilizador_count->pdown;
    }

    char name1[] = "Numero de utilizadores: ";
    char name2[] = "Utilizador: ";
    char name3[] = "Numero de Porta Chaves: ";
    char name4[] = "Data de geracao: ";
    char name5[] = "Data de atualizacao: ";
    char name6[] = "Numero de linhas: ";
    char name7[] = "INT keys Publicas:";
    char name8[] = "INT keys Privadas:";
    char name9[] = "INT keys Codificadas:";
    char name10[] = "CHAR keys Publicas:";
    char name11[] = "CHAR keys Privadas:";
    char name12[] = "CHAR keys Codificadas:";

    UTILIZADOR *utilizador = utilizadores->ptop;
    int size_name1 = strlen(name1) + 1;
    fwrite(&name1, sizeof(char),size_name1,fileInfo);
    fwrite(&count1, sizeof(int),1,fileInfo);
    fwrite("\n", sizeof(char),1,fileInfo);
    while (utilizador != NULL){
        int size_name2 = strlen(name2) + 1;
        fwrite(&name2,sizeof(char),size_name2,fileInfo);
        int size_name = strlen(utilizador->nome) + 1;
        fwrite(&utilizador->nome, sizeof(char), size_name, fileInfo);
        fwrite("/", sizeof(char),1,fileInfo);
        int size_email = strlen(utilizador->email) + 1;
        fwrite(&utilizador->email, sizeof(char), size_email, fileInfo);
        fwrite("\n", sizeof(char),1,fileInfo);

        PORTA_CHAVE *portaChave_count = utilizador->portaChaves->ptop;
        while (portaChave_count != NULL) {
            count2++;
            portaChave_count = portaChave_count->pdown;
        }
        PORTA_CHAVE *portaChave = utilizador->portaChaves->ptop;
        int size_name3 = strlen(name3) + 1;
        fwrite(&name3,sizeof(char),size_name3,fileInfo);
        fwrite(&count2, sizeof(int),1,fileInfo);
        fwrite("\n", sizeof(char),1,fileInfo);
        while(portaChave != NULL){
            int size_name4 = strlen(name4) + 1;
            fwrite(&name4, sizeof(char),size_name4,fileInfo);
            fwrite(&portaChave->geracao.dia, sizeof(int),1,fileInfo);
            fwrite("/", sizeof(char),1,fileInfo);
            fwrite(&portaChave->geracao.mes, sizeof(int),1,fileInfo);
            fwrite("/", sizeof(char),1,fileInfo);
            fwrite(&portaChave->geracao.ano, sizeof(int),1,fileInfo);
            fwrite(" ", sizeof(char),1,fileInfo);
            fwrite(&portaChave->geracao.hora, sizeof(int),1,fileInfo);
            fwrite("/", sizeof(char),1,fileInfo);
            fwrite(&portaChave->geracao.min, sizeof(int),1,fileInfo);
            fwrite("/", sizeof(char),1,fileInfo);
            fwrite(&portaChave->geracao.seg, sizeof(int),1,fileInfo);
            fwrite("\n", sizeof(char),1,fileInfo);

            int size_name5 = strlen(name5) + 1;
            fwrite(&name5, sizeof(char),size_name5,fileInfo);
            fwrite(&portaChave->atualizacao.dia, sizeof(int),1,fileInfo);
            fwrite("/", sizeof(char),1,fileInfo);
            fwrite(&portaChave->atualizacao.mes, sizeof(int),1,fileInfo);
            fwrite("/", sizeof(char),1,fileInfo);
            fwrite(&portaChave->atualizacao.ano, sizeof(int),1,fileInfo);
            fwrite(" ", sizeof(char),1,fileInfo);
            fwrite(&portaChave->atualizacao.hora, sizeof(int),1,fileInfo);
            fwrite("/", sizeof(char),1,fileInfo);
            fwrite(&portaChave->atualizacao.min, sizeof(int),1,fileInfo);
            fwrite("/", sizeof(char),1,fileInfo);
            fwrite(&portaChave->atualizacao.seg, sizeof(int),1,fileInfo);
            fwrite("\n", sizeof(char),1,fileInfo);

            int size_name6 = strlen(name6) + 1;
            fwrite(&name6, sizeof(char),size_name6,fileInfo);
            fwrite(&portaChave->keyHolder->lines, sizeof(int),1,fileInfo);
            fwrite("\n", sizeof(char),1,fileInfo);

            int size_name7 = strlen(name7) + 1;
            fwrite(&name7, sizeof(char),size_name7,fileInfo);
            fwrite("\n", sizeof(char),1,fileInfo);
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpub_int + j) + i) != -1; ++j) {
                    short matrix_aux = *(*(portaChave->keyHolder->matrix_kpub_int + j) + i);
                    fwrite(&matrix_aux, sizeof(short),1,fileInfo);
                    fwrite(" ", sizeof(char),1,fileInfo);
                }
                fwrite("\n", sizeof(char),1,fileInfo);
            }
            int size_name8 = strlen(name8) + 1;
            fwrite(&name8, sizeof(char),size_name8,fileInfo);
            fwrite("\n", sizeof(char),1,fileInfo);
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpriv_int + j) + i) != -1; ++j) {
                    short matrix_aux = *(*(portaChave->keyHolder->matrix_kpriv_int + j) + i);
                    fwrite(&matrix_aux, sizeof(short),1,fileInfo);
                    fwrite(" ", sizeof(char),1,fileInfo);
                }
                fwrite("\n", sizeof(char),1,fileInfo);
            }
            int size_name9 = strlen(name9) + 1;
            fwrite(&name9, sizeof(char),size_name9,fileInfo);
            fwrite("\n", sizeof(char),1,fileInfo);
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kcod_int + j) + i) != -1; ++j) {
                    short matrix_aux = *(*(portaChave->keyHolder->matrix_kcod_int + j) + i);
                    fwrite(&matrix_aux, sizeof(short),1,fileInfo);
                    fwrite(" ", sizeof(char),1,fileInfo);
                }
                fwrite("\n", sizeof(char),1,fileInfo);
            }
            int size_name10 = strlen(name10) + 1;
            fwrite(&name10, sizeof(char),size_name10,fileInfo);
            fwrite("\n", sizeof(char),1,fileInfo);
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpub_char + j) + i) != '\0'; ++j) {
                    char matrix_aux = *(*(portaChave->keyHolder->matrix_kpub_char + j) + i);
                    fwrite(&matrix_aux, sizeof(char),1,fileInfo);
                    fwrite(" ", sizeof(char),1,fileInfo);
                }
                fwrite("\n", sizeof(char),1,fileInfo);
            }
            int size_name11 = strlen(name11) + 1;
            fwrite(&name11, sizeof(char),size_name11,fileInfo);
            fwrite("\n", sizeof(char),1,fileInfo);
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kpriv_char + j) + i) != '\0'; ++j) {
                    char matrix_aux = *(*(portaChave->keyHolder->matrix_kpriv_char + j) + i);
                    fwrite(&matrix_aux, sizeof(char),1,fileInfo);
                    fwrite(" ", sizeof(char),1,fileInfo);
                }
                fwrite("\n", sizeof(char),1,fileInfo);
            }
            int size_name12 = strlen(name12) + 1;
            fwrite(&name12, sizeof(char),size_name12,fileInfo);
            fwrite("\n", sizeof(char),1,fileInfo);
            for (int i = 0; i < portaChave->keyHolder->lines; i++) {
                for (int j = 0; *(*(portaChave->keyHolder->matrix_kcod_char + j) + i) != '\0'; ++j) {
                    char matrix_aux = *(*(portaChave->keyHolder->matrix_kcod_char + j) + i);
                    fwrite(&matrix_aux, sizeof(char),1,fileInfo);
                    fwrite(" ", sizeof(char),1,fileInfo);
                }
                fwrite("\n", sizeof(char),1,fileInfo);
            }
            portaChave = portaChave->pdown;
        }
        utilizador = utilizador->pdown;
    }
}
