#include "GameLogic.h"

typedef struct base
{
    int r1Amount,/*quantidade do recurso 1*/
    r2Amount,/*quantidade do recurso 2*/
    defense,/*defesa da base*/
    x, y,/*posição da base*/
    height,/*altura da base*/
    width,/*largura da base*/
    hp;/*vida da base*/
}Base;

typedef struct build
{
    int hp,/*vida do prédio*/
    defense,/*defesa do prédio*/
    mineSpeed,/*velocidade de mineração*/
    resourceConsume,/*consumo de recurso*/
    x, y,/*posição*/
    height,/*altura do prédio*/
    width;/*largura do prédio*/
}Build;

typedef struct troop
{
    int hp,/*vida da tropa*/
    damage,/*dano*/
    defense,/*defesa*/
    amount,/*quantidade de tropas*/
    x, y;/*posição*/
}Troop;

extern Base Base_p;
extern Build B1_p, B2_p, B3_p;
extern Troop T1_p, T2_p, T3_p;

/*funções*/
Base* setBaseAtt(Base* bc, int x, int y, int height, int width);
Build* setBuildAtt(Build* b, int x, int y, int height, int width, int type);
Troop* setTroopAtt(Troop* t, int x, int y, int type);
void moveTroop(WINDOW* win, char** map);
