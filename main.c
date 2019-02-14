/*
 * Project created and developed by: João Vicente, student number 33969
 * University: Fernando Pessoa University, Porto, Portugal
 * Course: Computer Engineering
 * Curricular Unit: Algoritmos e Estruturas de Dados I & Linguagens de Programação I
 * Date: October 2018 to January 2019
 */

#include "fase1.h"
#include "fase2.h"
#include <stdlib.h>
#include <stdio.h>

void menu();

int main(int argc, const char * argv[]){
    menu();
    return 0;
}

/**
 * @brief menu de escolha de fase do projeto
 * TODO:
 * - Fase 2:
 *      - Generate random matrix in order to find a certain bag of words (dictionary) on the 'Tabuleiro' struct
 *      - Manipulation of struct "tabuleiro" in binary file
 *      - Manipulation of struct "soluções" in binary file
 */
void menu(){
    printf("\nProject created and developed by: Joao Vicente n. 33969\nCurricular Unit: Algoritmos e Estruturas de Dados I & Linguagens de Programacao I\nDate: October 2018 to January 2019\n\n");
    int option =0;
    printf("#############################################################################\n");
    printf("#                        S O P A  D E  L E T R A S                          #\n");
    printf("#############################################################################\n");
    printf("O que pretende realizar?\n\n");
    printf("(1) Primeira Fase \n");
    printf("(2) Segunda Fase \n");
    printf("(3) Sair\n\n");
    scanf("%d", &option);

    switch(option){
        case 1:
            main_sopa_letras();
            break;
        case 2:
            main_fase2();
            break;
        case 3:
            return ;
        default:
            printf("ERRO: Opcao invalida, tente novamente!\n\n");
            menu();
    }
}