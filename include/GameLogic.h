#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <menu.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

#define MAP_TILE '-'
#define GAME_STATE_PLAY '1' //ESTADO DE JOGO: JOGANDO
#define GAME_STATE_PAUSE '2' //ESTADO DE JOGO: PAUSADO
#define REFRESH_TIME 65000
#define RESOURCE_RAND 60
#define R1_RATE 0.08
#define R2_RATE 0.017
#define T1_RATE 0.02
#define T2_RATE 0.01
#define T3_RATE 0.01
#define R1_COST 0.08
#define R2_COST 0.12
#define NEW_GAME 0
#define LOAD_GAME 1

extern int map_x,/*colunas do mapa*/
            map_y,/*linhas do mapa*/
            troopSel,/*tropa selecionada*/
            gameState;/*flag se o jogo está pausado ou rodando*/
extern WINDOW* pauseWin;/*janela de pause*/
extern char** map1;/*matriz do mapa*/

/*Variável para identificar o save*/
int save;

/*Funções*/
void startNewGame();
void refreshGame();
void allocGame();
void destroyGame();
void printGame();
int getTroopSel(int troop);
void onGameRoutine();
void pauseGameRoutine();
void saveGame();
int loadGame();
void playerCheckers();
void playerControllers();
void enemyCheckers();
void enemyControllers();
void gameControllers();
void gameCheckers();
