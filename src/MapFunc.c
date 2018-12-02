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

/**
 **************************************************************************
 * @brief Função: Desalocar o Mapa do Jogo
 *
 * Descrição:
 * A Função recebe uma matriz (mapa do jogo) do tipo char e a desaloca. Então retorna a matriz desalocada.
 *
 * Parâmetros:
 * @param char** map - matriz do tipo char que vai ser desalocada
 *
 * Valor retornado:
 * @return char** map - matriz desalocada
 *
 * Assertiva de entrada:
 * char** map == NULL
 *
 * Assertiva de saída:
 * char** map == NULL
***************************************************************************/

char** deallocMap(char** map) {
    FILE* fp;
    int i;

    for (i = 0; i < map_y; i++) {
        free(map[i]);
    }
    free(map);
    map = NULL;

    /*Assertiva de saída*/
    if (map != NULL) {
        fp = fopen("Relatório_Erros.txt", "a");
        fprintf(fp, "Erro na liberação do mapa na deallocMap (arquivo MapFunc.c)\n");
        fclose(fp);
    }

    return map;
}

/**
 **************************************************************************
 * @brief Função: Colocar no Mapa a Base
 *
 * Descrição:
 * A Função recebe uma matriz (mapa do jogo) do tipo char, uma struct de uma base, a posição que essa base vai ficar, a altura e a largura dessa base, uma flag para identificar se a base é do player ou do PC e uma flag para identificar se a base é de um jogo novo ou de um save. A base é setada e escrita no mapa como 'B' ou 'C', dependendo da flag, na posição que foi mandada.
 *
 * Parâmetros:
 * @param char** map - matriz (mapa) do tipo char
 * @param Base* bc - uma struct para a base
 * @param int x - coordenada x da base
 * @param int y - coordenada y da base
 * @param int width - largura da base
 * @param int height - altura da base
 * @param int who - flag para identificar se a base é do Player (0) ou do PC (1)
 * @param int save - flag para identificar se a base está sendo carregada de um jogo novo (0) ou de um save (1)
 *
 * Valor retornado:
 * @return função void. Os valores são mudados por referência
 *
 * Assertiva de entrada:
 * char** map != NULL
 * Base* bc != NULL
 * int x >= 0
 * int y >= 0
 * int width > 0
 * int height > 0
 * int who == 0 || who == 1
 * int save == 0 || save == 1
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void setBaseOnMap(char** map, Base* bc, int x, int y, int width, int height, int who, int save) {
    int i, j;

    if (!save) {
        bc = setBaseAtt(bc, x, y, width, height);
    }

    for (i = bc->y; i <= (bc->height + bc->y); i++)
        for (j = bc->x; j <= (bc->width + bc->x); j++) {
            switch (who) {
            case 0: map[i][j] = 'X';
                break;

            case 1: map[i][j] = 'Y';
                break;
            }
        }
}
 