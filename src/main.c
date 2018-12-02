#include "WinManager.h"

/**main*/
int main() {
    extern int save;
    startWin();

    switch (startGameMenu()) {
        case 0:
            save = NEW_GAME;
            startNewGame();
            break;

        case 1:
            save = LOAD_GAME;
            startNewGame();
            break;

        case 2:
            mvprintw(0, 0, "Jogo Feito por: Amanda , Bruno e Jessica");
            refresh();
            getchar();
            break;

        case 3:
            refresh();
            endwin();
            return 1;
    }

    erase();
    refresh();
    endwin();
    return 0;
}
