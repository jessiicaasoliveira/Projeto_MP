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
