#include "MapFunc.h"

extern int termLines,/*numéro de linhas do terminal*/
            termCols;/*número de colunas do terminal*/

/*Funções*/
void startWin();
int getMenu(int mouse_x, int mouse_y);
int startGameMenu();
WINDOW* createWin(int WinHeight, int WinWidth, int WinStarty, int WinStartx);
void destroyWin(WINDOW** local_win);
void middlePrint(WINDOW* win, int WinStarty, int WinStartx, int WinWidth, char* string, chtype color);
WINDOW* gameWindow(int win_y, int win_x);
void refreshWindows(WINDOW* gameWin, WINDOW* statusWin);
void printPlayerStatus(WINDOW* status, Base* b, Build* b1, Build* b2, Build* b3, Troop* t1, Troop* t2, Troop* t3);
void printEnemyStatus(WINDOW* status, Base* b, Build* b1, Build* b2, Build* b3, Troop* t1, Troop* t2, Troop* t3);
int pauseGameMenu();
void gameEnd(Base* b_p, Base* b_e);
