/*
 * Project created and developed by: João Vicente nº 33969
 * Curricular Unit: Algoritmos e Estruturas de Dados I & Linguagens de Programação I
 * Date: October 2018 to January 2019
 */

#ifndef PROJECT2018_FASE2_H
#define PROJECT2018_FASE2_H

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "fase1.h"
#include "mergesort.h"

/*--------------------------------------------- DECLARAÇÃO DE ESTRUTURAS ---------------------------------------------*/
typedef struct letra{
    char letra;
    struct letra * N, *NE, *E, *SE, *S, *SO, *NO, *O;
    int line, col;
    struct caminho * p_sol_first;
}LETRA;

typedef struct tabuleiro{
    LETRA *pfirst;
    int lines, cols;
}TABULEIRO;

typedef struct palavra{
    char * word;
    int size;
    struct palavra *pnext;
}PALAVRA;

typedef struct dicionario{
    int nwords;
    PALAVRA * pfirst;
}DICIONARIO;

typedef  struct caminho{
    char * palavra;
    int x_inicial;
    int y_inicial;
    int direcoes;
    int x_final;
    int y_final;
    int check;
    struct caminho * pnext;
}CAMINHO;

typedef struct solucoes{
    int nsolucoes;
    CAMINHO * pfirst;
    CAMINHO * plast;
}SOLUCOES;

/*--------------------------------------------------- TABULEIRO ------------------------------------------------------*/

int main_fase2();
char ** save_txt_into_matrix(char * path, int lines, int cols);
void insert_letras_into_tabuleiro(TABULEIRO * tab, char ** matrix);
void print_matriz(TABULEIRO tab);

/*--------------------------------------------------- DICIONARIO -----------------------------------------------------*/

int menu_dicionario(DICIONARIO * dic,TABULEIRO tab, SOLUCOES sol, char * path_dicionario);
void menu_guardar_dicionario(DICIONARIO dic);
void init_dicionario_from_file(DICIONARIO * dic, char * path, int size);
char *create_copy_dyn_string_f2(char *str);
void init_dicionario_manual(DICIONARIO * dic);
void print_dicionario(DICIONARIO dic);
void modifica_dicionario_ordenado(TABULEIRO tab, DICIONARIO * dic, struct Node ** n); // utiliza dicionario ordenado pelo merge p/ pesquisa

/*-------------------------------------------------- PESQUISA --------------------------------------------------------*/

void find_path_f2(TABULEIRO tab, LETRA * l, PALAVRA * p, CAMINHO * c, SOLUCOES * sol, int line, int column, int *pos_i, int * solutionCount);
int check_consistency_f2(TABULEIRO tab, LETRA * l, PALAVRA p, char c, int line, int column);
int run_program_f2(TABULEIRO tab, DICIONARIO dic, SOLUCOES * sol, int size);
void print_lista_solucoes(SOLUCOES * s); //apresentacao de todos os resultados da pesquisa
int inverter_numero(int number); // inverte numero (inteiro de direcoes)

/*-------------------------------------------- LEITURA LINHAS/ COLUNAS TXT -------------------------------------------*/

int read_lines_from_txt_f2(char * path);
int read_cols_from_txt_f2(char * path);

/*-------------------------------------------- ALGORITMO MERGE SORT (R.6) --------------------------------------------*/

void menu_merge(TABULEIRO tab, DICIONARIO * dic);
struct Node ** ordena_dic(DICIONARIO dic);

/*------------------------------------------ MANIPULACAO STRUCTS TXT (R.12) ------------------------------------------*/

void ler_struct_dicionario_txt(DICIONARIO * dic);
void guardar_struct_dicionario_txt(DICIONARIO dic);
void guardar_struct_tabuleiro_txt(TABULEIRO tab);
void ler_struct_tabuleiro_txt(TABULEIRO * tab);
void guardar_struct_sol_txt(SOLUCOES sol);
void ler_struct_sol_txt(SOLUCOES * sol);
void insert_struct_sol_into_struct_letra(TABULEIRO * tab, SOLUCOES sol);

/*------------------------------------------------ REQUISITO 10 ------------------------------------------------------*/

char * recebe_posicao_direcoes(TABULEIRO tab, int * size);
void print_array_letras(char * array, int * size);

/*------------------------------------------------ REQUISITO 11 ------------------------------------------------------*/

void decode_dir(int aux);

/*------------------------------------------ MANIPULACAO STRUCTS BIN (R.13) ------------------------------------------*/

void guardar_struct_dic_bin(DICIONARIO dic);
void ler_struct_dic_bin(DICIONARIO * dic);
void insert_words_tail(DICIONARIO * dic, char * word, int size);

/*------------------------------------------ FUNCOES INICIA ESTRUTURA NULO -------------------------------------------*/

void iniciar_null(LETRA * letra);
void iniciar_palavra_null(PALAVRA * p);
void iniciar_caminho_null(CAMINHO * c);

#endif //PROJECT2018_FASE2_H