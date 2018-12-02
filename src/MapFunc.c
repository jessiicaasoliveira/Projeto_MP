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

/** 
**************************************************************************
 * @brief Função: Colocar no Mapa um prédio
 *
 * Descrição:
 * A Função recebe uma matriz (mapa do jogo) do tipo char, uma struct de uma prédio, a posição que esse prédio vai ficar, a altura e a largura desse prédio, uma flag para identificar qual o tipo desse prédio, uma flag para identificar se o prédio é do player ou do PC e uma flag para identificar se o prédio é de um jogo novo ou de um save. O prédio é setado e escrito no mapa na posição que foi mandado, que, dependendo das flags, fica como:
    'X' - prédio de type 0 do player
    'Y' - prédio do type 1 do player
    'Z' - prédio do type 2 do player
    'L' - prédio do type 0 do PC
    'M' - prédio do type 1 do PC
    'N' - prédio do type 2 do PC
 *
 * Parâmetros:
 * @param char** map - matriz (mapa) do tipo char
 * @param Build* b - uma struct para o prédio
 * @param int x - coordenada x do prédio
 * @param int y - coordenada y do prédio
 * @param int width - largura do prédio
 * @param int height - altura do prédio
 * @param int type - flag para identificar o tipo do prédio
 * @param int who - flag para identificar se o prédio é do Player (0) ou do PC (1)
 * @param int save - flag para identificar se o prédio está sendo carregado de um jogo novo (0) ou de um save (1)
 *
 * Valor retornado:
 * @return função void. Os valores são mudados por referência
 *
 * Assertiva de entrada:
 * char** map != NULL
 * Build* b != NULL
 * int x >= 0
 * int y >= 0
 * int width > 0
 * int height > 0
 * int type == 0 || type == 1 || type == 2
 * int who == 0 || who == 1
 * int save == 0 || save == 1
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/

void setBuildOnMap(char** map, Build* b, int x, int y, int width, int height, int type, int who, int save) {
    int i, j;

    if (!save) {
        b = setBuildAtt(b, x, y, height, width, type);
    }

    for (i = b->y; i <= (b->height + b->y); i++)
        for (j = b->x; j <= (b->width+b->x); j++) {
            switch (who) {
            case 0:
                    switch (type) {
                    case 0: map[i][j] = 'A';
                        break;

                    case 1: map[i][j] = 'C';
                        break;

                    case 2: map[i][j] = 'B';
                        break;
                    }
                break;

            case 1:
                    switch (type) {
                    case 0: map[i][j] = 'D';
                        break;

                    case 1: map[i][j] = 'F';
                        break;

                    case 2: map[i][j] = 'E';
                        break;
                    }
                break;
            }
        }
}

/**
**************************************************************************
 * @brief Função: Colocar no Mapa a Tropa
 *
 * Descrição:
 * A Função recebe uma matriz (mapa do jogo) do tipo char, uma struct de uma tropa, a posição que essa tropa vai ficar, uma flag para identificar qual o tipo de tropa, uma flag para identificar se a tropa é do player ou do PC e uma flag para identificar se a tropa é de um jogo novo ou de um save. A tropa é setada e escrita no mapa na posição mandada, que, dependendo das flags, fica como:
    '1' - tropa de type 0 do player
    '2' - tropa de type 1 do player
    '3' - tropa de type 2 do player
    '7' - tropa de type 0 do PC
    '8' - tropa de type 1 do PC
    '9' - tropa de type 2 do PC
 *
 * Parâmetros:
 * @param char** map - matriz (mapa) do tipo char
 * @param Troop* t - uma struct para a troop
 * @param int x - coordenada x da base
 * @param int y - coordenada y da base
 * @param int type - flag para identificar o tipo de tropa
 * @param int who - flag para identificar se a tropa é do Player (0) ou do PC (1)
 * @param int save - flag para identificar se a tropa está sendo carregada de um jogo novo (0) ou de um save (1)
 *
 * Valor retornado:
 * @return função void. Os valores são mudados por referência
 *
 * Assertiva de entrada:
 * char** map != NULL
 * Troop* t != NULL
 * int x >= 0
 * int y >= 0
 * int type == 0 || type == 1 || type == 2
 * int who == 0 || who == 1
 * int save == 0 || save == 1
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/

void setTroopOnMap(char** map, Troop* t, int x, int y, int type, int who, int save) {
    if (!save) {
        t = setTroopAtt(t, x, y, type);

        switch (who) {
            case 0:

                switch (type) {
                case 0:
                    map[y][x] = '1';
                    break;

                case 1:
                    map[y][x] = '2';
                    break;

                case 2:
                    map[y][x] = '3';
                    break;
            }
                break;

            case 1:

                switch (type) {
                case 0:
                    map[y][x] = '7';
                    break;

                case 1:
                    map[y][x] = '8';
                    break;

                case 2:
                    map[y][x] = '9';
                    break;
            }

                break;
        }
    } else {
        switch (who) {
            case 0:

                switch (type) {
                case 0:
                    map[t->y][t->x] = '1';
                    break;

                case 1:
                    map[t->y][t->x] = '2';
                    break;

                case 2:
                    map[t->y][t->x] = '3';
                    break;
            }
                break;

            case 1:

                switch (type) {
                case 0:
                    map[t->y][t->x] = '7';
                    break;

                case 1:
                    map[t->y][t->x] = '8';
                    break;

                case 2:
                    map[t->y][t->x] = '9';
                    break;
            }

                break;
        }
    }
}

/**
 **************************************************************************
 * @brief Função: Setar a Matriz do Mapa
 *
 * Descrição:
 * A Função recebe uma matriz (mapa do jogo) do tipo char e uma flag que identifica se o jogo é novo ou um save, então ela preenche o mapa com '.' .Depois é colocado as bases, prédios e tropas do player e do PC
 *
 * Parâmetros:
 * @param char** map - matriz (mapa) do tipo char
 * @param int save - flag para identificar se o mapa vai ser setado para um jogo novo (0) ou para um save (1)
 *
 * Valor retornado:
 * @return função void. Os valores são mudados por referência
 *
 * Assertiva de entrada:
 * char** map != NULL
 * int save == 0 || save == 1
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void setMap(char** map, int save) {
    int i, j;

    for (i = 0; i < map_y; i++)
        for (j = 0; j < map_x; j++)
            map[i][j] = MAP_TILE;

    setBaseOnMap(map, &Base_p, 0, (map_y/2)-3, 5, 8, 0, save);
    setBuildOnMap(map, &B1_p, 0, (map_y/2)-8, 2, 4, 0, 0, save);
    setBuildOnMap(map, &B2_p, 0, (map_y/2)+5, 2, 4, 1, 0, save);
    setBuildOnMap(map, &B3_p, 11, (map_y/2)-1, 2, 4, 2, 0, save);
    setTroopOnMap(map, &T1_p, 17, (map_y/2)-2, 0, 0, save);
    setTroopOnMap(map, &T2_p, 17, (map_y/2), 1, 0, save);
    setTroopOnMap(map, &T3_p, 17, (map_y/2)+2, 2, 0, save);

    setBaseOnMap(map, &Base_e, map_x-9, (map_y/2)-3, 5, 8, 1, save);
    setBuildOnMap(map, &B1_e, map_x-5, (map_y/2)-8, 2, 4, 0, 1, save);
    setBuildOnMap(map, &B2_e, map_x-5, (map_y/2)+5, 2, 4, 1, 1, save);
    setBuildOnMap(map, &B3_e, map_x-16, (map_y/2)-1, 2, 4, 2, 1, save);
    setTroopOnMap(map, &T1_e, map_x-18, (map_y/2)-2, 0, 1, save);
    setTroopOnMap(map, &T2_e, map_x-18, (map_y/2), 1, 1, save);
    setTroopOnMap(map, &T3_e, map_x-18, (map_y/2)+2, 2, 1, save);
}

/**
 **************************************************************************
 * @brief Função: Imprimir o Mapa na Window
 *
 * Descrição:
 * A Função recebe uma matriz (mapa do jogo) do tipo char e uma janela (ncurses). Então ela printa na tela o mapa, com as bases, prédios e tropas. Ela também é responsável pelas cores printadas.
 *
 * Parâmetros:
 * @param char** map - matriz (mapa) do tipo char
 * @param WINDOW* win - uma janela
 *
 * Valor retornado:
 * @return função void. É uma função de atualização de tela
 *
 * Assertiva de entrada:
 * char** map != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void printMap(WINDOW* win, char** map) {
    int i, j;

    for (i = 0; i < map_y; i++) {
        for (j = 0; j < map_x; j++) {
            switch (map[i][j]) {
            case 'X':
                mvwaddch(win, i+2, j+1, map[i][j] | COLOR_PAIR(6) | A_STANDOUT);
                break;

            case 'A':
            case 'C':
            case 'B':
                mvwaddch(win, i+2, j+1, map[i][j] | COLOR_PAIR(5) | A_STANDOUT);
                break;

            case 'D':
            case 'F':
            case 'E':
                mvwaddch(win, i+2, j+1, map[i][j] | COLOR_PAIR(7) | A_STANDOUT);
                break;

            case 'Y':
                mvwaddch(win, i+2, j+1, map[i][j] | COLOR_PAIR(8) | A_STANDOUT);
                break;

            case '1':
            case '2':
            case '3':
                mvwaddch(win, i+2, j+1, map[i][j] | COLOR_PAIR(9) | A_STANDOUT);
                break;

            case '7':
            case '8':
            case '9':
                mvwaddch(win, i+2, j+1, map[i][j] | COLOR_PAIR(10) | A_STANDOUT);
                break;

            default:
                mvwaddch(win, i+2, j+1, map[i][j]);
            }
        }
        wprintw(win, "\n");
    }
    wrefresh(win);
}
