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

/**
 **************************************************************************
 * @brief Função: Chama as Funções Para Atualizar o Jogo
 *
 * Descrição:
 * A Função chama funções de atualizar a tela, mover tropas, verificar recursos e tropas. Ou seja, atualiza tudo dentro do jogo.
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
void onGameRoutine()
{
    refreshGame();
    moveTroop(gameWin, map1);
    enemyMove(&T1_e, &T2_e, &T3_e);
    gameControllers();
    gameCheckers();

}

/**
 **************************************************************************
 * @brief Função: Verificar Status dos Prédios e Tropas do PC
 *
 * Descrição:
 * A Função chama funções para verificar a vida dos prédios e a quantidade de tropas do PC.
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
void enemyCheckers()
{
    enemyHitControl(&T1_e, &Base_p, &B1_p, &B2_p, &B3_p);
    enemyHitControl(&T2_e, &Base_p, &B1_p, &B2_p, &B3_p);
    enemyHitControl(&T3_e, &Base_p, &B1_p, &B2_p, &B3_p);
    buildHPChecker(&B1_e, &B2_e, &B3_e, map1);
    troopAmountChecker(&T1_e, &T2_e, &T3_e, map1);
}

/**
 **************************************************************************
 * @brief Função: Atualizar Status Gerais
 *
 * Descrição:
 * A Função chama funções de checagem de mudança de status em tropas e prédios do player e do PC.
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
void gameCheckers()
{
    playerCheckers();
    enemyCheckers();
}

/**
 **************************************************************************
 * @brief Função: Verificar Criação de Recursos e Tropas do Player
 *
 * Descrição:
 * A Função chama funções para verificar a mineração de recursos e a criação de tropas do player.
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
void playerControllers()
{
    resourceController(&Base_p, &B1_p, &B2_p);
    troopController(&T1_p, &T2_p, &T3_p, &B3_p, &Base_p);
}

/**
 **************************************************************************
 * @brief Função: Verificar Criação de Recursos e Tropas do PC
 *
 * Descrição:
 * A Função chama funções para verificar a mineração de recursos e a criação de tropas do PC.
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
void enemyControllers()
{
    resourceController(&Base_e, &B1_e, &B2_e);
    enemyTroopController(&T1_e, &T2_e, &T3_e, &B3_e, &Base_e);
}

/**
 **************************************************************************
 * @brief Função: Atualizar Recursos e Tropas Gerais
 *
 * Descrição:
 * A Função chama funções de verificação da mineração de recursos e da criação de tropas.
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
void gameControllers()
{
    playerControllers();
    enemyControllers();
}

/**
 **************************************************************************
 * @brief Função: Atualizar a Tela
 *
 * Descrição:
 * A Função atualiza a tela do jogo e dá um refresh.
 *
 * Parâmetros:
 * @param sem parâmetros
 *
 * Valor retornado:
 * @return função void - A função apenas imprime o jogo na tela
 *
 * Assertiva de entrada:
 * Sem parâmetros
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void refreshGame()
{
    /* Atualiza windows */
    printGame();
    refreshWindows(gameWin, statusWin);
}