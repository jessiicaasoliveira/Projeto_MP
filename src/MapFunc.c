#include "MapFunc.h"

/**número de colunas da matriz do mapa*/
int map_y;
/**número de linhas da matriz do mapa*/
int map_x;

/**
 **************************************************************************
 * @brief Função: Alocar o Mapa do Jogo
 *
 * Descrição:
 * A Função recebe uma matriz do tipo char, e o numero de linhas e de colunas que essa matriz (mapa do jogo) vai possuir. A matriz é alocada e retornada.
 *
 * Parâmetros:
 * @param char** map - matriz do tipo char que vai ser alocada
 * @param int x - número de linhas da matriz
 * @param int y - número de colunas da matriz
 *
 * Valor retornado:
 * @return char** map - matriz alocada
 *
 * Assertiva de entrada:
 * char** map == NULL
 * int x > 0
 * int y > 0
 *
 * Assertiva de saída:
 * char** map != NULL
 ***************************************************************************/
char** allocMap(char** map, int y, int x) {
    FILE* fp;
    int i;
    map_x = x-3;
    map_y = y-7;

    map = (char**)calloc(y, sizeof(char*));
    /*Assertiva de saída*/
    if (map == NULL) {
        fp = fopen("Relatório_Erros.txt", "a");
        fprintf(fp, "Erro na alocação do mapa na allocMap (arquivo MapFunc.c)\n");
        fclose(fp);
    }

    for (i = 0; i < map_y; i++) {
        map[i] = (char*)calloc(map_x, sizeof(char));
        /*Assertiva de saída*/
        if (map[i] == NULL) {
            fp = fopen("Relatório_Erros.txt", "a");
            fprintf(fp, "Erro na alocação do mapa na allocMap (arquivo MapFunc.c)\n");
            fclose(fp);
        }
    }

    return map;
}
