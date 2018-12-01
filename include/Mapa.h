#include "EnemyFunc.h"

/*matriz do mapa do jogo*/
char** map1;

/*funções*/
void setBuildOnMap(char** map, Build* b, int x, int y, int width, int height, int type, int who, int save);

void setBaseOnMap(char** map, Base* bc, int x, int y, int width, int height, int who, int save);

char** allocMap(char** map, int y, int x);

char** deallocMap(char** map);

void setMap(char** map, int save);

void printMap(WINDOW* win, char** map);

void setTroopOnMap(char** map, Troop* t, int x, int y, int type, int who, int save);