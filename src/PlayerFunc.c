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
