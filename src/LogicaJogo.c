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