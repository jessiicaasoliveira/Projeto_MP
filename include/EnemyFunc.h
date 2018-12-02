#include "PlayerFunc.h"

extern Base Base_e;
extern Build B1_e, B2_e, B3_e;
extern Troop T1_e, T2_e, T3_e;

/*Funções*/
void InitializePathfinder();
void EndPathfinder();
int FindPath(int pathfinderID,int startingX, int startingY, int targetX, int targetY);
int ReadPathX(int pathfinderID, int pathLocation);
int ReadPathY(int pathfinderID, int pathLocation);
void enemyMove(Troop* t1, Troop* t2, Troop* t3);
void loadMapData(int** walkability, int mapWidth, int mapHeight);
void ReadPath(int pathfinderID, int currentX, int currentY, int pixelsPerFrame);
void enemyMove(Troop* t1, Troop* t2, Troop* t3);
void moveEnemyTroop(Troop* t, int ID);
int doPathFinding(Troop* t, int ID, int targetY, int targetX);
int enemyTroopChecker(Troop* t, int mode);
void enemyTroopController(Troop* t1, Troop* t2, Troop* t3, Build* b3, Base* b);
void enemyHitControl(Troop* t, Base* b, Build* b1, Build* b2, Build* b3);
int checkAtack(Troop* t);
int checkAmount(Troop* t, int ID);
void moveTroopX(Troop* t, int ID, int targetY, int targetX);
