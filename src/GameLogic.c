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

/**
 **************************************************************************
 * @brief Função: Controlar as Opções no Menu de Pause
 *
 * Descrição:
 * A Função volta ao jogo, salva o jogo ou saí do jogo de acordo com a opção selecionada no menu de Pause.
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
void pauseGameRoutine()
{
    switch(pauseGameMenu())
    {
        case 0:

            gameState = GAME_STATE_PLAY;
            break;

        case 1:
            saveGame();
            gameState = GAME_STATE_PLAY;
            break;

        case 2:

            Base_p.hp = -1;
            Base_e.hp = -1;
            break;
    }
}

/**
 **************************************************************************
 * @brief Função: Printar na Tela o Jogo
 *
 * Descrição:
 * A Função imprime os status do player, do PC e o mapa do jogo.
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
void printGame()
{
    printPlayerStatus(statusWin, &Base_p, &B1_p, &B3_p, &B2_p, &T1_p, &T2_p, &T3_p);
    printEnemyStatus(statusWin, &Base_e, &B1_e, &B3_e, &B2_e, &T1_e, &T2_e, &T3_e);
    printMap(gameWin, map1);
}

/**
 **************************************************************************
 * @brief Função: Iniciar e Alocar Pré-Requisitos para o Jogo
 *
 * Descrição:
 * A Função aloca e cria as janelas do jogo e do status, aloca o mapa do jogo e o inicializa.
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
void allocGame()
{
    /* Alocação de windows e mapa */
    gameWin = gameWindow(termLines, termCols);
    statusWin = createWin(termLines-(termLines-6), termCols, 0, 0);
    keypad(statusWin, FALSE);
    box(statusWin, 0, 0);
    map1 = allocMap(map1, termLines, termCols);
    InitializePathfinder();
    setMap(map1,save);
    srand(time(NULL));
}

/**
 **************************************************************************
 * @brief Função: Desaloca e Finaliza as Janelas
 *
 * Descrição:
 * A Função desaloca a janela utilizada para o jogo e para o status e desaloca o mapa do jogo. Então limpa o terminal e atualiza a tela.
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
void destroyGame()
{
     /* Desalocando windows e mapa */
    destroyWin(&gameWin);
    destroyWin(&statusWin);
    map1 = deallocMap(map1);
    EndPathfinder();
    /* limpando terminal */
    erase();
    refresh();
}

/**
 **************************************************************************
 * @brief Função: Salvar o Jogo
 *
 * Descrição:
 * A Função cria um arquivo binário e salva todos os dados da base, dos prédios e das tropas do player e do PC nele.
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
void saveGame(){

    FILE* fp;

    fp = fopen("save.bin", "wb");

    if (fp == NULL) {
        fclose(fp);
        fp = fopen("Relatório_Erros.txt", "a");
        fprintf(fp, "Erro na saveGame (arquivo LogicaJogo.c)\n");
        fclose(fp);
    }

    /*Dados do player*/
    fwrite(&Base_p, sizeof(Base),1,fp);
    fwrite(&B1_p, sizeof(Build),1,fp);
    fwrite(&B2_p, sizeof(Build),1,fp);
    fwrite(&B3_p, sizeof(Build),1,fp);
    fwrite(&T1_p, sizeof(Troop),1,fp);
    fwrite(&T2_p, sizeof(Troop),1,fp);
    fwrite(&T3_p, sizeof(Troop),1,fp);

    /*Dados do PC*/
    fwrite(&Base_e, sizeof(Base),1,fp);
    fwrite(&B1_e, sizeof(Build),1,fp);
    fwrite(&B2_e, sizeof(Build),1,fp);
    fwrite(&B3_e, sizeof(Build),1,fp);
    fwrite(&T1_e, sizeof(Troop),1,fp);
    fwrite(&T2_e, sizeof(Troop),1,fp);
    fwrite(&T3_e, sizeof(Troop),1,fp);

    fclose(fp);

}

/**
 **************************************************************************
 * @brief Função: Carregar um Jogo Salvo
 *
 * Descrição:
 * A Função abre o arquivo de save e lê todos os dados da base, prédios e tropas do player e do PC. Caso não exista um save, é mostrado uma mensagem na tela.
 *
 * Parâmetros:
 * @param sem parâmetros
 *
 * Valor retornado:
 * @return 0 - se não existir um arquivo de save válido
 * @return 1 - se o load ocorrer sem problemas
 *
 * Assertiva de entrada:
 * Sem parâmetros
 *
 * Assertiva de saída:
 * A função retorna valores fixos.
 ***************************************************************************/
int loadGame(){

    FILE* fp;

    fp = fopen("save.bin","rb");

    if(fp == NULL)
    {
        mvprintw(LINES - 6, 0, "Nao ha jogo salvo!");
        refresh();

        return 0;
    }

    else
    {
        /*Dados do playes*/
        fread(&Base_p, sizeof(Base),1,fp);
        fread(&B1_p, sizeof(Build),1,fp);
        fread(&B2_p, sizeof(Build),1,fp);
        fread(&B3_p, sizeof(Build),1,fp);
        fread(&T1_p, sizeof(Troop),1,fp);
        fread(&T2_p, sizeof(Troop),1,fp);
        fread(&T3_p, sizeof(Troop),1,fp);

            /*Dados do PC*/
        fread(&Base_e, sizeof(Base),1,fp);
        fread(&B1_e, sizeof(Build),1,fp);
        fread(&B2_e, sizeof(Build),1,fp);
        fread(&B3_e, sizeof(Build),1,fp);
        fread(&T1_e, sizeof(Troop),1,fp);
        fread(&T2_e, sizeof(Troop),1,fp);
        fread(&T3_e, sizeof(Troop),1,fp);

        fclose(fp);

        return 1;
    }
    return 0;
}
