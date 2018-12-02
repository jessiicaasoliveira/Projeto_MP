#include "EnemyFunc.h"

/*matriz do mapa do jogo*/
char** map1;

/*funções*/

char** allocMap(char** map, int y, int x);

char** deallocMap(char** map);

void setBaseOnMap(char** map, Base* bc, int x, int y, int width, int height, int who, int save);
