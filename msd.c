//
// Created by swepp on 24/11/2018.
//

#include "msd.h"


//------------------MSD radix sort------------------
/**- Algoritmo de ordenação rápido e estável. Este começa por ordenar do digito mais significativo
 * de forma alfabetica. Repetindo a ordenaçao para os seguintes digitos, mas fazendo comparaçoes
 * entre cada letra da palavra
 * - Desvantagens:
 *      - Precisa de espaço extra para o vetor aux[] e para o count[]
 *      - Acesso a memoria e aleatorio
 *      - Loop interno possui muitas instruções
 * - Vantagens:
 *      - MSD examina apenas caracteres suficientes para ordenar os chars
 *      - Numero de caracteres examinados depende de chars**/

void mainClientMSD_WITHOUT_CUTOFF(char **strings, int N, char * path){
    //char *strings[]={"PORTO","AVEIRO","FARO","COIMBRA"};
    //int N = 4;
    FILE * fp;
    fp = fopen(path, "w");

    StringElementsArray a;
    StringElementsArray aux;
    createStringElementsArrayAndFill(&a,N,strings);
    createStringElementsArray(&aux,N);
    printf("Original List:\n");
    for (int i = 0; i < N; ++i) {
        printf("%s",a.str[i]);
    }
    msd_sort_whithout_cutoff(&a,&aux,0,N-1,0,CHAR_8BIT_RADIX);

    printf("\nFinal List:\n");
    for (int i = 0; i < N; ++i) {
        printf("%s",a.str[i]);
        fprintf(fp,"%s", a.str[i]);
    }

}

void msd_sort_whithout_cutoff(StringElementsArray *a, StringElementsArray *aux, int lo, int hi, int d, int R) {
    int i,r,c;
    int * count = newIntArray(R + 2);
    // reset count[] array
    for (i = 0; i < R+2; i++)
        count[i]=0;

    if (hi <= lo) return;

    // compute frequency counts
    for (i = lo; i <= hi; i++) {
        c = charAt(a, i, d);
        count[c + 2]++;
    }

    // transform counts to indicies
    for (r = 0; r < R + 1; r++)
        count[r+1] += count[r];

    // distribute
    for (i = lo; i <= hi; i++) {
        c = charAt(a, i, d);
        aux->str[count[c + 1]] = a->str[i];
        aux->len[count[c + 1]] = a->len[i];
        count[c + 1]++;
    }

    // copy back
    for (i = lo; i <= hi; i++) {
        a->str[i] = aux->str[i-lo];
        a->len[i] = aux->len[i-lo];
    }

    // Trace of recursive calls for MSD string sort (version with no cutoff for small subarrays used!)
    /*printf("\n-------------\nMSD Sorted List (left to right) after iteration (lo,hi,d)= %d,%d,%d:\n",lo,hi,d);
    for (i = lo; i <= hi; i++)
        printf("\t%s\n",a->str[i]);*/

    // recursively sort for each character
    for (r = 0; r < R; r++)
        msd_sort_whithout_cutoff(a, aux, lo + count[r], lo + count[r+1] - 1, d+1, R);
}

int charAt(StringElementsArray * a, int i, int d) {
    return (d < a->len[i]) ? (a->str[i][d]) : STRING_END_CHAR;
}

//
void createStringElementsArrayAndFill(StringElementsArray * si, int N, char ** strings){
    int i;
    createStringElementsArray(si, N);
    for (i = 0; i < N; i++) {
        si->str[i] = strings[i];
        si->len[i] = (int)strlen(strings[i]);
    }
    return;
}
//
void createStringElementsArray(StringElementsArray * si, int N) {
    si->N = N;
    si->str = (char **) malloc(sizeof(char *)*N);
    si->len = (int *) malloc(sizeof(int)*N);
    return;
}

//------------------Criar Vetor------------------
/**Funçao para criar um array**/
int * newIntArray(int N){
    return (int *) malloc(sizeof(int)*N);
}