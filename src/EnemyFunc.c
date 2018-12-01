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



/**
 **************************************************************************
 * @brief Função: Finaliza o PathFinder
 *
 * Descrição:
 * A Função desaloca a memória usada pelo Pathfinder.
 *
 * Parâmetros:
 * @param Sem Parâmetros
 *
 * Valor retornado:
 * @return Void - A função não retorna nada
 *
 * Assertiva de entrada:
 * Sem parâmetros
 *
 * Assertiva de saída:
 * Função Void
 ***************************************************************************/
void EndPathfinder()
{
    int x;
    for (x = 0; x < numberPeople+1; x++)
        free (pathBank [x]);
}

/**
 **************************************************************************
 * @brief Função: Ler o Path
 *
 * Descrição:
 * A Função lê o path data e converte em coordendas para a tela.
 *
 * Parâmetros:
 * @param int pathfinderID - identificador da Origem ( de onde o path sai)
 * @param int currentX - coordenada x atual que o path se encontra
 * @param int currentY - coordenada y atual que o path se encontra
 * @param int pixelsPerFrame - quantidade de pixels atualizados em 1 frame
 *
 * Valor retornado:
 * @return Void - A Função não retorna nada
 *
 * Assertiva de entrada:
 * int pathfinderID == 0 || pathfinderID == 1 || pathfinderID == 2 || pathfinderID == 3
 * int currentX >= 0
 * int currentY >= 0
 * int pixelsPerFrame == 1
 *
 * Assertiva de saída:
 * Função Void
 ***************************************************************************/
void ReadPath(int pathfinderID, int currentX, int currentY, int pixelsPerFrame)
{
    int ID = pathfinderID;

    if (pathStatus[ID] == found)
    {
        if (pathLocation[ID] < pathLength[ID])
        {
            if (pathLocation[ID] == 0 ||
                    (abs(currentX - xPath[ID]) < pixelsPerFrame && abs(currentY - yPath[ID]) < pixelsPerFrame))
                pathLocation[ID] = pathLocation[ID] + 1;
        }

        xPath[ID] = ReadPathX(ID,pathLocation[ID]);
        yPath[ID] = ReadPathY(ID,pathLocation[ID]);

        if (pathLocation[ID] == pathLength[ID])
        {
            if (abs(currentX - xPath[ID]) < pixelsPerFrame
                    && abs(currentY - yPath[ID]) < pixelsPerFrame)
                pathStatus[ID] = notStarted;
        }
    }

    else
    {
        xPath[ID] = currentX;
        yPath[ID] = currentY;
    }
}