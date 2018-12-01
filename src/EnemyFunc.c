#include "EnemyFunc.h"

/**struct Base do PC*/
Base Base_e;
/**struct Prédio 1 do PC*/
Build B1_e;
/**struct Prédio 2 do PC*/
Build B2_e;
/**struct Prédio 3 do PC*/
Build B3_e;
/**struct Tropa 1 do PC*/
Troop T1_e;
/**struct Tropa 2 do PC*/
Troop T2_e;
/**struct Tropa 3 do PC*/
Troop T3_e;

/** path-related constants */
int notStarted = 0;
/** constants for path found ou not found*/
int found = 1, nonexistent = 2;
/** constants for walkability array */
int walkable = 0, unwalkable = 1;
/** number of troops or builds*/
int numberPeople = 3;
/**stores numbers of needed paths */
int* pathBank [4];
/**stores length of the found path for critter */
int pathLength[4];
/* stores current status along the chosen path for critter */
int pathStatus[4];
/** stores current position along the chosen path for critter */
int pathLocation[4];
/**Path reading variables */
int xPath[4];
/**Path reading variables */
int yPath[4];

/**
 **************************************************************************
 * @brief Função: Inicializa o PathFinder
 *
 * Descrição:
 * A Função aloca memória para o Pathfinder.
 *
 * Parâmetros:
 * @param Sem Parâmetros
 *
 * Valor retornado:
 * @return Void - A Função não retorna nada
 *
 * Assertiva de entrada:
 * Sem parâmetros
 *
 * Assertiva de saída:
 * Função Void
 ***************************************************************************/
void InitializePathfinder()
{
    int x;
    for (x = 0; x < numberPeople+1; x++)
        pathBank[x] = (int*)malloc(4);
}