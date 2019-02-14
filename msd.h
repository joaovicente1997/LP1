//
// Created by swepp on 24/11/2018.
//

#ifndef PROJECT2018_MSD_H
#define PROJECT2018_MSD_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

// tamanho do alfabeto de chars com 8 bits (ASCII)
#define CHAR_8BIT_RADIX 256

// terminate symbol for strings
#define STRING_END_CHAR -1


//------------------Estrutura LSD radix sort, MSD and other------------------
typedef struct {
    char ** str; // array of strings
    int * len; // array of string lengths
    int N; // number of strings (size of array of strings)
} StringElementsArray;

void mainClientMSD_WITHOUT_CUTOFF(char **strings, int N, char * path);
int charAt(StringElementsArray * a, int i, int d);
void msd_sort_whithout_cutoff(StringElementsArray *a, StringElementsArray *aux, int lo, int hi, int d, int R);
void createStringElementsArrayAndFill(StringElementsArray * si, int N, char ** strings);
void createStringElementsArray(StringElementsArray * si, int N);
int * newIntArray(int N);


#endif //PROJECT2018_MSD_H
