/*
 * Project created and developed by: João Vicente, student number 33969
 * University: Fernando Pessoa University, Porto, Portugal
 * Course: Computer Engineering
 * Curricular Unit: Algoritmos e Estruturas de Dados I & Linguagens de Programação I
 * Date: October 2018 to January 2019
 */


#include "fase1.h"
#include "msd.h"


/* ---------------------------------------------- MENU INICIAL DE JOGO ---------------------------------------------- */


/**
 * @brief MENU DE ESCOLHA DE TIPO DE SOPA DE LETRAS A UTILIZAR
 * @return
 */
int main_sopa_letras() {
    int choice = 0;
    int l, col;
    char path[] = "C:/Users/swepp/CLionProjects/project2018/data/dicionario_ordenado.txt";
    char path_1[] = "C:/Users/swepp/CLionProjects/project2018/data/matrix.txt";
    int size = read_lines_from_txt(path);
    char *palavras[size];
    char **dicionarioOrdenado = init_dictionary_txt(palavras,size,path);
    char **matrix;
    char **aux;
    system("cls");
    printf("#####################################################################\n");
    printf("#                       M E N U  D E  J O G O                       #\n");
    printf("#####################################################################\n\n");

    printf("O que pretende realizar:");
    printf("\n\t(1) - Gerar Sopa de Letras Aleatoria!\n");
    printf("\t(2) - Consultar Sopa de Letras de Ficheiro de Texto!\n");
    printf("\t(3) - Ordenar Dicionario de Palavras!\n");
    printf("\t(0) - Sair!\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            init_dyn_matrix();
            break;
        case 2:
            l = read_lines_from_txt(path_1);
            col = read_cols_from_txt(path_1);
            aux = allocate_matrix_aux(l, col);
            matrix = text_file_matrix(path_1, l, col);
            print_matrix(matrix, &l, &col);
            init_dictionary(matrix, aux, &l, &col);
            break;
        case 3:
            mainClientMSD_WITHOUT_CUTOFF(dicionarioOrdenado, size, path);
            break;
        case 0:
            exit(0);
        default:
            printf("ERRO: Opcao invalida, tente novamente!\n\n");
            main_sopa_letras();
    }

    return 0;
}


/* ---------------------------------------------- INICIALIZAÇÃO DE PROGRAMA ---------------------------------------------- */


/**
 * @brief FUNÇÃO QUE INICIALIZA A PROCURA DE ACORDO COM A MATRIZ/ DICIONÁRIO ESCOLHIDOS NOS MENUS ANTERIORES
 * @param matrix
 * @param aux
 * @param matriz_strings
 * @param size
 * @param nlines
 * @param ncols
 * @return
 */
int run_program(char **matrix, char **aux, char **matriz_strings, int *size, int *nlines, int * ncols) {
    int solutionCount = 0;// INICIALIZA CONTADOR DE SOLUÇÃO
    int pos_i = 1;
    for (int i = 0; i < *size; i++) {
        char *paux = part_dynarray_strings_into_array(matriz_strings, i); // Guarda o conteúdo da matriz de strings no Endereço i em *paux
        printf("Vai procurar a palavra: %s\n", paux);    // Print a informar que vai procurar a palavra "paux"

        int number = strlen(paux) +2;   // para o tamanho da string path
        // (ex. se *paux = PORTO\n, strlen(paux) = 6, ou seja, number vai ser 8, para guardar x inicial, y inicial, direçao O, direção R, direção T, direção O, x final, y final)
        int path[number];   // declara a string de inteiros path com tamanho = Numer

        for(int x=0; x< number; x++){
            path[x] = 9; // inicializa o array a 9, pois assim, ñ é considerado no "decoder" de direções
        }

        int l, j, k;
        for (l = 0; l < *nlines; l++) {   // itera pelo nº de linhas
            for (int col = 0; col < *ncols; col++) { // itera pelo número de colunas
                if (check_consistency(matrix, *(paux + 0), l, col, nlines,ncols) == 1) { // caso o check, na matriz "fase1" na posição [l][col] com o caracter "*(paux+0)" (que irá ser o primeiro caracter da string em questão), seja 1 entra na condição
                    aux[l][col] = *(paux + 0);   //copia o primeiro caracter para a matriz auxiliar na posição: [l][col]
                    path[0] = l;    // envia na primeira posição o x inicial
                    path[1] = col;  // envia na segunda posição o y inicial
                    find_path(matrix, paux, l, col, aux, &pos_i, path, &number, nlines, ncols, &solutionCount);   //verifica se na matriz "fase1" existe continuação da palavra com o caracter copiado para a matriz auxiliar
                    pos_i = 1;
                    aux[l][col] = '-';
                }
            }
            for (j = 0; j < *nlines; j++) {   // LIMPA MATRIZ AUXILIAR (VOLTA A INSERI-LA COMPLETAMENTE COM "-")
                for (k = 0; k < *ncols; k++) {
                    aux[j][k] = '-';
                }
            }
            for(j=0; j<number; j++){ // inicializa o array a 9, para ser utilizado novamente
                path[j]=9;
            }
        }
        if (solutionCount > 1) { // CASO A VARIÁVEL "global_count" SEJA > 1 VAI HAVER MUITAS SOLUÇÕES
            printf("Existem %d solucoes\n\n", solutionCount); //IMPRIME Nº SOLUÇÕES
        } else if (solutionCount == 1) {
            printf("Existe %d solucao\n\n", solutionCount); // PARA O CASO DE APENAS 1 SOLUÇÃO
        } else {
            printf("ERRO: Nao existem solucoes\n\n"); // CASO NENHUMA SOLUÇÃO
        }
        solutionCount = 0; // LIMPA O COUNT GLOBAL

    }
    int yesOrNo; // Caso queira ou não realizar mais alguma ação na sopa de letras
    printf("\nDeseja realizar mais alguma acao?\n(1)-Sim\n(2)-Nao\n");
    scanf("%d", &yesOrNo);
    if(yesOrNo == 1) {
        main_sopa_letras();
    }
    else {
        return 0;
    }
}


/* ---------------------------------------------- ALGORITMOS DE PROCURA ---------------------------------------------- */


/**
 * @brief FUNÇÃO DE VERIFICAÇÃO /DIVISÃO "TAREFAS" POR EXISTÊNCIA DO CARACTER NAS COORDENADAS (N, S, E, O, NE, NO, SE, SO)
 * @param lab
 * @param c
 * @param line
 * @param column
 * @param aux
 */
void find_path(char **lab, char *c, int line, int column, char **aux, int *pos_i, int *path, int *number,
                  int *nlines, int *ncols, int *solutionCount) {
    char charAux;   // inicializa charAux
    charAux = *(c + (*pos_i));
    int aux_i = (*pos_i)+1;

    if (charAux == '\n') { // caso o caracter seja um \n, então a palavra terminou e podemos imprimir a matriz
        print_matrix(aux, nlines, ncols);  //imprime a matriz auxiliar
        path[aux_i] = line;
        path[aux_i+1] = column;
        decode_path(path, number);
        (*solutionCount)++; // incrementa o valor do count para apresentar o número de correspondências para a palavra em causa
        return; //retorna para a função anterior
    }

    if (check_consistency(lab, charAux, line - 1, column, nlines, ncols) == 1) {
        //Norte
        (*pos_i)++;
        aux[line - 1][column] = charAux;
        path[aux_i] = 0;    // 0 = N no decoder
        find_path(lab, c, line - 1, column, aux, pos_i, path, number, nlines, ncols, solutionCount);
        aux[line - 1][column] = '-';
        path[aux_i] = 9;
        (*pos_i)--;
    }

    if (check_consistency(lab, charAux, line - 1, column + 1, nlines, ncols) == 1) {
        //Nordeste
        (*pos_i)++;
        aux[line - 1][column + 1] = charAux;
        path[aux_i ] = 1;   // 1 = NE no decoder
        find_path(lab, c, line - 1, column + 1, aux, pos_i, path, number, nlines, ncols, solutionCount);
        aux[line - 1][column + 1] = '-';
        path[aux_i] = 9;
        (*pos_i)--;
    }

    if (check_consistency(lab, charAux, line, column + 1, nlines, ncols) == 1) {
        //Este
        (*pos_i)++;
        aux[line][column + 1] = charAux;
        path[aux_i ] = 2;   // 2 = E no decoder
        find_path(lab, c, line, column + 1, aux, pos_i, path, number, nlines, ncols, solutionCount);
        aux[line][column + 1] = '-';
        path[aux_i ] = 9;
        (*pos_i)--;
    }

    if (check_consistency(lab, charAux, line + 1, column + 1, nlines, ncols) == 1) {
        //Sudeste
        (*pos_i)++;
        aux[line + 1][column + 1] = charAux;
        path[aux_i ] = 3;   // 3 = SE no decoder
        find_path(lab, c, line + 1, column + 1, aux, pos_i, path, number, nlines, ncols, solutionCount);
        aux[line + 1][column + 1] = '-';
        path[aux_i ] = 9;
        (*pos_i)--;
    }

    if (check_consistency(lab, charAux, line + 1, column, nlines, ncols) == 1) {
        //Sul
        (*pos_i)++;
        aux[line + 1][column] = charAux;
        path[aux_i ] = 4;   // 4 = S no decoder
        find_path(lab, c, line + 1, column, aux, pos_i, path, number, nlines, ncols, solutionCount);
        aux[line + 1][column] = '-';
        path[aux_i ] = 9;
        (*pos_i)--;
    }

    if (check_consistency(lab, charAux, line + 1, column - 1, nlines, ncols) == 1) {
        //Sudoeste
        (*pos_i)++;
        aux[line + 1][column - 1] = charAux;
        path[aux_i ] = 5;   // 5 = SO no decoder
        find_path(lab, c, line + 1, column - 1, aux, pos_i, path, number, nlines, ncols, solutionCount);
        aux[line+1][column - 1] = '-';
        path[aux_i ] = 9;
        (*pos_i)--;
    }

    if (check_consistency(lab, charAux, line, column - 1, nlines, ncols) == 1) {
        //Oeste
        (*pos_i)++;
        aux[line][column - 1] = charAux;
        path[aux_i ] = 6;   // 6 = O no decoder
        find_path(lab, c, line, column - 1, aux, pos_i, path, number, nlines, ncols, solutionCount);
        aux[line][column - 1] = '-';
        path[aux_i ] = 9;
        (*pos_i)--;
    }

    if (check_consistency(lab, charAux, line - 1, column - 1, nlines, ncols) == 1) {
        //Noroeste
        (*pos_i)++;
        aux[line - 1][column - 1] = charAux;
        path[aux_i ] = 7;   // 7 = NO no decoder
        find_path(lab, c, line - 1, column - 1, aux, pos_i, path, number, nlines, ncols, solutionCount);
        aux[line - 1][column - 1] = '-';
        path[aux_i ] = 9;
        (*pos_i)--;
    }

}

/**
 * @brief FUNÇÃO QUE VERIFICA SE O CHAR C NAS COORDENADAS (N, S, E, O, NE, NO, SE, SO) SE ENCONTRA DENTRO DA MATRIZ, CASO ESTEJA VERIFICA SE ESTE NA POSICAO [line][column] SE ENCONTRA NA MATRIZ lab E SE AINDA NÃO EXISTE NA MATRIZ aux
 * @param lab
 * @param c
 * @param line
 * @param column
 * @param aux
 * @return
 */
int check_consistency(char **lab, char c, int line, int column, int *nlines, int * ncols) {
    if (line >= 0 && line < *nlines && column >= 0 && column < *ncols) {    // Verifica se a linha e a coluna enviadas estão dentro da matriz
        if (lab[line][column] == c) { // Verifica se o caracter recebido se encontra na matriz "lab"
            return 1;
        }
    }
    return 0;
}



/* ---------------------------------------------- FUNÇÕES DE LEITURA DE STDIN E ESCRITA P/ MATRIZ ---------------------------------------------- */



/**
 * @brief LÊ O STDIN E GUARDA-O EM STRAUX, POSTERIORMENTE CHAMA A FUNÇÃO create_copy_dyn_string QUE VAI ALOCAR A MEMÓRIA PARA A STRING DINÂMICA
 * @param str
 * @param size
 * @return
 */
char **read_dynarray_strings(char **str, int size) {
    char strAux[100];   //inicializa uma string com tamanho 100 (tamanho máx do que poderá ser lido no stdin)
    for (int i = 0; i < size; i++) {
        fflush(stdin);  //utilizado para limpar o buffer de input
        fgets(strAux, sizeof(strAux), stdin);   // "pede" ao utilizador para inserir 1 palavra, copia-a do stdin, com o tamanho max igual ao size de strAux e guarda-a em strAux
        *(str + i) = create_copy_dyn_string(strAux); //envia strAux para create_copy_dyn_string e o valor retornado é guardado no conteúdo de str na "posição" i
    }

    return str;
}


/**
 * @brief ALOCA MEMÓRIA DINâMICA E CRIA UM ARRAY DINAMICO COM A STRING RECEBIDA DE read_dynarray_strings (COM TAMANHO +1 PARA ADICIONAR \n)
 * @param str
 * @return
 */
char *create_copy_dyn_string(char *str) {
    char *pc = malloc(strlen(str) + 1 * sizeof(char));  //aloca memória com o tamanho da string str recebida +1 e guarda em *pc
    strcpy(pc, str);    //copia str para pc

    return pc; //retorna pc
}


/**
 * @brief FUNÇÃO QUE REPARTE O ARRAY DE STRINGS **matrix_strings NA STRING COM O ENDEREÇO = A auxSize E RETORNA UM ENDEREÇO QUE CONTEM 1 STRING
 * @param matrix_strings
 * @param auxSize
 * @return
 */
char *part_dynarray_strings_into_array(char **matrix_strings, int auxSize) {
    char *aux = NULL;   //inicializa o conteúdo da string "aux" a NULL
    aux = *(matrix_strings + auxSize);  //Guarda em aux o conteúdo da matriz "matrix_strings" no endereço "auxSize" que irá ser 1 endereço
    return aux; //retorna endereço "aux"
}


/*---------------------------------------------- ESCOLHA DE TABULEIROS ---------------------------------------------- */


/**
 * @brief FUNÇÃO DE INICIALIZAÇÃO DA SOPA DE LETRAS GUARDADA NO FICHEIRO TXT
 * @return
 */
char **text_file_matrix(char * path, int lines, int cols) {

    printf("#################################################################################\n");
    printf("#                       M A T R I Z  D E  F I C H E I R O                       #\n");
    printf("#################################################################################\n\n");

    FILE * fp = fopen(path, "r");
    char c;
    char **array = (char**) malloc(sizeof(char*)* lines);
    for(int i=0; i<lines; i++){
        *(array+i) = (char *) malloc(sizeof(char)*cols);
    }
    int j=0;
    int k=0;
    if(fp == NULL){
        return 0;
    }
    for (c = (char) getc(fp); c != EOF; c = (char) getc(fp)) {
        if (c != '\n') {
            array[j][k] = c;
            k++;
        }
        else{
            k=0;
            j++;
        }
    }
    fclose(fp);
    return array;
}

/**
 * @brief FUNÇÃO DE INICIALIZAÇÃO DA SOPA DE LETRAS DINAMICA, COM ESCOLHA DE Nº LINHAS E COLUNAS
 */
void init_dyn_matrix() {
    printf("#################################################################################\n");
    printf("#                        M A T R I Z  A L E A T O R I A                         #\n");
    printf("#################################################################################\n\n");
    int l, col = 0;
    printf("Introduza o numero de linhas:\n");
    scanf("%d", &l);
    printf("Introduza o numero de colunas:\n");
    scanf("%d", &col);
    char **matrix = allocate_matrix(l, col);        // ALOCA MATRIZ DINAMICA
    char **aux = allocate_matrix_aux(l, col);       // ALOCA MATRIZ INICIAL

    print_matrix(matrix, &l, &col);     //  "PRINTA" MATRIZ DINAMICA
    init_dictionary(matrix, aux, &l, &col);     // INICIA MENU DE ESCOLHA DE DICIONARIO
}


/*---------------------------------------------- ESCOLHA DE DICIONARIOS ---------------------------------------------- */


/**
 * @brief FUNÇÃO DE MENU DE ESCOLHA DE DICIONARIO
 * @param matriz
 * @param aux
 * @param nlines
 * @param ncols
 */
void init_dictionary(char **matriz, char **aux, int * nlines, int * ncols) {
    int option = 0;
    char path[] = "C:/Users/swepp/CLionProjects/project2018/data/dicionario.txt";
    char path1[] = "C:/Users/swepp/CLionProjects/project2018/data/dicionario_ordenado.txt";
    int size = read_lines_from_txt(path);
    int size_ordenado = read_lines_from_txt(path1);
    char *palavras[size];
    char **dicionario = NULL;

    printf("Qual dicionario pretende utilizar?:\n");
    printf("(1) Dicionario do ficheiro de texto.\n");
    printf("(2) Inserir Palavras Manualmente.\n");
    printf("(3) Dicionario Ordenado do ficheiro de texto\n");
    printf("(0) Sair!\n\n");

    scanf("%d", &option);
    switch (option) {
        case 1: // DICIONARIO DE TXT
            dicionario = init_dictionary_txt(palavras, size, path);
            run_program(matriz, aux, dicionario, &size, nlines, ncols);
            break;
        case 2: // DICIONARIO LIDO DO STDIN
            init_dictionary_manually(matriz, aux, nlines, ncols);
            break;
        case 3: // DICIONARIO ORDENADO PELO MSD
            dicionario = init_dictionary_txt(palavras, size_ordenado, path1);
            run_program(matriz, aux, dicionario, &size, nlines, ncols);
        case 0:
            return;
        default:
            printf("A opcao que inseriu e invalida, por favor, tente novamente!\n\n");
            init_dictionary(matriz, aux, nlines, ncols);
    }

}

/**
 * @brief FUNÇÃO PARA INICIALIZAÇÃO MANUAL DO DICIONARIO
 * @param matrix
 * @param aux
 * @return
 */
void init_dictionary_manually(char **matrix, char **aux, int *nlines, int *ncols) {
    int size = 0;
    int savingOption = 0;

    printf("Quantas palavras pretende procurar na Sopa de Letras?\n");
    scanf("%d", &size); //leitura de quantas palavras o utilizador pretende inserir (size)

    printf("Insira %d palavras para a procura: \n", size);
    char *matriz_strings[size]; //inicialização de uma matriz de strings para guardar as palavras que o utilizador pretende procurar
    char **matrizDicionario = read_dynarray_strings(matriz_strings, size); //envia a matriz e o tamanho da matriz (nº linhas) como parâmetros para a função read para ler do stdin
    print_dynarray_chars(matrizDicionario, size); //dá print às funções que o read_dynarray_strings leu do stdin

    printf("Pretende guardar o dicionario de palavras que inseriu num ficheiro? \n(1)-Sim\n(2)- Nao\n");
    scanf("%d", &savingOption);
    if (savingOption == 1) {
        save_dictionary_to_txt(matrizDicionario, &size);
    }

    run_program(matrix, aux, matrizDicionario, &size, nlines, ncols);
}

/**
 * @brief FUNÇÃO PARA INICIALIZAÇÃO DO DICIONARIO DE TXT
 * @param str
 * @param size
 * @param path
 * @return
 */
char **init_dictionary_txt(char **str, int size, char *path) {
    char strAux[100] = {};
    FILE *fp;
    fp = fopen(path, "r");  // abre o txt do dicionario no modo para este ser lido
    for (int i = 0; i < size; i++) {
        fgets(strAux, sizeof(strAux), fp);   // copia palavra do file fp, com o tamanho max igual ao size de strAux e guarda-a em strAux
        *(str + i) = create_copy_dyn_string(strAux); //envia strAux para create_copy_dyn_string e o valor retornado é guardado no conteúdo de str na "posição" i
    }

    fclose(fp); // fecha o file fp
    return str; // retorna o array de strings com o dicionario do txt
}


/*---------------------------------------------- GUARDAR/LER TXT ---------------------------------------------- */


/**
 * @brief FUNÇÃO QUE GUARDA UM ARRAY DE STRINGS PARA FICHEIRO TXT
 * @param matrizDicionario
 * @param size
 */
void save_dictionary_to_txt(char ** matrizDicionario, int * size){
    char str[100];
    char path[] = "C:/Users/swepp/CLionProjects/project2018/data/dicionario.txt";
    FILE *fp;
    FILE *fp2;
    fp = fopen(path,"r");   // abre o dicionario em modo read
    fp2 = fopen(path, "a"); // abre dicionario em modo append
    if (!fp) {
        exit(1);
    }
    for(int i=0; i<*size; i++) {
        char *paux = part_dynarray_strings_into_array(matrizDicionario, i); // parte o array em strings
        while (fgets(str,sizeof(str),fp)!=NULL) {   // continua até que não consiga ir buscar mais nada ao ficheiro
            if (strcmp(str, paux) == 0) { // caso a string que "partiu" exita no ficheiro, não adiciona
                printf("%sJa existe no dicionario!\n", paux);
                break;
            }
            else{   // caso não exista, adiciona-a ao final do txt
                printf("%sNao existe no dicionario!\n", paux);
                fprintf(fp2, "%s", paux);
                break;
            }
        }
    }
    fclose(fp); // fecha modo r
    fclose(fp2);    // fecha modo a
}

/**
 * @brief FUNÇÃO QUE LÊ O NUMERO DE LINHAS PRESENTES NO TXT NO CAMINHO 'path'
 * @param path
 * @return
 */
int read_lines_from_txt(char * path) {
    FILE *fp;
    fp = fopen(path, "r"); // abre ficheiro em modo read
    char c;
    int count = 0;  // inicializa contador de linhas

    if (fp == NULL) {
        return 0;   // ERRO caso não encontre ficheiro
    }
    for (c = (char) getc(fp); c != EOF; c = (char) getc(fp)) {
        if (c == '\n') // Incrementa count caso o caracter que encontrou seja um \n
            count = count + 1;
    }
    fclose(fp);

    return count; // retorna count (nº de linhas)
}


int read_cols_from_txt(char * path) {
    FILE *fp;
    fp = fopen(path, "r"); // abre ficheiro em modo read
    char c;
    int count = 0;  // inicializa contador de linhas

    if (fp == NULL) {
        return 0;   // ERRO caso não encontre ficheiro
    }
    for (c = (char) getc(fp); c != '\n'; c = (char) getc(fp)) {
        //if (c != '\n') // Incrementa count caso o caracter que encontrou não seja um \n
        count = count + 1;
    }
    fclose(fp);

    return count; // retorna count (nº de colunas)
}


/*---------------------------------------------- ALOCAÇÃO DE MATRIZES: ALEATÓRIA E AUXILIAR ---------------------------------------------- */


/**
 * @brief FUNÇÃO PARA ALOCAÇÃO DA MATRIZ UTILIZADA NA SOPA DE LETRAS ALEATÓRIA
 * @param l
 * @param c
 * @return
 */
char **allocate_matrix(int l, int c) { //Recebe a quantidade de Linhas e Colunas como Parâmetro

    char alphabet[ALPHABET] = {'A', 'B', 'C', 'D', 'E', 'F', 'G',
                               'H', 'I', 'J', 'K', 'L', 'M', 'N',
                               'O', 'P', 'Q', 'R', 'S', 'T', 'U',
                               'V', 'W', 'X', 'Y', 'Z'};

    int i, j; //Variáveis Auxiliares

    char **m = (char **) malloc(l * sizeof(char *)); //Aloca um Vetor de Ponteiros

    for (i = 0; i < l; i++) { //Percorre as linhas do Vetor de Ponteiros
        *(m + i) = (char *) malloc(c * sizeof(char)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
        for (j = 0; j < c; j++) { //Percorre o Vetor de Inteiros atual.
            char write = alphabet[rand() % ALPHABET]; //Inicializa com 0.
            write_to_matrix(m, i, j, write);
        }
        printf("\n");
    }
    return m; //Retorna o Ponteiro para a Matriz Alocada
}


/**
 * @brief FUNÇÃO DE ALOCAÇÃO DE MATRIZ AUXILIAR (INICIALIZA TODOS OS CAMPOS COM '-')
 * @param l
 * @param c
 * @return
 */
char **allocate_matrix_aux(int l, int c) { //Recebe a quantidade de Linhas e Colunas como Parâmetro

    int i, j; //Variáveis Auxiliares

    char **m = (char **) malloc(l * sizeof(char *)); //Aloca um Vetor de Ponteiros

    for (i = 0; i < l; i++) { //Percorre as linhas do Vetor de Ponteiros
        m[i] = (char *) malloc(c * sizeof(char)); //Aloca um Vetor de Inteiros para cada posição do Vetor de Ponteiros.
        for (j = 0; j < c; j++) { //Percorre o Vetor de Inteiros atual.
            m[i][j] = '-';
        }
    }
    return m; //Retorna o Ponteiro para a Matriz Alocada
}


/* ---------------------------------------------- ESCREVER NA MATRIZ O CARACTER WRITE ---------------------------------------------- */


/**
 * @brief FUNCÃO QUE ESCREVE EM matriz[nlines][ncols] O CHAR GUARDADO EM 'write'
 * @param matriz
 * @param nlines
 * @param ncols
 * @param write
 * @return
 */
char **write_to_matrix(char **matriz, int nlines, int ncols, char write) {
    char *line = *(matriz + nlines);
    *(line + ncols) = write;

    return matriz;
}


/* ---------------------------------------------- FUNÇÕES DE PRINT ---------------------------------------------- */


/**
 * @brief EXECUTA UM PRINT A MATRIZ matrix COM LINHA MAX de LINES e COLUNA MAX de COLS
 * @param matrix
 */
void print_matrix(char **matrix, int * nlines, int * ncols) {
    int i, j;
    for (i = 0; i < *nlines; i++) {
        char *paux = *(matrix + i);
        for (j = 0; j < *ncols; j++) {
            printf("%c ", *(paux + j));
        }
        printf("\n");
    }
    printf("\n");
}

/**
 * @brief FUNÇÃO QUE IMPRIME UMA PALAVRA NO ENDEREÇO = i PARA PROCURA NA SOPA DE LETRAS
 * @param pints
 * @param n
 */
void print_dynarray_chars(char **pints, int n) {
    for (int i = 0; i < n; i++) {
        printf("palavra numero %d do dicionario de procura: %s\n", i, *(pints + i)); //imprime a string de pints no endereço i
    }
    return;
}


/* ---------------------------------------------- DESCODIFICAR A SEQ. MOVIMENTOS ---------------------------------------------- */


 /**
 * @brief FUNÇÃO QUE DESCODIFICA STRING COM OS MOVIMENTOS E IMPRIME
 * @param path
 * @param number
 */
void decode_path(int *path, int *number){
    printf("Path: ");
    for(int i=0; i<(*number); i++){ // i = posição no vetor
        if(i==0){   // caso i = 0, primeira posição, imprime x inicial
            printf("(%d, ", path[i]);
        }
        else if(i==1){  // caso i = 1, segunda posição, imprime y inicial
            printf("%d) ", path[i]);
        }
        else if(i== ((*number)-1)){ // caso i = number-1, penultima posição, imprime y final
            printf("%d)", path[i]);
        }
        else if(i==((*number)-2)){  // caso i = number-2, antepenultima posição, imprime x final
            printf("-->");
            printf(" (%d, ", path[i]);
        }
        else
        {
            printf("-->");
            switch (path[i]){   // nos restantes casos imprime as direções conforme o inteiro guardado
                case 0:
                    printf(" N" );
                    break;
                case 1:
                    printf(" NE ");
                    break;
                case 2:
                    printf(" E ");
                    break;
                case 3:
                    printf(" SE ");
                    break;
                case 4:
                    printf(" S ");
                    break;
                case 5:
                    printf(" SO ");
                    break;
                case 6:
                    printf(" O ");
                    break;
                case 7:
                    printf(" NO ");
                    break;
                default:
                    break;
            }
        }
    }
    printf("\n\n");
    return;
}
