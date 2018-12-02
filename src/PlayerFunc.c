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

