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

/**
**************************************************************************
 * @brief Função: Controlar a Mineração de Recursos
 *
 * Descrição:
 * A Função recebe as structs da base e de 2 prédios responsáveis pela mineração de recursos. Para controlar a frequencia de mineração, é verificado randomicamente um valor inteiro, e se ele for maior que 60 e a vida do prédio for superior a 0 é aumentado a quantidade de recursos minerados de acordo com a velocidade de mineração de cada tipo de prédio.
 *
 * Parâmetros:
 * @param Base* b - struct da base
 * @param Build* b1 - struct do prédio do tipo 1
 * @param Build* b2 - struct do prédio do tipo 2
 *
 * Valor retornado:
 * @return Void. A função não retorna nada
 *
 * Assertiva de entrada:
 * Base* b != NULL
 * Build* b1 != NULL
 * Build* b2 != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void resourceController(Base* b, Build* b1, Build* b2) {
    if ((rand_r()%101) > RESOURCE_RAND) {
        if (b1->hp > 0)
            b->r1Amount += (b1->mineSpeed * R1_RATE);
        if (b2->hp > 0)
            b->r2Amount += (b2->mineSpeed * R2_RATE);
    }
}
/**
 **************************************************************************
 * @brief Função: Controlar a Criação de Tropas
 *
 * Descrição:
 * A Função recebe as structs da base, das tropas e do prédio responsável pela criação de tropas. Então ela verifica se a tropa está do lado do prédio que gera tropa, e se há recursos para gerar mais tropas. Então essa tropa tem a quantidade aumentada.
 *
 * Parâmetros:
 * @param Troop* t1 - struct da tropa do tipo 1
 * @param Troop* t2 - struct da tropa do tipo 2
 * @param Troop* t3 - struct da tropa do tipo 3
 * @param Build* b3 - struct do prédio do tipo 3
 * @param Base* b - struct da base
 *
 * Valor retornado:
 * @return Void. A função não retorna nada
 *
 * Assertiva de entrada:
 * Troop* t1 != NULL
 * Troop* t2 != NULL
 * Troop* t3 != NULL
 * Build* b3 != NULL
 * Base* b != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void troopController(Troop* t1, Troop* t2, Troop* t3, Build* b3, Base* b) {
    if (troopChecker(t1, 0) && b->r1Amount > 0) {
        t1->amount += (b3->mineSpeed * T1_RATE);
        b->r1Amount += (-b3->resourceConsume * R1_COST);
        if (b->r1Amount <=0)
            b->r1Amount = 0;
    }
    if (troopChecker(t2, 0) && b->r1Amount > 0) {
        t2->amount += (b3->mineSpeed * T2_RATE);
        b->r1Amount += (-b3->resourceConsume * R1_COST);
        if (b->r1Amount <=0)
            b->r1Amount = 0;
    }
    if (troopChecker(t3, 0) && b->r2Amount > 0) {
        t3->amount += (b3->mineSpeed * T3_RATE);
        b->r2Amount += (-b3->resourceConsume * R2_COST);
        if (b->r2Amount <=0)
            b->r2Amount = 0;
    }
}

/**
 **************************************************************************
 * @brief Função: Verificar as Redondezas da Tropa
 *
 * Descrição:
 * A Função recebe a struct de uma tropa e verifica as redondezas dessa tropa, e retorna um valor de acordo com o que está do lado dessa tropa.
 *
 * Parâmetros:
 * @param Troop* t - struct da tropa
 * @param int mode - flag para identificar se a função foi chamada para checar se a tropa está perto do prédio responsável por aumentar tropas (0) ou se foi chamada para checar se há tropas inimigas por perto (1)
 *
 * Valor retornado:
 * @return 0 - caso a tropa não esteja perto de nada
 * @return 1 - caso a mode = 0 e a tropa esteja perto do prédio responsável por gerar tropas
 * @return 7 - caso a tropa esteja perto da tropa inimiga '7'
 * @return 8 - caso a tropa esteja perto da tropa inimiga '8'
 * @return 9 - caso a tropa esteja perto da tropa inimiga '9'
 * @return 10 - caso a tropa esteja perto do base 'Y'
 * @return 11 - caso a tropa esteja perto do prédio 'D'
 * @return 12 - caso a tropa esteja perto do prédio 'F'
 * @return 13 - caso a tropa esteja perto do prédio 'E'
 *
 * Assertiva de entrada:
 * Troop* t != NULL
 * int mode == 0 || mode == 1
 *
 * Assertiva de saída:
 * A função retorna valores fixos.
 ***************************************************************************/
int troopChecker(Troop* t, int mode) {
/* variável mode para checar redondezas -> batalha ou aumento de tropa */
    switch (mode) {
    case 0: /* Caso para gerar tropa */
        if (t->x+1 < map_x && map1[t->y][t->x+1] == 'C')
            return 1;
        else if (t->x-1 >= 0 && map1[t->y][t->x-1] == 'C')
            return 1;
        else if (t->y-1 >= 0 && map1[t->y-1][t->x] == 'C')
            return 1;
        else if (t->y+1 < map_y && map1[t->y+1][t->x] == 'C')
            return 1;
        break;
    case 1: /* Caso de batalha */
        if (t->x+1 < map_x) {
            switch (map1[t->y][t->x+1]) {
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            case 'Y':
                return 10;
            case 'D':
                return 11;
            case 'F':
                return 12;
            case 'E':
                return 13;
            }
        }
        if (t->x-1 >= 0) {
            switch (map1[t->y][t->x-1]) {
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            case 'Y':
                return 10;
            case 'D':
                return 11;
            case 'F':
                return 12;
            case 'E':
                return 13;
            }
        }
        if (t->y-1 >= 0) {
            switch (map1[t->y-1][t->x]) {
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            case 'Y':
                return 10;
            case 'D':
                return 11;
            case 'F':
                return 12;
            case 'E':
                return 13;
            }
        }
        if (t->y+1 < map_y) {
            switch (map1[t->y+1][t->x]) {
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            case 'Y':
                return 10;
            case 'D':
                return 11;
            case 'F':
                return 12;
            case 'E':
                return 13;
            }
        }
        break;
    }
    map1[T1_p.y][T1_p.x] = '1';
    map1[T2_p.y][T2_p.x] = '2';
    map1[T3_p.y][T3_p.x] = '3';
    return 0;
}

/**
 **************************************************************************
 * @brief Função: Verificar se um Prédio foi Derrubado
 *
 * Descrição:
 * A Função recebe as structs dos prédios e a matriz do mapa. Ela verifica se a vida dos prédios é 0. Se for ela retira o prédio do mapa e deixa o hp da base como -1.
 *
 * Parâmetros:
 * @param Build* b1 - struct do prédio do tipo 1
 * @param Build* b2 - struct do prédio do tipo 2
 * @param Build* b3 - struct do prédio do tipo 3
 * @param char** map - matriz do mapa do jogo
 *
 * Valor retornado:
 * @return Void. A função não retorna nada
 *
 * Assertiva de entrada:
 * Build* b1 != NULL
 * Build* b2 != NULL
 * Build* b3 != NULL
 * Build* b3 != NULL
 * char** map != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void buildHPChecker(Build* b1, Build* b2, Build* b3, char** map) {
    int i, j;
    if (b1->hp == 0) {
        for (i = b1->y; i <= (b1->height + b1->y); i++)
            for (j = b1->x; j <= (b1->width + b1->x); j++)
                map[i][j] = MAP_TILE;
        b1->hp = -1;
    }
    if (b2->hp == 0) {
        for (i = b2->y; i <= (b2->height + b2->y); i++)
            for (j = b2->x; j <= (b2->width + b2->x); j++)
                map[i][j] = MAP_TILE;
        b2->hp = -1;
    }
    if (b3->hp == 0) {
        for (i = b3->y; i <= (b3->height + b3->y); i++)
            for (j = b3->x; j <= (b3->width + b3->x); j++)
                map[i][j] = MAP_TILE;
        b3->hp = -1;
    }
}
/**
 **************************************************************************
 * @brief Função: Verificar se uma Tropa foi eliminada
 *
 * Descrição:
 * A Função recebe as structs das tropas e a matriz do mapa. Ela verifica se a quantidade de tropas é igual a zero e se for ela retira a tropa do mapa.
 *
 * Parâmetros:
 * @param Troop* t1 - struct da tropa do tipo 1
 * @param Troop* t2 - struct da tropa do tipo 2
 * @param Troop* t3 - struct da tropa do tipo 3
 * @param char** map - matriz do mapa
 *
 * Valor retornado:
 * @return Void. A função não retorna nada
 *
 * Assertiva de entrada:
 * Troop* t1 != NULL
 * Troop* t2 != NULL
 * Troop* t3 != NULL
 * char** map != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void troopAmountChecker(Troop* t1, Troop* t2, Troop* t3, char** map) {
    if (t1->amount <= 0) {
        map[t1->y][t1->x] = MAP_TILE;
        t1->amount = 0;
        t1->y = t1->x = 0;
    }
    if (t2->amount <= 0) {
        map[t2->y][t2->x] = MAP_TILE;
        t2->amount = 0;
        t2->y = t2->x = 0;
    }
    if (t3->amount <= 0) {
        map[t3->y][t3->x] = MAP_TILE;
        t3->amount = 0;
        t3->y = t3->x = 0;
    }
}
