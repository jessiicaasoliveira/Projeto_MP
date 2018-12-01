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

/**
 **************************************************************************
 * @brief Função: Ler o Path X
 *
 * Descrição:
 * A Função lê a coordenada X do próximo passo do Path.
 *
 * Parâmetros:
 * @param int pathfinderID - identificador da Origem (de onde o path sai)
 * @param int pathLocation - local onde o path está atualmente
 *
 * Valor retornado:
 * @return int x - coordenada x do próximo passo do Path
 *
 * Assertiva de entrada:
 * int pathfinderID == 0 || pathfinderID == 1 || pathfinderID == 2 || pathfinderID == 3
 * int pathLocation >= 0
 *
 * Assertiva de saída:
 * int x >= 0
 ***************************************************************************/
int ReadPathX(int pathfinderID, int pathLocation)
{
    int x = 0;
    if (pathLocation <= pathLength[pathfinderID])
    {
        /* Read coordinate from bank */
        x = pathBank[pathfinderID][pathLocation*2-2];

    }
    return x;
}

/**
 **************************************************************************
 * @brief Função: Ler o Path Y
 *
 * Descrição:
 * A Função lê a coordenada y do próximo passo do Path.
 *
 * Parâmetros:
 * @param int pathfinderID - identificador da Origem (de onde o path sai)
 * @param int pathLocation - local onde o path está atualmente
 *
 * Valor retornado:
 * @return int y - coordenada y do próximo passo do Path
 *
 * Assertiva de entrada:
 * int pathfinderID == 0 || pathfinderID == 1 || pathfinderID == 2 || pathfinderID == 3
 * int pathLocation >= 0
 *
 * Assertiva de saída:
 * int y >= 0
 ***************************************************************************/
int ReadPathY(int pathfinderID, int pathLocation)
{
    int y = 0;
    if (pathLocation <= pathLength[pathfinderID])
    {
        /* Read coordinate from bank */
        y = pathBank[pathfinderID][pathLocation*2-1];

    }
    return y;
}

/**
 **************************************************************************
 * @brief Função: Mover uma Tropa do PC
 *
 * Descrição:
 * A Função recebe uma struct de uma tropa, o ID dessa tropa e a posição que essa tropa deve chegar. Então move essa tropa.
 *
 * Parâmetros:
 * @param int Troop* t - struct de uma tropa do PC
 * @param int ID - identificação de qual tropa vai ser movimentada
 * @param int targetY - coordenada y para onde a tropa deve ir
 * @param int targetX - coordenada x para onde a tropa deve ir
 *
 * Valor retornado:
 * @return Void - A função não retorna nada
 *
 * Assertiva de entrada:
 * Troop* t != NULL
 * int ID == 0 || ID == 1 || ID == 2
 * int targetY >= 0
 * int targetX >= 0
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void moveTroopX(Troop* t, int ID, int targetY, int targetX)
{
    if (t->y != targetY || t->x != targetX)
    {
        if (pathStatus[ID] == notStarted || pathLocation[ID] == 5)
        {
            pathStatus[ID] = FindPath(ID, t->y, t->x, targetY, targetX);

        }
    }

    if (pathStatus[ID] == found) moveEnemyTroop(t, ID);
}


/**
 **************************************************************************
 * @brief Função: Controla os Movimentos do PC
 *
 * Descrição:
 * A Função inicia a procura de paths e chama uma função de mover as tropas.
 *
 * Parâmetros:
 * @param Troop* t1 - Tropa do tipo 1 do PC
 * @param Troop* t2 - Tropa do tipo 2 do PC
 * @param Troop* t3 - Tropa do tipo 3 do PC
 *
 * Valor retornado:
 * @return Void - A Função não retorna nada
 *
 * Assertiva de entrada:
 * Troop* t1 != NULL
 * Troop* t2 != NULL
 * Troop* t3 != NULL
 *
 * Assertiva de saída:
 * Função Void
 ***************************************************************************/
void enemyMove(Troop* t1, Troop* t2, Troop* t3)
{

    if(B1_p.defense > 0 && B1_p.hp > 0)
        moveTroopX(&T1_e, 1, B1_p.y+1, B1_p.x+B1_p.width+1);

    else if(B1_p.defense == 0 && B1_p.hp == -1)
        moveTroopX(t1, 1, Base_p.y, Base_p.x+Base_p.width+1);

    if(B3_p.defense > 0 && B3_p.hp > 0)
        moveTroopX(t2, 2, B3_p.y+1, B3_p.x+B3_p.width+1);

    else if(B3_p.defense == 0 && B3_p.hp == -1)
        moveTroopX(t2, 2, Base_p.y+2, Base_p.x+Base_p.width+1);

    if(B2_p.defense > 0 && B2_p.hp > 0)
        moveTroopX(t3, 3, B2_p.y+1, B2_p.x+B2_p.width+1);

    else if(B2_p.defense == 0 && B2_p.hp == -1)
        moveTroopX(t3, 3, Base_p.y+3, Base_p.x+Base_p.width+1);
}



/**
 **************************************************************************
 * @brief Função: Controlar a Criação de Tropas do PC
 *
 * Descrição:
 * A Função recebe as structs da base, das tropas e do prédio responsável pela criação de tropas. Então ela verifica se a tropa está do lado do prédio que gera tropa, e se há recursos para gerar mais tropas. Então essa tropa tem a quantidade aumentada.
 *
 * Parâmetros:
 * @param Troop* t1 - struct da tropa do tipo 1 do PC
 * @param Troop* t2 - struct da tropa do tipo 2 do PC
 * @param Troop* t3 - struct da tropa do tipo 3 do PC
 * @param Build* b3 - struct do prédio do tipo 3 do PC
 * @param Base* b - struct da base do PC
 *
 * Valor retornado:
 * @return Void. A função não retorna nada
 *
 * Assertiva de entrada:
 * Troop* t1 != NULL
 * Troop* t2 != NULL
 * Troop* t3 != NULL
 * Build* b3 != NULL
 * Base* b != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void enemyTroopController(Troop* t1, Troop* t2, Troop* t3, Build* b3, Base* b)
{
    if(enemyTroopChecker(t1, 0) && b->r1Amount > 0)
    {
        t1->amount += (b3->mineSpeed * T1_RATE);
        b->r1Amount += (-b3->resourceConsume * R1_COST);

        if(b->r1Amount <=0)
            b->r1Amount = 0;
    }

    if(enemyTroopChecker(t2, 0) && b->r1Amount > 0)
    {
        t2->amount += (b3->mineSpeed * T2_RATE);
        b->r1Amount += (-b3->resourceConsume * R1_COST);

        if(b->r1Amount <=0)
            b->r1Amount = 0;
    }

    if(enemyTroopChecker(t3, 0) && b->r2Amount > 0)
    {
        t3->amount += (b3->mineSpeed * T3_RATE);
        b->r2Amount += (-b3->resourceConsume * R2_COST);

        if(b->r2Amount <=0)
            b->r2Amount = 0;
    }
}

/**
 **************************************************************************
 * @brief Função: Controlar o Ataque de Tropas do PC aos Prédios/Base
 *
 * Descrição:
 * A Função recebe as structs dos prédios, da base e de uma tropa. Ela verifica se a tropa está perto de algum prédio/base e se estiver é calculado o dano que essa tropa está dando no prédio/base. Antes de diminuir a vida do prédio/base é necessário diminuir a defesa para 0.
 *
 * Parâmetros:
 * @param Troop* t - struct da tropa do tipo 1 do PC
 * @param Base* b - struct da base
 * @param Build* b1 - struct do prédio do tipo 1
 * @param Build* b2 - struct do prédio do tipo 2
 * @param Build* b3 - struct do prédio do tipo 3
 *
 * Valor retornado:
 * @return Void. A função não retorna nada
 *
 * Assertiva de entrada:
 * Troop* t != NULL
 * Base* b != NULL
 * Build* b1 != NULL
 * Build* b2 != NULL
 * Build* b3 != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void enemyHitControl(Troop* t, Base* b, Build* b1, Build* b2, Build* b3)
{
    switch(enemyTroopChecker(t, 1))
    {
    case 4:

        if(b->defense > 0)
        {
            b->defense += (-t->damage);

            if(b->defense < 0)
                b->defense = 0;
        }

        else if(b->defense == 0 && b->hp > 0)
        {
            b->hp += (-t->damage);

            if(b->hp < 0)
                b->hp = 0;
        }

        break;

    case 5:

        if(b1->defense > 0)
        {
            b1->defense += (-t->damage);

            if(b1->defense < 0)
                b1->defense = 0;
        }

        else if(b1->defense == 0 && b1->hp > 0)
        {
            b1->hp += (-t->damage);

            if(b1->hp < 0)
                b1->hp = 0;
        }

        break;

    case 7:

        if(b3->defense > 0)
        {
            b3->defense += (-t->damage);

            if(b3->defense < 0)
                b3->defense = 0;
        }

        else if(b3->defense == 0 && b3->hp > 0)
        {
            b3->hp += (-t->damage);

            if(b3->hp < 0)
                b3->hp = 0;
        }

        break;

    case 6:

        if(b2->defense > 0)
        {
            b2->defense += (-t->damage);

            if(b2->defense < 0)
                b2->defense = 0;
        }

        else if(b2->defense == 0 && b2->hp > 0)
        {
            b2->hp += (-t->damage);

            if(b2->hp < 0)
                b2->hp = 0;
        }

        break;
    }
}







/**
 **************************************************************************
 * @brief Função: Mostrar Movimentos das Tropas do PC
 *
 * Descrição:
 * A Função recebe a struct de uma tropa e sua identificação. Então se essa tropa foi movimentanda, a função atualiza a tela de acordo com essa movimentação.
 *
 * Parâmetros:
 * @param Troop* t - Struct da tropa do PC
 * @param int ID - identificação da tropa
 *
 * Valor retornado:
 * @return Void - A Função não retorna nada
 *
 * Assertiva de entrada:
 * Troop* t != NULL
 * int ID == 0 || ID == 1 || ID == 2
 *
 * Assertiva de saída:
 * Função Void
 ***************************************************************************/
void moveEnemyTroop(Troop* t, int ID)
{
    switch(ID)
    {
        case 1:
        if(map1[t->y][t->x] == MAP_TILE || map1[t->y][t->x] == '7')
            map1[t->y][t->x] = MAP_TILE;
        break;

    case 2:
        if(map1[t->y][t->x] == MAP_TILE || map1[t->y][t->x] == '8')
            map1[t->y][t->x] = MAP_TILE;
        break;

    case 3:
        if(map1[t->y][t->x] == MAP_TILE || map1[t->y][t->x] == '9')
            map1[t->y][t->x] = MAP_TILE;
        break;
    }

    ReadPath(ID, t->y, t->x, 1);

    if (t->y > xPath[ID]) t->y--;

    if (t->y < xPath[ID]) t->y++;

    if (t->x > yPath[ID]) t->x--;

    if (t->x < yPath[ID]) t->x++;

    switch(ID)
    {
    case 1:
        if(map1[t->y][t->x] == MAP_TILE) map1[t->y][t->x] = '7';
        break;

    case 2:
        if(map1[t->y][t->x] == MAP_TILE) map1[t->y][t->x] = '8';
        break;

    case 3:
        if(map1[t->y][t->x] == MAP_TILE) map1[t->y][t->x] = '9';
        break;
    }
}

/**
 **************************************************************************
 * @brief Função: Encontra um Path
 *
 * Descrição:
 * A Função utiliza um algoritmo chamado A* ( A star) para encontrar um Path.
 *
 * Parâmetros:
 * @param int pathfinderID - Identificador da Origem( de onde o path sai)
 * @param int startingX - Coordenada x que a origem está
 * @param int startingY - Coordenada y que a origem está
 * @param int targetX - Coordenada x que o path quer chegar
 * @param int targetY - Coordenada y que o path quer chegar
 *
 * Valor retornado:
 * @return int path - se a função encontra um caminho
 * @return int nonexistent - se a função não encontra nada
 *
 * Assertiva de entrada:
 * int pathfinderID == 0 || pathfinderID == 1 || pathfinderID == 2 || pathfinderID == 3
 * int startingX >= 0
 * int startingY >= 0
 * int targetX >= 0
 * int targetY >= 0
 *
 * Assertiva de saída:
 * int path == 1
 * int noexistent == 0
 ***************************************************************************/
int FindPath (int pathfinderID,int startingX, int startingY, int targetX, int targetY)
{

    /* Constants declaration */
    int mapWidth = map_y, mapHeight = map_x, onClosedList = 10;

    /* Created needed arrays */
    char walkability [mapWidth][mapHeight];
    int openList[mapWidth*mapHeight+2]; /* Array holding ID of open list items */
    int whichList[mapWidth+1][mapHeight+1];  /* Matrix used to record */

    /* whether a cell is on the open list or on the closed list */
    int openX[mapWidth*mapHeight+2]; /* 1d array stores the x location of an item on the open list */
    int openY[mapWidth*mapHeight+2]; /* 1d array stores the y location of an item on the open list */
    int parentX[mapWidth+1][mapHeight+1]; /* 2d array to store parent of each cell (x) */
    int parentY[mapWidth+1][mapHeight+1]; /* 2d array to store parent of each cell (y) */
    int Fcost[mapWidth*mapHeight+2];	/* 1d array to store F cost of a cell on the open list */
    int Gcost[mapWidth+1][mapHeight+1]; /* 2d array to store G cost for each cell */
    int Hcost[mapWidth*mapHeight+2];	/* 1d array to store H cost of a cell on the open list */
    int onOpenList = 0, parentXval = 0, parentYval = 0, a = 0, b = 0, m = 0, u = 0, v = 0, temp = 0;
    int addedGCost = 0, tempGcost = 0, path = 0, newOpenListItemID = 0, corner = 0, numberOfOpenListItems = 0;
    int tempx, pathX, pathY, cellPosition, startX, startY, x, y;

    for(x = 0; x < mapWidth; x++)
    {
        for(y = 0; y < mapHeight; y++)
        {
            switch(map1[x][y])
            {
            case '1':
            case '2':
            case '3':
            case '7':
            case '8':
            case '9':
            case 'X':
            case 'B':
            case 'Z':
            case 'Y':
            case 'L':
            case 'M':
            case 'N':
            case 'C':
                walkability[x][y] = walkable;
                break;

            default:
                walkability[x][y] = walkable;
            }
        }
    }

    startX = startingX;
    startY = startingY;

    /* If starting location and target are in the same location */
    if (startX == targetX && startY == targetY && pathLocation[pathfinderID] > 0)
        return found;

    if (startX == targetX && startY == targetY && pathLocation[pathfinderID] == 0)
        return nonexistent;

    /* If target square is unwalkable, return that it's a nonexistent path. */
    if (walkability[targetX][targetY] == unwalkable)
        goto noPath;

    /* Reset some variables that need to be cleared */
    if (onClosedList > 1000000) /* reset whichList occasionally */
    {
        for (x = 0; x < mapWidth; x++)
        {
            for (y = 0; y < mapHeight; y++)
                whichList [x][y] = 0;
        }
        onClosedList = 10;
    }
    onClosedList = onClosedList+2; /* changing the values of onOpenList and onClosed list is faster than redimming whichList() array*/
    onOpenList = onClosedList-1;
    pathLength [pathfinderID] = notStarted;
    pathLocation [pathfinderID] = notStarted;
    Gcost[startX][startY] = 0; /* reset starting square's G value to 0 */

    /* Add the starting location to the open list of squares to be checked. */
    numberOfOpenListItems = 1;
    openList[1] = 1; /*assign it as the top (and currently only) item in the open list, maintained as a binary heap*/
    openX[1] = startX ;
    openY[1] = startY;

    /* Do the until a path is found or deemed nonexistent */
    do
    {

        /* If the open list is not empty, take the first cell off of the list.*/
        /* This is the lowest F cost cell on the open list. */
        if (numberOfOpenListItems != 0)
        {

            /* Pop the first item off the open list. */
            parentXval = openX[openList[1]];
            parentYval = openY[openList[1]]; /* record cell coordinates of the item */
            whichList[parentXval][parentYval] = onClosedList; /* add the item to the closed list */

            /*Open List = Binary Heap: Delete this item from the open list, which
            is maintained as a binary heap. For more information on binary heaps */
            numberOfOpenListItems = numberOfOpenListItems - 1; /* reduce number of open list items by 1 */

            /* Delete the top item in binary heap and reorder the heap, with the lowest F cost item rising to the top.*/
            openList[1] = openList[numberOfOpenListItems+1]; /* move the last item in the heap up to slot 1 */
            v = 1;

            /* Repeat the following until the new item in slot #1 sinks to its proper spot in the heap. */
            do
            {
                u = v;
                if (2*u+1 <= numberOfOpenListItems) /* if both children exist */
                {
                    /* Check if the F cost of the parent is greater than each child. */
                    /* Select the lowest of the two children. */
                    if (Fcost[openList[u]] >= Fcost[openList[2*u]])
                        v = 2*u;
                    if (Fcost[openList[v]] >= Fcost[openList[2*u+1]])
                        v = 2*u+1;
                }
                else
                {
                    if (2*u <= numberOfOpenListItems) /* if only child 1 exists */
                    {
                        /* Check if the F cost of the parent is greater than child 1 */
                        if (Fcost[openList[u]] >= Fcost[openList[2*u]])
                            v = 2*u;
                    }
                }

                if (u != v) /* if parent's F is > one of its children, swap them */
                {
                    temp = openList[u];
                    openList[u] = openList[v];
                    openList[v] = temp;
                }
                else
                    break; /* otherwise, exit loop */

            }
            while (1); /* reorder the binary heap */

            for (b = parentYval-1; b <= parentYval+1; b++)
            {
                for (a = parentXval-1; a <= parentXval+1; a++)
                {

                    /* If not off the map (do this first to avoid array out-of-bounds errors) */
                    if (a != -1 && b != -1 && a != mapWidth && b != mapHeight)
                    {

                        /* If not already on the closed list (items on the closed list have
                        already been considered and can now be ignored). */
                        if (whichList[a][b] != onClosedList)
                        {

                            /* If not a wall/obstacle square. */
                            if (walkability [a][b] != unwalkable)
                            {

                                corner = walkable;
                                if (a == parentXval-1)
                                {
                                    if (b == parentYval-1)
                                    {
                                        if (walkability[parentXval-1][parentYval] == unwalkable
                                                || walkability[parentXval][parentYval-1] == unwalkable)
                                            corner = unwalkable;
                                    }
                                    else if (b == parentYval+1)
                                    {
                                        if (walkability[parentXval][parentYval+1] == unwalkable
                                                || walkability[parentXval-1][parentYval] == unwalkable)
                                            corner = unwalkable;
                                    }
                                }
                                else if (a == parentXval+1)
                                {
                                    if (b == parentYval-1)
                                    {
                                        if (walkability[parentXval][parentYval-1] == unwalkable
                                                || walkability[parentXval+1][parentYval] == unwalkable)
                                            corner = unwalkable;
                                    }
                                    else if (b == parentYval+1)
                                    {
                                        if (walkability[parentXval+1][parentYval] == unwalkable
                                                || walkability[parentXval][parentYval+1] == unwalkable)
                                            corner = unwalkable;
                                    }
                                }
                                if (corner == walkable)
                                {
                                    /* If not already on the open list, add it to the open list. */
                                    if (whichList[a][b] != onOpenList)
                                    {

                                        /* Create a new open list item in the binary heap. */
                                        newOpenListItemID = newOpenListItemID + 1; /* each new item has a unique ID */
                                        m = numberOfOpenListItems+1;
                                        openList[m] = newOpenListItemID; /* place the new open list item (actually, its ID) at the bottom of the heap */
                                        openX[newOpenListItemID] = a;
                                        openY[newOpenListItemID] = b; /* record the x and y coordinates of the new item */

                                        /* Calculate its G cost */
                                        if (abs(a-parentXval) == 1 && abs(b-parentYval) == 1)
                                            addedGCost = 14; /* cost of going to diagonal squares */
                                        else
                                            addedGCost = 10; /*cost of going to non-diagonal squares*/
                                        Gcost[a][b] = Gcost[parentXval][parentYval] + addedGCost;

                                        /* Calculate its H and F costs and parent */
                                        Hcost[openList[m]] = 10*(abs(a - targetX) + abs(b - targetY));
                                        Fcost[openList[m]] = Gcost[a][b] + Hcost[openList[m]];
                                        parentX[a][b] = parentXval ;
                                        parentY[a][b] = parentYval;

                                        /* Move the new open list item to the proper place in the binary heap.
                                         * Starting at the bottom, successively compare to parent items,
                                         * swapping as needed until the item finds its place in the heap
                                         * or bubbles all the way to the top (if it has the lowest F cost). */
                                        while (m != 1) /* While item hasn't bubbled to the top (m=1) */
                                        {
                                            /* Check if child's F cost is < parent's F cost. If so, swap them. */
                                            if (Fcost[openList[m]] <= Fcost[openList[m/2]])
                                            {
                                                temp = openList[m/2];
                                                openList[m/2] = openList[m];
                                                openList[m] = temp;
                                                m = m/2;
                                            }
                                            else
                                                break;
                                        }
                                        numberOfOpenListItems = numberOfOpenListItems+1; /* add one to the number of items in the heap */

                                        /* Change whichList to show that the new item is on the open list.*/
                                        whichList[a][b] = onOpenList;
                                    }

                                    /*If adjacent cell is already on the open list, check to see if this
                                     path to that cell from the starting location is a better one.
                                     If so, change the parent of the cell and its G and F costs.*/
                                    else /* If whichList(a,b) = onOpenList */
                                    {

                                        /* Figure out the G cost of this possible new path */
                                        if (abs(a-parentXval) == 1 && abs(b-parentYval) == 1)
                                            addedGCost = 14; /* cost of going to diagonal tiles */
                                        else
                                            addedGCost = 10; /*cost of going to non-diagonal tiles */
                                        tempGcost = Gcost[parentXval][parentYval] + addedGCost;

                                        /* If this path is shorter (G cost is lower) then change
                                         *  the parent cell, G cost and F cost. */
                                        if (tempGcost < Gcost[a][b]) /* if G cost is less, */
                                        {
                                            parentX[a][b] = parentXval; /* change the square's parent */
                                            parentY[a][b] = parentYval;
                                            Gcost[a][b] = tempGcost;/*change the G cost */

                                            for (x = 1; x <= numberOfOpenListItems; x++) /* look for the item in the heap */
                                            {
                                                if (openX[openList[x]] == a && openY[openList[x]] == b) /*item found */
                                                {
                                                    Fcost[openList[x]] = Gcost[a][b] + Hcost[openList[x]];/*change the F cost*/

                                                    /* See if changing the F score bubbles the item up from it's current location in the heap*/
                                                    m = x;
                                                    while (m != 1) /*While item hasn't bubbled to the top (m=1)*/
                                                    {
                                                        /*Check if child is < parent. If so, swap them.*/
                                                        if (Fcost[openList[m]] < Fcost[openList[m/2]])
                                                        {
                                                            temp = openList[m/2];
                                                            openList[m/2] = openList[m];
                                                            openList[m] = temp;
                                                            m = m/2;
                                                        }
                                                        else
                                                            break;
                                                    }
                                                    break; /*exit for x = loop*/
                                                } /*If openX(openList(x)) = a*/
                                            } /*For x = 1 To numberOfOpenListItems*/
                                        }/*If tempGcost < Gcost(a,b) */
                                    }/*else If whichList(a,b) = onOpenList */
                                }/*If not cutting a corner*/
                            }/*If not a wall/obstacle square.*/
                        }/*If not already on the closed list*/
                    }/*If not off the map*/
                }/*for (a = parentXval-1; a <= parentXval+1; a++){*/
            }/*for (b = parentYval-1; b <= parentYval+1; b++){ */

        }/*if (numberOfOpenListItems != 0)*/

        /* If open list is empty then there is no path. */
        else
        {
            path = nonexistent;
            break;
        }

        /*If target is added to open list then path has been found.*/
        if (whichList[targetX][targetY] == onOpenList)
        {
            path = found;
            break;
        }

    }
    while (1);/*Do until path is found or deemed nonexistent*/

    /* Save the path if it exists.*/
    if (path == found)
    {

        /* Working backwards from the target to the starting location by checking
        	each cell's parent, figure out the length of the path. */
        pathX = targetX;
        pathY = targetY;
        do
        {
            /*Look up the parent of the current cell.*/
            tempx = parentX[pathX][pathY];
            pathY = parentY[pathX][pathY];
            pathX = tempx;

            /*Figure out the path length*/
            pathLength[pathfinderID] = pathLength[pathfinderID] + 1;
        }
        while (pathX != startX || pathY != startY);

        /* Resize the data bank to the right size in bytes */
        pathBank[pathfinderID] = (int*) realloc (pathBank[pathfinderID],
                                 pathLength[pathfinderID]*8);
        pathX = targetX ;
        pathY = targetY;
        cellPosition = pathLength[pathfinderID]*2;
        do
        {
            cellPosition = cellPosition - 2;
            pathBank[pathfinderID] [cellPosition] = pathX;
            pathBank[pathfinderID] [cellPosition+1] = pathY;
            tempx = parentX[pathX][pathY];
            pathY = parentY[pathX][pathY];
            pathX = tempx;

        }while (pathX != startX || pathY != startY);

        ReadPath(pathfinderID, startingX, startingY, 1);

    }
    return path;


    /* If there is no path to the selected target, set the pathfinder's
    xPath and yPath equal to its current location and return that the
    path is nonexistent.*/

noPath:
    xPath[pathfinderID] = startingX;
    yPath[pathfinderID] = startingY;
    return nonexistent;
}




/**
 **************************************************************************
 * @brief Função: Verificar as Redondezas da Tropa do PC
 *
 * Descrição:
 * A Função recebe a struct de uma tropa e verifica as redondezas dessa tropa, e retorna um valor de acordo com o que está do lado dessa tropa.
 *
 * Parâmetros:
 * @param Troop* t - struct da tropa
 * @param int mode - flag para identificar se a função foi chamada para checar se a tropa está perto do prédio responsável por aumentar tropas (0) ou se foi chamada para checar se há tropas inimigas por perto (1)
 *
 * Valor retornado:
 * @return 0 - caso a tropa não esteja perto de nada
 * @return 1 - caso a mode = 0 e a tropa esteja perto do prédio responsável por gerar tropas
 * @return 4 - caso a tropa esteja perto do base 'B'
 * @return 5 - caso a tropa esteja perto do prédio 'X'
 * @return 6 - caso a tropa esteja perto do prédio 'Y'
 * @return 7 - caso a tropa esteja perto do prédio 'Z'
 *
 * Assertiva de entrada:
 * Troop* t != NULL
 * int mode == 0 || mode == 1
 *
 * Assertiva de saída:
 * A função retorna valores fixos.
 ***************************************************************************/
int enemyTroopChecker(Troop* t, int mode)
{
    switch(mode)
    {
    case 0: /* Caso para gerar tropa */

        if(t->x+1 < map_x && map1[t->y][t->x+1] == 'M')
            return 1;

        else if(t->x-1 >= 0 && map1[t->y][t->x-1] == 'M')
            return 1;

        else if(t->y-1 >= 0 && map1[t->y-1][t->x] == 'M')
            return 1;

        else if(t->y+1 < map_y && map1[t->y+1][t->x] == 'M')
            return 1;

        break;

    case 1: /* Caso de batalha */

        if(t->x+1 < map_x)
        {
            switch(map1[t->y][t->x+1])
            {

            case 'B':
                return 4;

            case 'X':
                return 5;

            case 'Y':
                return 6;

            case 'Z':
                return 7;
            }
        }

        if(t->x-1 >= 0)
        {
            switch(map1[t->y][t->x-1])
            {

            case 'B':
                return 4;

            case 'X':
                return 5;

            case 'Y':
                return 6;

            case 'Z':
                return 7;

            }
        }

        if(t->y-1 >= 0)
        {
            switch(map1[t->y-1][t->x])
            {

            case 'B':
                return 4;

            case 'X':
                return 5;

            case 'Y':
                return 6;

            case 'Z':
                return 7;
            }
        }

        if(t->y+1 < map_y)
        {
            switch(map1[t->y+1][t->x])
            {

            case 'B':
                return 4;

            case 'X':
                return 5;

            case 'Y':
                return 6;

            case 'Z':
                return 7;

            }
        }

        break;
    }

    return 0;
}