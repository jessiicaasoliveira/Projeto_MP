#include "PlayerFunc.h"

/**struct base*/
Base Base_p;
/**struct prédio 1*/
Build B1_p;
/**struct prédio 2*/
Build B2_p;
/**struct prédio 3*/
Build B3_p;
/**struct tropa 1*/
Troop T1_p;
/**struct tropa 2*/
Troop T2_p;
/**struct tropa 3*/
Troop T3_p;
/**variável que mostra qual tropa está selecionada*/
int troopSel = 45;

/**
 **************************************************************************
 * @brief Função: Setar Atributos da Base
 *
 * Descrição:
 * A Função recebe uma struct da base, sua posição, comprimento e largura.Então esses valores são setados nessa struct e é setado também a quantidade de recursos 1 e 2, a defesa e a vida dessa base.
 *
 * Parâmetros:
 * @param Base* bc - uma struct para a base
 * @param int x - coordenada x da base
 * @param int y - coordenada y da base
 * @param int height - altura da base
 * @param int width - largura da base
 *
 * Valor retornado:
 * @return Base* bc - struct com os valores modificados e iniciados para o começo do jogo
 *
 * Assertiva de entrada:
 * Base* bc != NULL
 * int x >= 0
 * int y >= 0
 * int height > 0
 * int width > 0
 *
 * Assertiva de saída:
 * Base* bc != NULL
 ***************************************************************************/

Base* setBaseAtt(Base* bc, int x, int y, int height, int width) {
    FILE* fp;

    /* Variáveis de posição e tamanho da base */
    bc->x = x;
    bc->y = y;
    bc->height = height;
    bc->width = width;

    /* Variáveis de jogo da base */
    bc->r1Amount = 100;
    bc->r2Amount = 100;
    bc->defense = 1000;
    bc->hp = 5000;

    /*Assertiva de saída*/
    if (bc == NULL) {
        fp = fopen("Relatório_Erros.txt", "a");
        fprintf(fp, "Erro na setBaseAtt (arquivo PlayerFunc.c)\n");
        fclose(fp);
    }
    return bc;
}

/**
 **************************************************************************
 * @brief Função: Setar Atributos dos Prédios
 *
 * Descrição:
 * A Função recebe uma struct de um prédio, sua posição, comprimento, largura e um valor inteiro que define qual o seu tipo.Então esses valores são setados nessa struct e é setado também, dependendo do tipo, a defesa, a velocidade de mineração, o consumo de recursos e a vida.
 *
 * Parâmetros:
 * @param Build* b - uma struct para o prédio
 * @param int x - coordenada x do prédio
 * @param int y - coordenada y do prédio
 * @param int height - altura do prédio
 * @param int width - largura do prédio
 * @param int type - tipo de prédio
 *
 * Valor retornado:
 * @return Build* b - struct com os valores modificados e iniciados para o começo do jogo
 *
 * Assertiva de entrada:
 * Build* b != NULL
 * int x >= 0
 * int y >= 0
 * int height > 0
 * int width > 0
 * int type == 0 || type == 1 || type == 2
 *
 * Assertiva de saída:
 * Build* b != NULL
 ***************************************************************************/
Build* setBuildAtt(Build* b, int x, int y, int height, int width, int type) {
    FILE* fp;
    /* Variáveis de posição e tamanho da base */
    b->x = x;
    b->y = y;
    b->width = height;
    b->height = width;
    /* Variáveis de jogo da base */
    switch (type) { /* Atributos para diferentes tipos*/
        case 0: /* Minerador de recurso 1*/
            b->defense = 500;
            b->mineSpeed = 150;
            b->resourceConsume = 0;
            b->hp = 1000;
            break;
        case 1: /* Minerador de recurso 2*/
            b->defense = 500;
            b->mineSpeed = 120;
            b->resourceConsume = 0;
            b->hp = 1200;
            break;
        case 2: /* Minerador de tropas */
            b->defense = 700;
            b->mineSpeed = 100;
            b->resourceConsume = 100;
            b->hp = 1300;
            break;
    }
    /*Assertiva de saída*/
    if (b == NULL) {
        fp = fopen("Relatório_Erros.txt", "a");
        fprintf(fp, "Erro na setBuildAtt (arquivo PlayerFunc.c)\n");
        fclose(fp);
    }
    return b;
}
/**
**************************************************************************
 * @brief Função: Setar Atributos das Tropas
 *
 * Descrição:
 * A Função recebe uma struct das tropas, a sua posição e um valor inteiro que define qual o seu tipo. Então esses valores,menos o tipo, são setados nessa struct e é setado também, dependendo do seu tipo, quantidade de soldados na tropa, o dano da tropa, a defesa da tropa e a sua vida.
 *
 * Parâmetros:
 * @param Troop* bc - uma struct para a tropa
 * @param int x - coordenada x da tropa
 * @param int y - coordenada y da tropa
 * @param int type - tipo de tropa
 *
 * Valor retornado:
 * @return Troop* t - struct com os valores modificados e iniciados para o começo do jogo
 *
 * Assertiva de entrada:
 * Troop* t != NULL
 * int x >= 0
 * int y >= 0
 * int type == 0 || type == 1 || type == 2
 *
 * Assertiva de saída:
 * Troop* t != NULL
 ***************************************************************************/
Troop* setTroopAtt(Troop* t, int x, int y, int type) {
    FILE* fp;
    /* Variáveis de posição e tamanho da base */
    t->x = x;
    t->y = y;
    switch (type) { /* Atributos para diferentes tipos*/
        case 0: /* Tropa tipo 0*/
            t->amount = 100;
            t->damage = 40;
            t->defense = 30;
            t->hp = 80;
            break;
        case 1: /* Tropa tipo 1*/
            t->amount = 80;
            t->damage = 60;
            t->defense = 40;
            t->hp = 90;
            break;
        case 2: /* Tropa tipo 2 */
            t->amount = 40;
            t->damage = 100;
            t->defense = 70;
            t->hp = 70;
            break;
    }
    /*Assertiva de saída*/
    if (t == NULL) {
        fp = fopen("Relatório_Erros.txt", "a");
        fprintf(fp, "Erro na setBaseAtt (arquivo PlayerFunc.c)\n");
        fclose(fp);
    }
    return t;
}

/**
 **************************************************************************
 * @brief Função: Mover as Tropas
 *
 * Descrição:
 * A Função recebe uma janela (ncurses) e uma matriz do mapa. Então ela verifica as entradas digitadas pelo usuário. No caso, 0, 1 e 2 para selecionar as tropas e/ou as teclas direcionais do teclado para movimentar as tropas. Então a função modifica a localização da tropa.
 *
 * Parâmetros:
 * @param WINDOW* win - uma janela
 * @param char** map - uma matriz que contém o mapa
 *
 * Valor retornado:
 * @return Void - a função não retorna nada
 *
 * Assertiva de entrada:
 * char** map != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void moveTroop(WINDOW* win, char** map) {
    flushinp();
    wtimeout(win, 1000); /* waits 1000 miliseconds = 1 second for user input*/
    switch (wgetch(win)) {
    case KEY_DOWN:
        switch (troopSel) {
        case 49:/*1 na tabela ASCII*/
            if (T1_p.y+1 < map_y && map[T1_p.y+1][T1_p.x] == MAP_TILE && T1_p.amount > 0) {
                map[T1_p.y][T1_p.x] = MAP_TILE;
                map[T1_p.y+1][T1_p.x] = '1';
                T1_p.y++;
            }
            break;
        case 50:/*2 na tabela ASCII*/
            if (T2_p.y+1 < map_y && map[T2_p.y+1][T2_p.x] == MAP_TILE && T2_p.amount > 0) {
                map[T2_p.y][T2_p.x] = MAP_TILE;
                map[T2_p.y+1][T2_p.x] = '2';
                T2_p.y++;
            }
            break;
        case 51:/*3 na tabela ASCII*/
            if (T3_p.y+1 < map_y && map[T3_p.y+1][T3_p.x] == MAP_TILE && T3_p.amount > 0) {
                map[T3_p.y][T3_p.x] = MAP_TILE;
                map[T3_p.y+1][T3_p.x] = '3';
                T3_p.y++;
            }
            break;
        default:
            usleep(REFRESH_TIME);
        }
        break;
    case KEY_UP:
        switch (troopSel) {
           case 49:/*1 na tabela ASCII*/
             if (T1_p.y-1 >= 0 && map[T1_p.y-1][T1_p.x] == MAP_TILE && T1_p.amount > 0) {
                map[T1_p.y][T1_p.x] = MAP_TILE;
                map[T1_p.y-1][T1_p.x] = '1';
                T1_p.y--;
            }
            break;
        case 50:/*2 na tabela ASCII*/
            if (T2_p.y-1 >= 0 && map[T2_p.y-1][T2_p.x] == MAP_TILE && T2_p.amount > 0) {
                map[T2_p.y][T2_p.x] = MAP_TILE;
                map[T2_p.y-1][T2_p.x] = '2';
                T2_p.y--;
            }
            break;
        case 51:/*3 na tabela ASCII*/
            if (T3_p.y-1 >= 0 && map[T3_p.y-1][T3_p.x] == MAP_TILE && T3_p.amount > 0) {
                map[T3_p.y][T3_p.x] = MAP_TILE;
                map[T3_p.y-1][T3_p.x] = '3';
                T3_p.y--;
            }
            break;
        default:
            usleep(REFRESH_TIME);
        }
        break;
    case KEY_LEFT:
        switch (troopSel) {
           case 49:/*1 na tabela ASCII*/
             if (T1_p.x-1 >= 0 && map[T1_p.y][T1_p.x-1] == MAP_TILE && T1_p.amount > 0) {
                map[T1_p.y][T1_p.x] = MAP_TILE;
                map[T1_p.y][T1_p.x-1] = '1';
                T1_p.x--;
            }
            break;
        case 50:/*2 na tabela ASCII*/
            if (T2_p.x-1 >= 0 && map[T2_p.y][T2_p.x-1] == MAP_TILE && T2_p.amount > 0) {
                map[T2_p.y][T2_p.x] = MAP_TILE;
                map[T2_p.y][T2_p.x-1] = '2';
                T2_p.x--;
            }
            break;
        case 51:/*3 na tabela ASCII*/
            if (T3_p.x-1 >= 0 && map[T3_p.y][T3_p.x-1] == MAP_TILE && T3_p.amount > 0) {
                map[T3_p.y][T3_p.x] = MAP_TILE;
                map[T3_p.y][T3_p.x-1] = '3';
                T3_p.x--;
            }
            break;
        default:
            usleep(REFRESH_TIME);
        }
        break;
    case KEY_RIGHT:
        switch (troopSel) {
           case 49:/*1 na tabela ASCII*/
             if (T1_p.x+1 >= 0 && map[T1_p.y][T1_p.x+1] == MAP_TILE && T1_p.amount > 0) {
                map[T1_p.y][T1_p.x] = MAP_TILE;
                map[T1_p.y][T1_p.x+1] = '1';
                T1_p.x++;
            }
            break;
        case 50:/*2 na tabela ASCII*/
            if (T2_p.x+1 >= 0 && map[T2_p.y][T2_p.x+1] == MAP_TILE && T2_p.amount > 0) {
                map[T2_p.y][T2_p.x] = MAP_TILE;
                map[T2_p.y][T2_p.x+1] = '2';
                T2_p.x++;
            }
            break;
        case 51:/*3 na tabela ASCII*/
            if (T3_p.x+1 >= 0 && map[T3_p.y][T3_p.x+1] == MAP_TILE && T3_p.amount > 0) {
                map[T3_p.y][T3_p.x] = MAP_TILE;
                map[T3_p.y][T3_p.x+1] = '3';
                T3_p.x++;
            }
            break;
        default:
            usleep(REFRESH_TIME);
        }
        break;
    case 49:/*1 na tabela ASCII*/
        troopSel = 49;
        break;
    case 50:/*2 na tabela ASCII*/
        troopSel = 50;
        break;
    case 51:/*3 na tabela ASCII*/
        troopSel = 51;
        break;
    case 27: /* Escape na tabela ASCII */
        gameState = GAME_STATE_PAUSE;
        break;
    default:
        troopSel = 45;/* - na tabela ASCII*/
    }
}
