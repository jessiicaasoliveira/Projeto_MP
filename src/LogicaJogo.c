#include "WinManager.h"

/** Janela do jogo*/
WINDOW* gameWin;

/** Janela dos status*/
WINDOW* statusWin;

/** Flag para identificar se o jogo está pausado ou rodando*/
int gameState;

/**
 **************************************************************************
 * @brief Função: Inicia e determina o que acontece no jogo
 *
 * Descrição:
 * A Função é responsável por alocar tudo que o jogo vai usar, atualizar a tela, verificar se o jogo está em Play ou em Pause. É onde o loop do jogo acontece. Quando a vida da base de um dos jogadores se torna 0, a função encerra o jogo e finaliza tudo.
 *
 * Parâmetros:
 * @param sem parâmetros
 *
 * Valor retornado:
 * @return função void - a função não retorna nada
 *
 * Assertiva de entrada:
 * Sem parâmetros
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void startNewGame()
{
    allocGame();
    refreshGame();
    gameState = GAME_STATE_PLAY;

    while(Base_p.hp > 0 && Base_e.hp > 0)
    {
        switch(gameState)
        {

        case GAME_STATE_PLAY:

            onGameRoutine();
            break;

        case GAME_STATE_PAUSE:

            pauseGameRoutine();
            break;
        }
    }

    gameEnd(&Base_p, &Base_e);

   destroyGame();
}

/**
 **************************************************************************
 * @brief Função: Verificar Status das Estruturas e tropas do Player
 *
 * Descrição:
 * A Função chama as funções para verificar se há batalhas entre tropas, se alguma tropa está atacando algum prédio ou base inimiga, qual a vida dos prédios do player e a quantidade de tropas que o player possui.
 *
 * Parâmetros:
 * @param sem parâmetros
 *
 * Valor retornado:
 * @return função void - A função não retorna nada
 *
 * Assertiva de entrada:
 * Sem parâmetros
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void playerCheckers()
{
    battleChecker(&T1_p, &T1_e, &T2_e, &T3_e);
    battleChecker(&T2_p, &T1_e, &T2_e, &T3_e);
    battleChecker(&T3_p, &T1_e, &T2_e, &T3_e);
    destroyBuildChecker(&T1_p, &Base_e, &B1_e, &B2_e, &B3_e);
    destroyBuildChecker(&T2_p, &Base_e, &B1_e, &B2_e, &B3_e);
    destroyBuildChecker(&T3_p, &Base_e, &B1_e, &B2_e, &B3_e);
    buildHPChecker(&B1_p, &B2_p, &B3_p, map1);
    troopAmountChecker(&T1_p, &T2_p, &T3_p, map1);
}