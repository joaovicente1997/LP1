/*
 * Project created and developed by: João Vicente, student number 33969
 * University: Fernando Pessoa University, Porto, Portugal
 * Course: Computer Engineering
 * Curricular Unit: Algoritmos e Estruturas de Dados I & Linguagens de Programação I
 * Date: October 2018 to January 2019
 */


#ifndef PROJECT2018_MATRIX_FUNCTIONS_H
#define PROJECT2018_MATRIX_FUNCTIONS_H
#define ALPHABET 26

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* ---------------------------------------------- MENU INICIAL DE JOGO ---------------------------------------------- */
int main_sopa_letras();

/* ---------------------------------------------- INICIALIZAÇÃO DE PROGRAMA ---------------------------------------------- */
int run_program(char** matrix, char **aux, char**matriz_strings, int *size, int * nlines, int * ncols);

/* ---------------------------------------------- ALGORITMOS DE PROCURA ---------------------------------------------- */
void find_path(char **lab, char *c, int line, int column, char **aux, int *pos_i, int *path, int *number,
                  int *nlines, int *ncols, int *solutionCount);
int check_consistency(char **lab, char c, int line, int column, int *nlines, int *ncols);

/* ---------------------------------------------- FUNÇÕES DE LEITURA DE STDIN E ESCRITA P/ MATRIZ ---------------------------------------------- */
char **read_dynarray_strings(char **str, int size);
char *create_copy_dyn_string(char *str);
char *part_dynarray_strings_into_array(char **matrix_strings, int auxSize);

/*---------------------------------------------- ESCOLHA DE TABULEIROS ---------------------------------------------- */
char **text_file_matrix(char * path, int lines, int cols);
void init_dyn_matrix();

/*---------------------------------------------- ESCOLHA DE DICIONARIOS ---------------------------------------------- */
void init_dictionary(char **matrix, char **aux, int * nlines, int * ncols);
void init_dictionary_manually(char **matrix, char **aux, int * nlines, int *ncols);
char **init_dictionary_txt(char **str, int size, char * path);

/*---------------------------------------------- GUARDAR/LER TXT ---------------------------------------------- */
void save_dictionary_to_txt(char ** matrizDicionario, int * size);
int read_lines_from_txt(char * path);
int read_cols_from_txt(char * path);

/*---------------------------------------------- ALOCAÇÃO DE MATRIZES: ALEATÓRIA E AUXILIAR ---------------------------------------------- */
char** allocate_matrix(int l,int c);
char** allocate_matrix_aux(int l,int c);

/* ---------------------------------------------- ESCREVER NA MATRIZ O CARACTER WRITE ---------------------------------------------- */
char **write_to_matrix(char **matriz, int nlines, int ncols, char write);

/* ---------------------------------------------- FUNÇÕES DE PRINT ---------------------------------------------- */
void print_matrix(char **matrix, int * nlines, int * ncols);
void print_dynarray_chars(char **pints, int n);

/* ---------------------------------------------- DESCODIFICAR A SEQ. MOVIMENTOS ---------------------------------------------- */
void decode_path(int *path, int *number);




#endif //PROJECT2018_MATRIX_FUNCTIONS_H
