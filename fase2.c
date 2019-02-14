/*
 * Project created and developed by: João Vicente, student number 33969
 * University: Fernando Pessoa University, Porto, Portugal
 * Course: Computer Engineering
 * Curricular Unit: Algoritmos e Estruturas de Dados I & Linguagens de Programação I
 * Date: October 2018 to January 2019
 */

#include "fase2.h"

/*---------------------------------------------------- TABULEIRO -----------------------------------------------------*/

/**
 * @brief funcao para menu de escolha de tabuleiro para inicializacao
 * @return
 */
int main_fase2() {
    char *path = "C:/Users/swepp/CLionProjects/project2018/data/matrix.txt";   // caminho p/ ficheiro tabuleiro
    char *path_dicionario = "C:/Users/swepp/CLionProjects/project2018/data/dicionario.txt";    // ficheiro dicionario
    char **matrix;
    //inicializa tabuleiro
    TABULEIRO tab = {NULL, 0, 0};
    DICIONARIO dic = {0, NULL};
    SOLUCOES sol = {0, NULL, NULL};

    int choice = 0;
    system("cls");
    printf("#########################################################################\n");
    printf("#                         M E N U  D E  J O G O                         #\n");
    printf("#########################################################################\n\n");

    printf("O que pretende realizar:");
    printf("\n\t(1) - Ler Estrutura Tabuleiro atraves de ficheiro TXT!\n");
    printf("\t(2) - Consultar Sopa de Letras de Ficheiro de Texto!\n");
    printf("\t(0) - Sair!\n");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            ler_struct_tabuleiro_txt(&tab);
            ler_struct_sol_txt(&sol);
            insert_struct_sol_into_struct_letra(&tab, sol);
            menu_dicionario(&dic, tab, sol, path_dicionario);
            break;
        case 2:
            tab.lines = read_lines_from_txt_f2(path); //linhas
            tab.cols = read_cols_from_txt_f2(path); //colunas
            matrix = save_txt_into_matrix(path, tab.lines, tab.cols); //copia txt para matriz
            insert_letras_into_tabuleiro(&tab, matrix); //copia matriz para txt
            print_matriz(tab);  // imprime matriz
            guardar_struct_tabuleiro_txt(tab);
            menu_dicionario(&dic, tab, sol, path_dicionario); // entra menu dicionario
            break;
        case 0:
            exit(0);
        default:
            printf("ERRO: Opcao invalida, tente novamente!\n\n");
            main_fase2();
    }
    return 0;
}

/**
 * @brief funcao que le ficheiro txt onde se encontra o tabuleiro e que o guarda num formato de matriz
 * @param path
 * @param lines
 * @param cols
 * @return
 */
char **save_txt_into_matrix(char *path, int lines, int cols) {
    FILE *fp = fopen(path, "r");
    char c;
    char **array = (char **) malloc(sizeof(char *) * lines);
    for (int i = 0; i < lines; i++) {
        *(array + i) = (char *) malloc(sizeof(char) * cols);
    }
    int j = 0;
    int k = 0;
    if (fp == NULL) {
        return 0;
    }
    for (c = (char) getc(fp); c != EOF; c = (char) getc(fp)) {
        if (c != '\n') {
            array[j][k] = c;
            k++;
        } else {
            k = 0;
            j++;
        }
    }
    fclose(fp);
    return array;
}

/**
 * @brief liga os apontadores da estrutura tabuleiro, de acordo com o conteudo da matriz, e preenche-os
 * @param tab
 * @param matrix
 */
void insert_letras_into_tabuleiro(TABULEIRO *tab, char **matrix) { //(DONE)
    LETRA *plines = NULL;
    LETRA *linha = NULL;
    LETRA *pcols = NULL;
    for (int i = 0; i < tab->lines; i++) {
        for (int j = 0; j < tab->cols; j++) {
            if (tab->pfirst == NULL) { // if inicio
                LETRA *pnew = malloc(sizeof(LETRA));
                iniciar_null(pnew);
                pnew->letra = matrix[i][j];
                pnew->line = i;
                pnew->col = j;
                pcols = pnew;
                tab->pfirst = pnew;
            } else {
                if (i == 0) { // if primeira linha
                    if (j == (tab->cols) - 1) {  // if ultima coluna
                        LETRA *pnew = malloc(sizeof(LETRA));
                        iniciar_null(pnew);
                        pnew->letra = matrix[i][j];
                        pnew->line = i;
                        pnew->col = j;
                        pnew->O = pcols;
                        pcols->E = pnew;
                        linha = tab->pfirst;
                        pcols = linha;
                    } else { // meio coluna
                        LETRA *pnew = malloc(sizeof(LETRA));
                        iniciar_null(pnew);
                        pnew->letra = matrix[i][j];
                        pnew->line = i;
                        pnew->col = j;
                        pnew->O = pcols;
                        pcols->E = pnew;
                        pcols = pcols->E;
                    }
                } else // meio/última linha
                {
                    if (j == 0) { // if primeira coluna
                        LETRA *pnew = malloc(sizeof(LETRA));
                        iniciar_null(pnew);
                        pnew->letra = matrix[i][j];
                        pnew->line = i;
                        pnew->col = j;
                        pnew->N = linha;
                        pnew->NE = linha->E;
                        linha->S = pnew;
                        pcols = pnew;
                        linha->E->SO = pnew;
                        plines = linha->E;
                    } else if (j == (tab->cols) - 1) {  // if ultima coluna
                        LETRA *pnew = malloc(sizeof(LETRA));
                        iniciar_null(pnew);
                        pnew->letra = matrix[i][j];
                        pnew->line = i;
                        pnew->col = j;
                        pnew->N = plines;
                        pnew->NO = plines->O;
                        pnew->O = pcols;
                        plines->S = pnew;
                        plines->O->SE = pnew;
                        pcols->E = pnew;
                        linha = linha->S;
                        pcols = linha;
                    } else { // meio coluna
                        LETRA *pnew = malloc(sizeof(LETRA));
                        iniciar_null(pnew);
                        pnew->letra = matrix[i][j];
                        pnew->line = i;
                        pnew->col = j;
                        pnew->N = plines;
                        pnew->NE = plines->E;
                        pnew->NO = plines->O;
                        pnew->O = pcols;
                        pcols->E = pnew;
                        plines->S = pnew;
                        plines->E->SO = pnew;
                        plines->O->SE = pnew;
                        plines = plines->E;
                        pcols = pcols->E;
                    }
                }
            }
        }
    }
    free(matrix);
}

/**
 * @brief imprime conteudo de uma estrutura ligada com 8 apontadores em forma de matriz p/ recriar tabuleiro
 * @param tab
 */
void print_matriz(TABULEIRO tab) {
    LETRA *paux = tab.pfirst;
    LETRA *pline = tab.pfirst;
    printf("#########################################################################\n");
    printf("#                               TABULEIRO                               #\n");
    printf("#########################################################################\n\n");
    for (int i = 0; i < tab.lines; i++) {
        for (int j = 1; j <= tab.cols; j++) {
            if (j == tab.cols) {
                printf("%c", paux->letra);
            } else {
                printf("%c ", paux->letra);
                paux = paux->E;
            }
        }
        printf("\n");
        pline = pline->S;
        paux = pline;
    }
    printf("\n\n");
}

/*--------------------------------------------------- DICIONARIO -----------------------------------------------------*/

/**
 * @brief menu de escolha de dicionario
 * @param dic
 * @param tab
 * @param sol
 * @param path_dicionario
 * @return
 */
int menu_dicionario(DICIONARIO *dic, TABULEIRO tab, SOLUCOES sol, char *path_dicionario) {
    int option = 0;
    int size = 0;
    int merge_option = 0;

    printf("Qual dicionario pretende utilizar?:\n");
    printf("(1) Dicionario do ficheiro de texto.\n");
    printf("(2) Inserir Palavras Manualmente.\n");
    printf("(3) Inserir Posicao e Direcoes\n");
    printf("(4) Ler dicionario gravado anteriormente no ficheiro TXT\n");
    printf("(5) Ler dicionario gravado anteriormente no ficheiro BIN\n");
    printf("(0) Sair!\n\n");

    scanf("%d", &option);
    printf("#########################################################################\n");
    printf("#                              DICIONARIO                               #\n");
    printf("#########################################################################\n");
    switch (option) {
        case 1: // DICIONARIO DE TXT
            dic->nwords = read_lines_from_txt_f2(path_dicionario);
            init_dicionario_from_file(dic, path_dicionario, dic->nwords);
            print_dicionario(*dic);
            menu_guardar_dicionario(*dic);
            printf("\nDeseja ordenar o dicionario, utilizando o algoritmo Merge Sort?\n(1)-Sim\n(2)-Nao\n");
            scanf("%d", &merge_option);
            if (merge_option == 1) {
                menu_merge(tab, dic);
                run_program_f2(tab, *dic, &sol, dic->nwords);
            } else if (merge_option == 2) {
                run_program_f2(tab, *dic, &sol, dic->nwords);
            }
            break;
        case 2: // DICIONARIO LIDO DO STDIN
            init_dicionario_manual(dic);
            menu_guardar_dicionario(*dic);
            printf("\nDeseja ordenar o dicionario, utilizando o algoritmo Merge Sort?\n(1)-Sim\n(2)-Nao\n");
            scanf("%d", &merge_option);
            if (merge_option == 1) {
                menu_merge(tab, dic);
                run_program_f2(tab, *dic, &sol, dic->nwords);
            } else if (merge_option == 2) {
                run_program_f2(tab, *dic, &sol, dic->nwords);
            }
            break;
        case 3: // INSERIR POSICOES E DIRECOES MANUAL
            printf("Quantas direcoes? \n");
            scanf("%d", &size);
            recebe_posicao_direcoes(tab, &size);
            int yesOrNo; // Caso queira ou não realizar mais alguma ação na sopa de letras
            printf("\n\nDeseja realizar mais alguma acao?\n(1)-Sim\n(2)-Nao\n");
            scanf("%d", &yesOrNo);
            if (yesOrNo == 1) {
                main_fase2();
            } else {
                return 0;
            }
            break;
        case 4:
            ler_struct_dicionario_txt(dic);
            print_dicionario(*dic);
            run_program_f2(tab, *dic, &sol, dic->nwords);
            break;
        case 5:
            ler_struct_dic_bin(dic);
            print_dicionario(*dic);
            run_program_f2(tab, *dic, &sol, dic->nwords);
        case 0:
            return 0;
        default:
            printf("A opcao que inseriu e invalida, por favor, tente novamente!\n\n");
            menu_dicionario(dic, tab, sol, path_dicionario);
    }
}

/**
 * @brief menu para escolha de guardar o dicionario em ficheiro TXT ou BIN
 * @param dic
 */
void menu_guardar_dicionario(DICIONARIO dic){
    int option=0;
    printf("\nDeseja guardar o dicionario num ficheiro TXT?\n(1)-Sim\n(2)-Nao\n");
    scanf("%d", &option);
    if(option == 1){
        guardar_struct_dicionario_txt(dic);
    }
    else if(option == 2) {

    }
    printf("\nDeseja guardar o dicionario num ficheiro BIN?\n(1)-Sim\n(2)-Nao\n");
    scanf("%d", &option);
    if(option == 1){
        guardar_struct_dic_bin(dic);
    }
    else if(option == 2) {

    }
}

/**
 * @brief funcao de inicializacao de dicionario de ficheiro TXT
 * @param dic
 * @param path
 * @param size
 */
void init_dicionario_from_file(DICIONARIO *dic, char *path, int size) {
    PALAVRA *paux = NULL;
    FILE *fp = fopen(path, "r");
    char strAux[100];
    for (int i = 0; i <= size; i++) {
        if (dic->pfirst == NULL) {
            fgets(strAux, sizeof(strAux), fp);
            PALAVRA *pnew = malloc(sizeof(PALAVRA));
            iniciar_palavra_null(pnew);
            pnew->word = create_copy_dyn_string_f2(strAux);
            pnew->size = strlen(pnew->word);
            dic->pfirst = pnew;
            paux = pnew;
            size--;
        } else {
            fgets(strAux, sizeof(strAux), fp);
            PALAVRA *pnew = malloc(sizeof(PALAVRA));
            iniciar_palavra_null(pnew);
            pnew->word = create_copy_dyn_string_f2(strAux);
            pnew->size = strlen(pnew->word);
            paux->pnext = pnew;
            paux = pnew;
        }
    }
    fclose(fp);
}

/**
 * @brief ALOCA MEMÓRIA DINâMICA E CRIA UM ARRAY DINAMICO COM A STRING RECEBIDA DE read_dynarray_strings (COM TAMANHO +1 PARA ADICIONAR \n)
 * @param str
 * @return
 */
char *create_copy_dyn_string_f2(char *str) {
    char *pc = malloc(
            strlen(str) + 1 * sizeof(char));  //aloca memória com o tamanho da string str recebida +1 e guarda em *pc
    strcpy(pc, str);    //copia str para pc

    return pc; //retorna pc
}

/**
 * @brief funcao que le palavras do stdin e as guarda em lista ligada dicionario
 * @param dic
 */
void init_dicionario_manual(DICIONARIO *dic) {
    int size = 0;
    PALAVRA *paux = NULL;
    char strAux[100];   //inicializa uma string com tamanho 100 (tamanho máx do que poderá ser lido no stdin)

    printf("Quantas palavras pretende procurar na Sopa de Letras?\n");
    scanf("%d", &size); //leitura de quantas palavras o utilizador pretende inserir (size)

    printf("Insira %d palavras para a procura: \n", size);
    dic->nwords = size;

    for (int i = 0; i < size; i++) {
        fflush(stdin);  //utilizado para limpar o buffer de input
        if (dic->pfirst == NULL) {
            fgets(strAux, sizeof(strAux), stdin);
            PALAVRA *pnew = malloc(sizeof(PALAVRA));
            iniciar_palavra_null(pnew);
            pnew->word = create_copy_dyn_string_f2(strAux);
            pnew->size = strlen(pnew->word);
            dic->pfirst = pnew;
            paux = pnew;
        } else {
            fgets(strAux, sizeof(strAux), stdin);
            PALAVRA *pnew = malloc(sizeof(PALAVRA));
            iniciar_palavra_null(pnew);
            pnew->word = create_copy_dyn_string_f2(strAux);
            pnew->size = strlen(pnew->word);
            paux->pnext = pnew;
            paux = pnew;
        }
    }
}

/**
 * @brief funcao para print de dicionario
 * @param dic
 */
void print_dicionario(DICIONARIO dic) {
    PALAVRA *paux = dic.pfirst;
    printf("\nPALAVRAS:\n\n");
    for (int i = 0; i < dic.nwords; i++) {
        printf(" - %s", paux->word);
        paux = paux->pnext;
    }
}

/**
 * @brief funcao que utiliza o dicionario ordenado para a pesquisa de resultados na funcao find_path
 * @param tab
 * @param dic
 * @param n
 */
void modifica_dicionario_ordenado(TABULEIRO tab, DICIONARIO *dic, struct Node **n) {
    char path[] = "C:\\Users\\swepp\\CLionProjects\\project2018\\data\\dicionario_ordenado.txt";
    int size = dic->nwords;
    SOLUCOES sol = {0, NULL};
    DICIONARIO dic2 = {size, NULL};
    FILE *fp;
    fp = fopen(path, "w");
    struct Node *paux = *(n + 0);
    for (int i = 0; i < size; i++) {
        fprintf(fp, "%s", paux->data);
        paux = paux->next;
    }
    fclose(fp);
    free(dic);
    init_dicionario_from_file(&dic2, path, size);
    printf("\n#########################################################################\n");
    printf("#                              DICIONARIO                               #\n");
    printf("#########################################################################\n\n");
    print_dicionario(dic2);
    run_program_f2(tab, dic2, &sol, dic2.nwords);
}

/*--------------------------------------------------- PESQUISA -------------------------------------------------------*/

/**
 * @brief Algoritmo de procura de caminho
 * @param tab
 * @param l
 * @param p
 * @param c
 * @param sol
 * @param line
 * @param column
 * @param pos_i
 * @param solutionCount
 */
void find_path_f2(TABULEIRO tab, LETRA *l, PALAVRA *p, CAMINHO *c, SOLUCOES *sol, int line, int column, int *pos_i,
                  int *solutionCount) {
    char charAux;   // inicializa charAux
    charAux = *((p->word) + (*pos_i));

    if (charAux == '\n') { // caso o caracter seja um \n, então a palavra terminou e podemos imprimir a matriz
        (*solutionCount)++; // incrementa o valor do count para apresentar o número de correspondências para a palavra em causa
        c->y_final = column;
        c->x_final = line;
        c->check = 1;
        sol->nsolucoes++;
        if (sol->pfirst != NULL) {
            CAMINHO *cnew = malloc(sizeof(CAMINHO));
            iniciar_caminho_null(cnew);
            cnew->y_inicial = sol->plast->y_inicial;
            cnew->x_inicial = sol->plast->x_inicial;
            cnew->direcoes = sol->plast->direcoes;
            cnew->palavra = sol->plast->palavra;
            sol->plast->pnext = cnew;
            sol->plast = cnew;
        }

        //printf("x: %d\ty: %d\tdir: %d\n",c->x_inicial, c->y_inicial, c->direcoes);
        //printf("CAUX: x: %d\ty: %d\tdir: %d\n\n",caux->x_inicial, caux->y_inicial, caux->direcoes);
        return; //retorna para a função anterior
    }

    if (check_consistency_f2(tab, l->N, *p, charAux, line - 1, column) == 1) {
        //Norte
        (*pos_i)++;
        c->direcoes = (c->direcoes) * 10;
        c->direcoes = (c->direcoes) + 1;
        find_path_f2(tab, l->N, p, sol->plast, sol, line - 1, column, pos_i, solutionCount);
        c = sol->plast;
        c->direcoes = (c->direcoes) - 1;
        c->direcoes = (c->direcoes) / 10;
        (*pos_i)--;
    }

    if (check_consistency_f2(tab, l->NE, *p, charAux, line - 1, column + 1) == 1) {
        //Nordeste
        (*pos_i)++;
        c->direcoes = (c->direcoes) * 10;
        c->direcoes = (c->direcoes) + 2;
        find_path_f2(tab, l->NE, p, sol->plast, sol, line - 1, column + 1, pos_i, solutionCount);
        c = sol->plast;
        c->direcoes = (c->direcoes) - 2;
        c->direcoes = (c->direcoes) / 10;
        (*pos_i)--;
    }

    if (check_consistency_f2(tab, l->E, *p, charAux, line, column + 1) == 1) {
        //Este
        (*pos_i)++;
        c->direcoes = (c->direcoes) * 10;
        c->direcoes = (c->direcoes) + 3;
        find_path_f2(tab, l->E, p, sol->plast, sol, line, column + 1, pos_i, solutionCount);
        c = sol->plast;
        c->direcoes = (c->direcoes) - 3;
        c->direcoes = (c->direcoes) / 10;
        (*pos_i)--;
    }

    if (check_consistency_f2(tab, l->SE, *p, charAux, line + 1, column + 1) == 1) {
        //Sudeste
        (*pos_i)++;
        c->direcoes = (c->direcoes) * 10;
        c->direcoes = (c->direcoes) + 4;
        find_path_f2(tab, l->SE, p, sol->plast, sol, line + 1, column + 1, pos_i, solutionCount);
        c = sol->plast;
        c->direcoes = (c->direcoes) - 4;
        c->direcoes = (c->direcoes) / 10;
        (*pos_i)--;
    }

    if (check_consistency_f2(tab, l->S, *p, charAux, line + 1, column) == 1) {
        //Sul
        (*pos_i)++;
        c->direcoes = (c->direcoes) * 10;
        c->direcoes = (c->direcoes) + 5;
        find_path_f2(tab, l->S, p, sol->plast, sol, line + 1, column, pos_i, solutionCount);
        c = sol->plast;
        c->direcoes = (c->direcoes) - 5;
        c->direcoes = (c->direcoes) / 10;
        (*pos_i)--;
    }

    if (check_consistency_f2(tab, l->SO, *p, charAux, line + 1, column - 1) == 1) {
        //Sudoeste
        (*pos_i)++;
        c->direcoes = (c->direcoes) * 10;
        c->direcoes = (c->direcoes) + 6;
        find_path_f2(tab, l->SO, p, sol->plast, sol, line + 1, column - 1, pos_i, solutionCount);
        c = sol->plast;
        c->direcoes = (c->direcoes) - 6;
        c->direcoes = (c->direcoes) / 10;
        (*pos_i)--;
    }

    if (check_consistency_f2(tab, l->O, *p, charAux, line, column - 1) == 1) {
        //Oeste
        (*pos_i)++;
        c->direcoes = (c->direcoes) * 10;
        c->direcoes = (c->direcoes) + 7;
        find_path_f2(tab, l->O, p, sol->plast, sol, line, column - 1, pos_i, solutionCount);
        c = sol->plast;
        c->direcoes = (c->direcoes) - 7;
        c->direcoes = (c->direcoes) / 10;
        (*pos_i)--;
    }

    if (check_consistency_f2(tab, l->NO, *p, charAux, line - 1, column - 1) == 1) {
        //Noroeste
        (*pos_i)++;
        c->direcoes = (c->direcoes) * 10;
        c->direcoes = (c->direcoes) + 8;
        find_path_f2(tab, l->NO, p, sol->plast, sol, line - 1, column - 1, pos_i, solutionCount);
        c = sol->plast;
        c->direcoes = (c->direcoes) - 8;
        c->direcoes = (c->direcoes) / 10;
        (*pos_i)--;
    }
}

/**
 * @brief FUNÇÃO QUE VERIFICA SE O CHAR C NAS COORDENADAS (N, S, E, O, NE, NO, SE, SO) SE ENCONTRA DENTRO DO TABULEIRO, CASO ESTEJA VERIFICA SE O CHAR C É = A LETRA NA CELULA
 * @param tab
 * @param l
 * @param c
 * @param line
 * @param column
 * @return
 */
int check_consistency_f2(TABULEIRO tab, LETRA *l, PALAVRA p, char c, int line, int column) {
    if (line >= 0 && line < tab.lines && column >= 0 &&
        column < tab.cols) {    // Verifica se a linha e a coluna enviadas estão dentro da matriz
        if (l->letra == c) { // Verifica se o caracter recebido se encontra na matriz "lab"
            CAMINHO * paux = l->p_sol_first; // Apontador para o primeiro caminho da celula
            if(paux == NULL){  // Caso seja nulo, retorna 1, para realizar procura de palavras
                return 1;
            }
            while(paux != NULL) { // Caso contrário procura se a palavra à procura, já existe na cache, caso exista retorna 0
                if(paux->palavra == p.word){ // palavra da procura = palavra da cache
                    return 0;
                }
                paux = paux->pnext; // passa para a proxima palavra
            }
            return 1;
        }
    }
    return 0;
}

/**
 * @brief funcao de inicializacao da pesquisa de acordo com o tabuleiro e dicionario escolhidos nos menus
 * @param tab
 * @param dic
 * @param sol
 * @param size
 * @return
 */
int run_program_f2(TABULEIRO tab, DICIONARIO dic, SOLUCOES *sol, int size) {
    int solutionCount = 0;// INICIALIZA CONTADOR DE SOLUÇÃO
    int pos_i = 1;
    int yesOrNo; // Caso queira ou não realizar mais alguma ação na sopa de letras
    LETRA *inicial = tab.pfirst; // apontador para a celula inicial do tabuleiro
    LETRA *percorrer = tab.pfirst; // apontador para a celula a percorrer
    PALAVRA *paux = dic.pfirst; // apontador para a palavra inicial do dicionario
    printf("\n\n#########################################################################\n");
    printf("#                               PESQUISA                                #\n");
    printf("#########################################################################\n\n");
    for (int i = 0; i < size; i++) {
        CAMINHO *c = malloc(sizeof(CAMINHO)); // alocacao de 1 novo caminho
        iniciar_caminho_null(c);
        printf("Vai procurar a palavra: %s\n", paux->word);    // Print a informar que vai procurar a palavra "paux"
        c->palavra = paux->word; // palavra do caminho = palavra do dicionario
        if (sol->pfirst == NULL) { // se n existir caminhos, insere o primeiro e o ultimo como sendo c
            sol->pfirst = c;
            sol->plast = c;
        } else {
            CAMINHO *caux = sol->pfirst; // apontador de caminho auxiliar para o primeiro caminho
            while (caux->pnext != sol->plast) { // itera pelas solucoes ate chegar à penultima
                caux = caux->pnext;
            }
            caux->pnext = c; // declara a seguinte da penultima como sendo c
            sol->plast = c; // declara a ultima como sendo c
        }

        for (int l = 0; l < tab.lines; l++) {   // itera pelo nº de linhas
            for (int col = 0; col < tab.cols; col++) { // itera pelo número de colunas
                if (check_consistency_f2(tab, percorrer, *paux,*((c->palavra) + 0), l, col == 1)) {
                    c = sol->plast;
                    c->x_inicial = l;    // envia na primeira posição o x inicial
                    c->y_inicial = col;  // envia na segunda posição o y inicial
                    find_path_f2(tab, percorrer, paux, sol->plast, sol, l, col, &pos_i,
                                 &solutionCount);   //verifica se na matriz "fase1" existe continuação da palavra com o caracter copiado para a matriz auxiliar
                    pos_i = 1;
                }
                percorrer = percorrer->E; // vai para a letra na coluna seguinte na mesma linha
            }
            percorrer = inicial->S; // passa a letra presente na primeira coluna na linha seguinte
            inicial = inicial->S; // passa a apontar para a primeira coluna da linha seguinte
        }

        if (solutionCount > 1) { // CASO A VARIÁVEL "global_count" SEJA > 1 VAI HAVER MUITAS SOLUÇÕES
            printf("Existem %d solucoes\n\n", solutionCount); //IMPRIME Nº SOLUÇÕES
        } else if (solutionCount == 1) {
            printf("Existe %d solucao\n\n", solutionCount); // PARA O CASO DE APENAS 1 SOLUÇÃO
        } else {
            printf("ERRO: Nao existem solucoes\n\n"); // CASO NENHUMA SOLUÇÃO
        }
        solutionCount = 0; // LIMPA O COUNT

        inicial = tab.pfirst; // inicializa o apontador a letra inicial para a primeira
        percorrer = tab.pfirst; // inicializa percorrer como a primeira letra do tabuleiro
        paux = paux->pnext; // passa a proxima palavra
    }

    printf("\nDeseja imprimir todos os resultados?\n(1)-Sim\n(2)-Nao\n");
    scanf("%d", &yesOrNo);
    if (yesOrNo == 1) {
        print_lista_solucoes(sol);
    }

    yesOrNo = 0; // Caso queira guardar os resultados num ficheiro TXT
    printf("\nDeseja guardar todos os resultados em ficheiro?\n(1)-Sim\n(2)-Nao\n");
    scanf("%d", &yesOrNo);
    if (yesOrNo == 1) {
        guardar_struct_sol_txt(*sol);
    }

    yesOrNo = 0; // Caso queira realizar mais alguma açao no programa
    printf("\nDeseja realizar mais alguma acao?\n(1)-Sim\n(2)-Nao\n");
    scanf("%d", &yesOrNo);
    if (yesOrNo == 1) {
        main_fase2();
    } else {
        return 0;
    }
}

/**
 * @brief funcao de impressao da lista ligada de resultados
 * @param s
 */
void print_lista_solucoes(SOLUCOES *s) {
    printf("\n\n#########################################################################\n");
    printf("#                              RESULTADOS                               #\n");
    printf("#########################################################################\n\n");
    CAMINHO *paux = s->pfirst;
    int aux = 0;
    char *string = malloc(sizeof(paux->palavra));
    while (paux != s->plast) {
        if (strcmp(string, paux->palavra) != 0) {
            printf("\n");
            printf("%s", paux->palavra);
            string = paux->palavra;
        }
        printf("(%d,%d) -> ", paux->x_inicial, paux->y_inicial);
        aux = inverter_numero(paux->direcoes);
        decode_dir(aux);
        printf("(%d, %d)\n", paux->x_final, paux->y_final);

        paux = paux->pnext;
    }
}

/**
 * @brief inverte um inteiro
 * @param number
 * @return
 */
int inverter_numero(int number) {
    int resto = 0;
    int aux = number;
    int invertido = 0;
    for (int i = 0; aux % 10 != 0; i++) {
        resto = aux % 10;
        aux = aux / 10;
        invertido *= 10;
        invertido += resto;
    }
    invertido += aux;

    return invertido;
}

/*-------------------------------------------- LEITURA LINHAS/ COLUNAS TXT -------------------------------------------*/

/**
 * @brief funcao que le o numero de linhas de um ficheiro
 * @param path
 * @return
 */
int read_lines_from_txt_f2(char *path) {
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

/**
 * @brief funcao que le numero de colunas de um ficheiro
 * @param path
 * @return
 */
int read_cols_from_txt_f2(char *path) {
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

/*-------------------------------------------- ALGORITMO MERGE SORT (R.6) --------------------------------------------*/

/**
 * @brief funcao apos escolha de ordenacao do dicionario, onde inicia o algoritmo Merge Sort
 * @param tab
 * @param dic
 */
void menu_merge(TABULEIRO tab, DICIONARIO *dic) {
    int op = 0;
    printf("\n#########################################################################\n");
    printf("#                          DICIONARIO ORDENADO                          #\n");
    printf("#########################################################################\n\n");
    struct Node **n = NULL;
    n = ordena_dic(*dic);
    printf("Deseja realizar a pesquisa com qual dicionario?\n(1)-Normal\n(2)-Ordenado\n");
    scanf("%d", &op);
    if (op == 1) {
        return;
    } else if (op == 2) {
        modifica_dicionario_ordenado(tab, dic, n);
        return;
    } else {
        printf("ERRO: OPCAO NAO RECONHECIDA!!!\n\n");
    }
}

/**
 * @brief funcao de inicializacao da ordenacao utilizando o algoritmo "Merge Sort", reutilizado
 * @param dic
 * @return
 */
struct Node **ordena_dic(DICIONARIO dic) {
    struct Node **new_node = (struct Node **) malloc(sizeof(struct Node *));
    PALAVRA *data = dic.pfirst;
    int i = 0;
    while (i < dic.nwords) {
        addElement(new_node, data->word, i);
        if (data->pnext != NULL) {
            i++;
            data = data->pnext;
        } else {
            i++;
        }
    }

    MergeSort(new_node, 1);
    printList(*(new_node + 0));

    return new_node;
}

/*------------------------------------------ MANIPULACAO STRUCTS TXT (R.12) ------------------------------------------*/

/**
 * @brief le um ficheiro TXT que contem os campos de uma estrutura utilizada anteriormente e inicializa a estrutura com os mesmos dados
 * @param dic
 */
void ler_struct_dicionario_txt(DICIONARIO *dic) {
    char path[] = {"C:\\Users\\swepp\\CLionProjects\\project2018\\data\\struct_dic.txt"};
    FILE *fp;
    char palavra[100];
    int size = 0;
    fp = fopen(path, "r");
    if (fp != NULL) {
        fscanf(fp, "%*s %*s %d\n", &dic->nwords);
        if (dic->nwords) {
            PALAVRA *current = malloc(sizeof(PALAVRA)), *previous;
            dic->pfirst = current;
            int numero_palavras = dic->nwords;
            for (int i = 0; i < numero_palavras; i++) {
                fscanf(fp, "%s %d", palavra, &size);
                current->word = malloc(sizeof(char) * (strlen(palavra) + 2));
                strcpy(current->word, palavra);
                strcat(current->word, "\n");
                current->size = size;
                previous = current;
                if (i == dic->nwords - 1)
                    current = NULL;
                else
                    current = malloc(sizeof(PALAVRA));
                previous->pnext = current;
            }
        }
        fclose(fp);
    }
}

/**
 * @brief guarda todos os campos da estrutura dicionario num ficheiro TXT
 * @param dic
 */
void guardar_struct_dicionario_txt(DICIONARIO dic) {
    char path[] = {"C:\\Users\\swepp\\CLionProjects\\project2018\\data\\struct_dic.txt"};
    FILE *fp;
    fp = fopen(path, "w");
    if (fp != NULL) {
        fprintf(fp, "Numero palavras: %d", dic.nwords);
        fprintf(fp, "\n");
        PALAVRA *temp = dic.pfirst;
        for (int i = 0; i < dic.nwords; i++) {
            fprintf(fp, "%s %d\n", temp->word, temp->size);
            temp = temp->pnext;
        }
        fclose(fp);
    } else
        printf("O Ficheiro nao foi aberto!\n");
}

/**
 * @brief guarda os campos da estrutura tabuleiro num ficheiro TXT
 * @param tab
 */
void guardar_struct_tabuleiro_txt(TABULEIRO tab) {
    char path[] = {"C:\\Users\\swepp\\CLionProjects\\project2018\\data\\struct_tab.txt"};
    FILE *fp;
    fp = fopen(path, "w");
    if (fp != NULL) {
        LETRA *temp = tab.pfirst;
        LETRA *linha = tab.pfirst;
        for (int i = 0; i < tab.lines; i++) {
            for (int j = 0; j < tab.cols; j++) {
                fprintf(fp, "%c", temp->letra);
                temp = temp->E;
            }
            fprintf(fp, "\n");
            linha = linha->S;
            temp = linha;
        }
        fclose(fp);
    } else
        printf("O ficheiro nao foi aberto!\n");
}

/**
 * @brief le um ficheiro TXT que contem os campos de uma estrutura 'TABULEIRO' utilizada anteriormente e inicializa a estrutura com os mesmos dados
 * @param tab
 */
void ler_struct_tabuleiro_txt(TABULEIRO *tab) {
    char **matrix;
    char path[] = {"C:\\Users\\swepp\\CLionProjects\\project2018\\data\\struct_tab.txt"};

    tab->lines = read_lines_from_txt(path);
    tab->cols = read_cols_from_txt(path);
    matrix = save_txt_into_matrix(path, tab->lines, tab->cols);
    insert_letras_into_tabuleiro(tab, matrix); //copia matriz para txt
    print_matriz(*tab);  // imprime matriz
}

/**
 * @brief Guarda a estrutura 'SOLUCOES' em ficheiro TXT
 * @param sol
 */
void guardar_struct_sol_txt(SOLUCOES sol) {
    char path[] = {"C:\\Users\\swepp\\CLionProjects\\project2018\\data\\struct_sol.txt"};
    FILE *fp;
    fp = fopen(path, "w");
    if (fp != NULL) {
        fprintf(fp, "Numero solucoes: %d\n", sol.nsolucoes);
        CAMINHO *temp = sol.pfirst;
        for (int i = 0; i < sol.nsolucoes; i++) {
            fprintf(fp, "%s %d %d %d %d %d %d\n", temp->palavra, temp->x_inicial, temp->y_inicial, temp->direcoes,
                    temp->x_final, temp->y_final, temp->check);
            temp = temp->pnext;
        }
        fclose(fp);
    } else
        printf("O ficheiro nao foi aberto!\n");
}

/**
 * @brief Le ficheiro TXT e preenche a estrutura 'SOLUCOES' com a lista ligada de estruturas 'CAMINHO' com os dados presentes no TXT para cada caminho
 * @param sol
 */
void ler_struct_sol_txt(SOLUCOES *sol) {
    char path[] = {"C:\\Users\\swepp\\CLionProjects\\project2018\\data\\struct_sol.txt"};
    FILE *fp;
    char palavra[100];
    int dir = 0, check = 0, x_i = 0, x_f = 0, y_i = 0, y_f = 0;
    fp = fopen(path, "r");
    if (fp != NULL) {
        fscanf(fp, "%*s %*s %d\n", &sol->nsolucoes);
        if (&sol->nsolucoes) {
            CAMINHO *current = malloc(sizeof(CAMINHO)), *previous;
            sol->pfirst = current;
            int numero_palavras = sol->nsolucoes;
            for (int i = 0; i < numero_palavras; i++) {
                fscanf(fp, "%s %d %d %d %d %d %d\n", palavra, &x_i, &y_i, &dir, &x_f, &y_f, &check);
                current->palavra = malloc(sizeof(char) * (strlen(palavra) + 2));
                strcpy(current->palavra, palavra);
                strcat(current->palavra, "\n");
                current->x_inicial = x_i;
                current->y_inicial = y_i;
                current->direcoes = dir;
                current->x_final = x_f;
                current->y_final = y_f;
                current->check = check;
                previous = current;
                if (i == sol->nsolucoes - 1) {
                    current = NULL;
                    sol->plast = previous;
                } else
                    current = malloc(sizeof(CAMINHO));
                previous->pnext = current;
            }
        }
        fclose(fp);
    }
}

/**
 * @brief Insere os caminhos (soluções) na estrutura letra onde esse caminho teve origem (CACHE)
 * @param tab
 * @param sol
 */
void insert_struct_sol_into_struct_letra(TABULEIRO *tab, SOLUCOES sol) {
    LETRA *temp = tab->pfirst;
    LETRA *linha = tab->pfirst;
    CAMINHO *psol = sol.pfirst;
    for (int i = 0; i < tab->lines; i++) {
        for (int j = 0; j < tab->cols; j++) {
            CAMINHO *pant = NULL;
            while (psol != NULL) {
                if (temp->line == psol->x_inicial && temp->col == psol->y_inicial) {
                    if (temp->p_sol_first == NULL) {
                        CAMINHO *paux = malloc(sizeof(CAMINHO));
                        iniciar_caminho_null(paux);
                        paux->palavra = malloc(sizeof(char) * strlen(psol->palavra) + 1);
                        strcpy(paux->palavra, psol->palavra);
                        paux->direcoes = psol->direcoes;
                        paux->y_inicial = psol->y_inicial;
                        paux->y_final = psol->y_final;
                        paux->x_inicial = psol->x_inicial;
                        paux->check = psol->check;
                        paux->x_final = psol->x_final;
                        pant = paux;
                        temp->p_sol_first = pant;
                    } else {
                        CAMINHO *paux = malloc(sizeof(CAMINHO));
                        iniciar_caminho_null(paux);
                        paux->palavra = malloc(sizeof(char) * strlen(psol->palavra) + 1);
                        strcpy(paux->palavra, psol->palavra);
                        paux->direcoes = psol->direcoes;
                        paux->y_inicial = psol->y_inicial;
                        paux->y_final = psol->y_final;
                        paux->x_inicial = psol->x_inicial;
                        paux->check = psol->check;
                        paux->x_final = psol->x_final;
                        pant->pnext = paux;
                        pant = paux;
                    }
                }
                psol = psol->pnext;
            }
            psol = sol.pfirst;
            temp = temp->E;
        }
        linha = linha->S;
        temp = linha;
    }
}

/*------------------------------------------------ REQUISITO 10 ------------------------------------------------------*/

/**
 * @brief funcao que recebe numero de direcoes, direcoes, e posicao inicial que deseja tomar e retorna sequencia de caracteres correspondente
 * @param tab
 * @param size
 * @return
 */
char *recebe_posicao_direcoes(TABULEIRO tab, int *size) {
    int x, y;
    char strAux[100];
    int i = 0;
    LETRA *pnew = NULL;
    LETRA *pline = NULL;
    printf("Insira linha inicial, entre 0 e %d:\n ", tab.lines);
    scanf("%d", &x);
    printf("Insira coluna inicial, entre 0 e %d:\n ", tab.cols);
    scanf("%d", &y);
    if (x < 0 || x > tab.lines || y < 0 || y > tab.cols) {
        printf("ERRO: INSERIU COORDENADAS FORA DO TABULEIRO!!\n");
        return NULL;
    }
    char *array_letras = (char *) malloc(sizeof(char) * (*size));
    char **direcoes = (char **) malloc(sizeof(char *) * (*size));
    for (int j = 0; j < *size; j++) {
        *(direcoes + j) = (char *) malloc(sizeof(char) * 4);
    }
    printf("Insira as direcoes!! (PALAVRAS SEPARADAS POR ENTERS): \n");
    fflush(stdin);
    while (i < *size) {
        fgets(strAux, sizeof(strAux), stdin);
        *(direcoes + i) = create_copy_dyn_string_f2(strAux);
        i++;
        fflush(stdin);
    }
    pnew = tab.pfirst;
    pline = tab.pfirst;
    for (int l = 0; l < tab.lines; l++) {
        for (int col = 0; col < tab.cols; col++) {
            if (pnew->line == x && pnew->col == y) {
                *(array_letras + 0) = pnew->letra;
                for (int k = 0; k < *size; k++) {
                    char *paux = *(direcoes + k);
                    if (*(paux + 0) == (char) 'N' && *(paux + 1) == (char) '\n' ||
                        *(paux + 0) == (char) 'n' && *(paux + 1) == (char) '\n') {
                        pnew = pnew->N;
                        if (pnew != NULL) {
                            *(array_letras + k + 1) = pnew->letra;
                        } else {
                            printf("\n\nERRO, NAO EXISTE LETRA NA DIRECAO N\n");
                            return NULL;
                        }
                    } else if (*(paux + 0) == (char) 'N' && *(paux + 1) == (char) 'E' ||
                               *(paux + 0) == (char) 'n' && *(paux + 1) == (char) 'e') {
                        pnew = pnew->NE;
                        if (pnew != NULL) {
                            *(array_letras + k + 1) = pnew->letra;
                        } else {
                            printf("\n\nERRO, NAO EXISTE LETRA NA DIRECAO NE\n");
                            return NULL;
                        }
                    } else if (*(paux + 0) == (char) 'E' && *(paux + 1) == (char) '\n' ||
                               *(paux + 0) == (char) 'e' && *(paux + 1) == (char) '\n') {
                        pnew = pnew->E;
                        if (pnew != NULL) {
                            *(array_letras + k + 1) = pnew->letra;
                        } else {
                            printf("\n\nERRO, NAO EXISTE LETRA NA DIRECAO E\n");
                            return NULL;
                        }
                    } else if (*(paux + 0) == (char) 'S' && *(paux + 1) == (char) 'E' ||
                               *(paux + 0) == (char) 's' && *(paux + 1) == (char) 'e') {
                        pnew = pnew->SE;
                        if (pnew != NULL) {
                            *(array_letras + k + 1) = pnew->letra;
                        } else {
                            printf("\n\nERRO, NAO EXISTE LETRA NA DIRECAO SE\n");
                            return NULL;
                        }
                    } else if (*(paux + 0) == (char) 'S' && *(paux + 1) == (char) '\n' ||
                               *(paux + 0) == (char) 's' && *(paux + 1) == (char) '\n') {
                        pnew = pnew->S;
                        if (pnew != NULL) {
                            *(array_letras + k + 1) = pnew->letra;
                        } else {
                            printf("\n\nERRO, NAO EXISTE LETRA NA DIRECAO S\n");
                            return NULL;
                        }
                    } else if (*(paux + 0) == (char) 'S' && *(paux + 1) == (char) 'O' ||
                               *(paux + 0) == (char) 's' && *(paux + 1) == (char) 'o') {
                        pnew = pnew->SO;
                        if (pnew != NULL) {
                            *(array_letras + k + 1) = pnew->letra;
                        } else {
                            printf("\n\nERRO, NAO EXISTE LETRA NA DIRECAO SO\n");
                            return NULL;
                        }
                    } else if (*(paux + 0) == (char) 'O' && *(paux + 1) == (char) '\n' ||
                               *(paux + 0) == (char) 'o' && *(paux + 1) == (char) '\n') {
                        pnew = pnew->O;
                        if (pnew != NULL) {
                            *(array_letras + k + 1) = pnew->letra;
                        } else {
                            printf("\n\nERRO, NAO EXISTE LETRA NA DIRECAO O\n");
                            return NULL;
                        }
                    } else if (*(paux + 0) == (char) 'N' && *(paux + 0) == (char) 'O' ||
                               *(paux + 0) == (char) 'n' && *(paux + 0) == (char) 'o') {
                        pnew = pnew->NO;
                        if (pnew != NULL) {
                            *(array_letras + k + 1) = pnew->letra;
                        } else {
                            printf("\n\nERRO, NAO EXISTE LETRA NA DIRECAO NO\n");
                            return NULL;
                        }
                    }
                }
                print_array_letras(array_letras, size);
                return array_letras;
            }
            pnew = pnew->E;
        }
        pline = pline->S;
        pnew = pline;
    }
}

/**
 * @brief funcao para impressao dos caracteres da sequencia correspondente a funçao "char * recebe_posicao_direcoes(TABULEIRO tab, int * size)"
 * @param array
 * @param size
 */
void print_array_letras(char *array, int *size) {
    printf("Lista de caracteres: \n\n");
    for (int i = 0; i <= (*size); i++) {
        if (i < *size) {
            printf("%c -> ", *(array + i));
        } else
            printf("%c", *(array + i));
    }

}

/*------------------------------------------------ REQUISITO 11 ------------------------------------------------------*/

/**
 * @brief funcao para descodificar inteiro de direcoes e imprimir as mesmas
 * @param aux
 */
void decode_dir(int aux) {
    int resto;
    for (int i = 0; aux > 10; i++) {
        resto = aux % 10;
        if (resto == 1) {
            printf("N -> ");
        } else if (resto == 2) {
            printf("NE -> ");
        } else if (resto == 3) {
            printf("E -> ");
        } else if (resto == 4) {
            printf("SE -> ");
        } else if (resto == 5) {
            printf("S -> ");
        } else if (resto == 6) {
            printf("SO -> ");
        } else if (resto == 7) {
            printf("O -> ");
        } else if (resto == 8) {
            printf("E -> ");
        }
        aux /= 10;
    }
    if (aux % 10 != 0) {
        resto = aux;
        if (resto == 1) {
            printf("N -> ");
        } else if (resto == 2) {
            printf("NE -> ");
        } else if (resto == 3) {
            printf("E -> ");
        } else if (resto == 4) {
            printf("SE -> ");
        } else if (resto == 5) {
            printf("S -> ");
        } else if (resto == 6) {
            printf("SO -> ");
        } else if (resto == 7) {
            printf("O -> ");
        } else if (resto == 8) {
            printf("E -> ");
        }
    }
}

/*------------------------------------------ MANIPULACAO STRUCTS BIN (R.13) ------------------------------------------*/

/**
 * @brief guarda os campos da lista ligada de PALAVRAS (DICIONARIO) num ficheiro .dat (binario)
 * @param dic
 */
void guardar_struct_dic_bin(DICIONARIO dic) {
    char path[] = "C:\\Users\\swepp\\CLionProjects\\project2018\\data\\dic.dat";
    FILE *fp = NULL;
    int lenght = 0;
    PALAVRA *paux = NULL;
    fp = fopen(path, "wb");
    if (fp == NULL) {
        printf("Erro ao abrir o ficheiro!\n");
        return;
    }
    fwrite(&(dic.nwords), sizeof(int), 1, fp);

    paux = dic.pfirst;
    for (int i = 0; i < dic.nwords; i++) {
        lenght = strlen(paux->word) + 1;
        fwrite(&lenght, sizeof(lenght), 1, fp);
        fwrite(paux->word, 1, (size_t) lenght, fp);
        fwrite(&(paux->size), sizeof(int), 1, fp);
        paux = paux->pnext;
    }
    fclose(fp);
}

/**
 * @brief Lê campos do ficheiro .dat (binario)
 * @param dic
 */
void ler_struct_dic_bin(DICIONARIO *dic) {
    char path[] = "C:\\Users\\swepp\\CLionProjects\\project2018\\data\\dic.dat";
    FILE *fp;
    int len = 0, size = 0, nwords = 0;
    char word[100];
    fp = fopen(path, "rb");

    if (fp != NULL) {
        fread(&nwords, sizeof(int), 1, fp);

        for (int i = 0; i < nwords; i++) {
            fread(&len, sizeof(len), 1, fp);
            fread(word, 1, (size_t) len, fp);
            fread(&size, sizeof(int), 1, fp);
            insert_words_tail(dic, word, size);
        }
        fclose(fp);
    } else
        printf("Erro ao abrir o ficheiro\n");
}

/**
 * @brief preenche a lista ligada de PALAVRAS (DICIONARIO) com uma palavra com 1 size à tail
 * @param dic
 * @param word
 * @param size
 */
void insert_words_tail(DICIONARIO *dic, char *word, int size) {
    PALAVRA *paux = NULL;
    PALAVRA *pnew = malloc(sizeof(PALAVRA));
    pnew->word = create_copy_dyn_string_f2(word);
    pnew->size = size;
    pnew->pnext = NULL;

    if (dic->pfirst == NULL) {
        dic->pfirst = pnew;
        dic->nwords++;
    } else {
        dic->nwords++;
        paux = dic->pfirst;
        while (paux->pnext != NULL) {
            paux = paux->pnext;
        }
        paux->pnext = pnew;
    }
}

/*------------------------------------------ FUNCOES INICIA ESTRUTURA NULO -------------------------------------------*/

/**
 * @brief inicia todos os campos da estrutura LETRA a nulo
 * @param letra
 */
void iniciar_null(LETRA *letra) {
    letra->letra = '\0';
    letra->col = 0;
    letra->line = 0;
    letra->N = NULL;
    letra->NE = NULL;
    letra->E = NULL;
    letra->SE = NULL;
    letra->S = NULL;
    letra->SO = NULL;
    letra->O = NULL;
    letra->NO = NULL;
    letra->p_sol_first = NULL;
}

/**
 * @brief inicia todos os campos da estrutura palavra a nulo
 * @param p
 */
void iniciar_palavra_null(PALAVRA *p) {
    p->pnext = NULL;
    p->size = 0;
    p->word = NULL;
}

/**
 * @brief funcao que inicia todos os campos da estrutura caminho a nulo
 * @param c
 */
void iniciar_caminho_null(CAMINHO *c) {
    c->pnext = NULL;
    c->direcoes = 0;
    c->palavra = NULL;
    c->x_final = 0;
    c->x_inicial = 0;
    c->y_final = 0;
    c->y_inicial = 0;
    c->check = 0;
}

