#include "EnemyFunc.h"

/*matriz do mapa do jogo*/
char** map1;

/*funções*/

char** allocMap(char** map, int y, int x);

char** deallocMap(char** map);

void setBaseOnMap(char** map, Base* bc, int x, int y, int width, int height, int who, int save);

void setBuildOnMap(char** map, Build* b, int x, int y, int width, int height, int type, int who, int save);

void setTroopOnMap(char** map, Troop* t, int x, int y, int type, int who, int save);

void setMap(char** map, int save);

void printMap(WINDOW* win, char** map);
