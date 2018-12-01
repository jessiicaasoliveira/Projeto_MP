#include "WinManager.h"

/** This define gets exactly the size of the array of arrays */
#define ARRAY_SIZE(a) (sizeof(a) / sizeof(a[0]))

/** variável para o número de linhas do terminal*/
int termLines;
/** variável para o número de colunas do terminal*/
int termCols;

/**
 **************************************************************************
 * @brief Função: Iniciar as funções da Ncurses usadas no jogo
 *
 * Descrição:
 * A Função é responsável por iniciar tudo que o programa irá utilizar. Entre eles, as specials keys, as cores, o uso do mouse, captura o tamanho do terminal, desabilita o echo (a necessidade de apertar enter para capturar uma entrada) e inicia a janela da ncurses. Com tudo inicializado as outras funções podem funcionar.
 *
 * Parâmetros:
 * @param sem parâmetros
 *
 * Valor retornado:
 * @return Void - a função não retorna nada
 *
 * Assertiva de entrada:
 * sem parâmetros
 *
 * Assertiva de saída:
 * função void
 ***************************************************************************/
void startWin()
{
    /*inicia a janela da ncurses*/
	initscr();
	cbreak();
	start_color();
    /*desabilita a necessidade de dar enter quando digita algo*/
	noecho();
	curs_set(1);
    /*habilita a special keys na tela da ncurses*/
	keypad(stdscr, TRUE);
    /*pega o tamanho do terminal*/
	getmaxyx(stdscr, termLines, termCols);
    /*possibilita a identificação do mouse*/
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL);

    /* Setting pairs of colors */
    init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(4, COLOR_BLUE, COLOR_BLACK);
	init_pair(5, COLOR_BLUE, COLOR_WHITE);
	init_pair(6, COLOR_CYAN, COLOR_WHITE);
	init_pair(7, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(8, COLOR_RED, COLOR_WHITE);
	init_pair(9, COLOR_GREEN, COLOR_WHITE);
	init_pair(10, COLOR_YELLOW, COLOR_BLACK);
}

/**
 **************************************************************************
 * @brief Função: Informar a posição do cursor do mouse no menu
 *
 * Descrição:
 * A Função recebe as coordenadas do cursor do mouse e identifica se o cursor está em algumas das opções do menu e retorna uma flag de acordo com a opção selecionada.
 *
 * Parâmetros:
 * @param int mouse_x - posição x do cursor no menu
 * @param int mouse_y - posição y do cursor no menu
 *
 * Valor retornado:
 * @return int i - flag que simboliza em qual opção do menu o mouse se encontra. Seus valores podem ser:
    0 - Mouse sobre nenhuma das opções
    1 - Mouse sobre a New Game
    2 - Mouse sobre o Load Game
    3 - Mouse sobre os Créditos
    4 - Mouse sobre o Exit
 *
 * Assertiva de entrada:
 * int mouse_x >= 0
 * int mouse_y >= 0
 *
 * Assertiva de saída:
 * int i == 0 || i == 1 || i == 2 || i == 3 || i == 4
 ***************************************************************************/
int getMenu(int mouse_x, int mouse_y){
    FILE* fp;
    int i = 0;

    if (mouse_y == (termLines/6 + 4)) {
        if (mouse_x >= (termCols/3 +15) && mouse_x <= (termCols/3 +23)) {
            i = 1; /*New Game*/
        }
    }
    if (mouse_y == (termLines/6 + 5)) {
        if (mouse_x >= (termCols/3 +15) && mouse_x <= (termCols/3 +24)) {
            i = 2; /*Load Game*/
        }
    }
    if (mouse_y == (termLines/6 + 6)) {
        if (mouse_x >= (termCols/3 +15) && mouse_x <= (termCols/3 +22)) {
            i = 3; /*Credits*/
        }
    }
    if (mouse_y == (termLines/6 + 7)) {
        if (mouse_x >= (termCols/3 +15) && mouse_x <= (termCols/3 +19)) {
            i = 4; /*Exit*/
        }
    }

    /*Assertiva de saída*/
    if (i != 0 && i != 1 && i != 2 && i != 3 && i != 4) {
        fp = fopen("Relatório_Erros.txt", "a");
        fprintf(fp, "Erro na getMenu (arquivo WinManager.c)\n");
        fclose(fp);
    }

    return i;
}

/**
 **************************************************************************
 * @brief Função: Iniciar, printar e controlar o Menu do Início do Jogo
 *
 * Descrição:
 * A Função inicializa os itens do menu inicial, inicializa o menu, cria a janela do menu sobre a janela da ncurses, printa o menu e as bordas com as suas cores. Então ela espera o usuário escolher um dos itens e dar "enter" . Depois a função destrói o menu inicial e retorna o valor do item selecionado.
 *
 * Parâmetros:
 * @param sem parâmetros
 *
 * Valor retornado:
 * @return (long int)itemPtr - valor do item selecionado pelo player. Dependendo da opção selecionada, a variável possui um valor. Podendo ser:
    0 - New Game
    1 - Load Game
    2 - Credits
    3 - Exit
 *
 * Assertiva de entrada:
 * sem parâmetros
 *
 * Assertiva de saída:
 * (long int)itemPtr == 0 || itemPtr == 1 || itemPtr == 2 || itemPtr == 3
 ***************************************************************************/
int startGameMenu()
{
    FILE* fp;
    char* choices[] = { "New Game", "Load Game", "Credits", "Exit" };
    ITEM** items;
    ITEM* cur_item;
	int n_choices, sel = 0;
	long int i;
	void* itemPtr;
	MENU* menu;
	WINDOW* menuWin;
    MEVENT evento_mouse;


    /* Initialize items to the menu */
	n_choices = ARRAY_SIZE(choices);
    items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    for(i = 0; i < n_choices; ++i)
    {
        items[i] = new_item(choices[i], NULL);
        set_item_userptr(items[i], (void*)i);
    }
	items[n_choices] = (ITEM *)NULL;

	/* Initiate menu */
	menu = new_menu((ITEM**)items);

    /* Create window for Menu */
    menuWin = createWin(10, 40, (termLines/6), (termCols/3));
    keypad(menuWin, TRUE);
    set_menu_win(menu, menuWin);
    set_menu_sub(menu, derwin(menuWin, 0, 0, 4, 13));
    set_menu_mark(menu, "- ");

    /* Print window and border*/
    box(menuWin, 0, 0);
    middlePrint(menuWin, 1, 0, 40, "TROOPS DUEL", COLOR_PAIR(1));
    mvwaddch(menuWin, 2, 0, ACS_LTEE);
	mvwhline(menuWin, 2, 1, ACS_HLINE, 38);
	mvwaddch(menuWin, 2, 39, ACS_RTEE);
	mvprintw(LINES - 2, 0, "Press UP and DOWN to navigate and ENTER to select an option");
	refresh();


	/* Setting grounds (fore and back) for the menu */
	set_menu_fore(menu, COLOR_PAIR(1)); //EDITAR CORES
	set_menu_back(menu, COLOR_PAIR(2)); //EDITAR CORES
	set_menu_grey(menu, COLOR_PAIR(3)); //EDITAR CORES

	/* Printing the menu */
	post_menu(menu);
	wrefresh(menuWin);

	while(!sel || (!loadGame() && itemPtr == (void*)1))
	{

        switch(wgetch(menuWin))
        {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;

            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;

            case 10:
                cur_item = current_item(menu);
                itemPtr = item_userptr(cur_item);
                sel = 1;
                break;
            case KEY_MOUSE:
                getmouse(&evento_mouse);
                if (evento_mouse.bstate & REPORT_MOUSE_POSITION) {
                    i = getMenu(evento_mouse.x , evento_mouse.y);
                    switch (i) {
                        case 1:
                            menu_driver(menu, REQ_FIRST_ITEM);
                            break;
                        case 2:
                            menu_driver(menu, REQ_FIRST_ITEM);
                            menu_driver(menu, REQ_DOWN_ITEM);
                            break;
                        case 3:
                            menu_driver(menu, REQ_LAST_ITEM);
                            menu_driver(menu, REQ_UP_ITEM);
                            break;
                        case 4:
                            menu_driver(menu, REQ_LAST_ITEM);
                            break;
                        default:
                            break;
                    }
                }
                if (evento_mouse.bstate & BUTTON1_CLICKED) {
                    sel = getMenu(evento_mouse.x, evento_mouse.y);
                    switch (sel) {
                        case 1:
                            menu_driver(menu, REQ_FIRST_ITEM);
                            cur_item = current_item(menu);
                            itemPtr = item_userptr(cur_item);
                            break;
                        case 2:
                            menu_driver(menu, REQ_FIRST_ITEM);
                            menu_driver(menu, REQ_DOWN_ITEM);
                            cur_item = current_item(menu);
                            itemPtr = item_userptr(cur_item);
                            break;
                        case 3:
                            menu_driver(menu, REQ_LAST_ITEM);
                            menu_driver(menu, REQ_UP_ITEM);
                            cur_item = current_item(menu);
                            itemPtr = item_userptr(cur_item);
                            break;
                        case 4:
                            menu_driver(menu, REQ_LAST_ITEM);
                            cur_item = current_item(menu);
                            itemPtr = item_userptr(cur_item);
                            break;
                        default:
                            break;
                    }
                }
                break;

        }
        wrefresh(menuWin);
	}

	unpost_menu(menu);
    free_menu(menu);
	for(i = 0; i < n_choices; ++i)
		free_item(items[i]);

    destroyWin(&menuWin);
    erase();
    refresh();

    /*Assertiva de saída*/
    if ((long int)itemPtr != 0 && (long int)itemPtr != 1 && (long int)itemPtr != 2 && (long int)itemPtr != 3) {
        fp = fopen("Relatório_Erros.txt", "a");
        fprintf(fp, "Erro na escolha de item na startGameMenu (arquivo WinManager.c)\n");
        fclose(fp);
    }
    return (long int)itemPtr;
}

/**
 **************************************************************************
 * @brief Função: Criar uma Janela
 *
 * Descrição:
 * A Função recebe o tamanho e uma posição no mapa e cria uma janela e retorna essa janela.
 *
 * Parâmetros:
 * @param int WinHeight - altura da janela
 * @param int WinWidth - largura da janela
 * @param int WinStarty - coordenada y que a janela vai começar a ser contruída
 * @param int WinStartx - coordenada x que a janela vai começar a ser contruída
 *
 * Valor retornado:
 * @return WINDOW* local_win - janela criada
 *
 * Assertiva de entrada:
 * int WinHeight > 0
 * int WinWidth > 0
 * int WinStarty >= 0
 * int WinStartx >= 0
 *
 * Assertiva de saída:
 * WINDOW* local_win != NULL
 ***************************************************************************/
WINDOW* createWin(int WinHeight, int WinWidth, int WinStarty, int WinStartx)
{
    FILE* fp;
    WINDOW* local_win;

	local_win = newwin(WinHeight, WinWidth, WinStarty, WinStartx);
	keypad(local_win, TRUE);
	wrefresh(local_win);

    /*Assertiva de saída*/
    if (local_win == NULL) {
        fp = fopen("Relatório_Erros.txt", "a");
        fprintf(fp, "Erro na createWin (arquivo WinManager.c)\n");
        fclose(fp);
    }
	return local_win;
}

/**
 **************************************************************************
 * @brief Função: Destruir uma Janela
 *
 * Descrição:
 * A Função recebe uma janela e a destrói, desalocando e retirando da tela.
 *
 * Parâmetros:
 * @param WINDOW** local_win
 *
 * Valor retornado:
 * @return Void. A função não retorna nada
 *
 * Assertiva de entrada:
 * WINDOW** local_win != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void destroyWin(WINDOW** local_win)
{
	werase(*local_win);
	wrefresh(*local_win);
	delwin(*local_win);
	*local_win = NULL;
}

/**
 **************************************************************************
 * @brief Função: Printa uma string em uma Janela
 *
 * Descrição:
 * A Função recebe uma janela, uma string e a cor e a posição  em que essa string deve ser escrita na janela.
 *
 * Parâmetros:
 * @param WINDOW* win - uma janela
 * @param int WinStarty - coordenada y que a string vai ficar
 * @param int WinStartx - coordenada x que a string vai ficar
 * @param int WinWidth - largura da janela
 * @param char* string - string que vai ser impressa na janela
 * @param chtype color - cor da string
 *
 * Valor retornado:
 * @return Void. A função somente imprime em uma janela
 *
 * Assertiva de entrada:
 * WINDOW* win != NULL
 * int WinStarty >= 0
 * int WinStartx >= 0
 * int WinWidth > 0
 * char* string != NULL
 *
 * Assertiva de saída:
 * Função Void
 ***************************************************************************/
void middlePrint(WINDOW* win, int WinStarty, int WinStartx, int WinWidth, char* string, chtype color)
{
    int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;

	getyx(win, y, x);

	if(WinStartx != 0)
		x = WinStartx;

	if(WinStarty != 0)
		y = WinStarty;

	if(WinWidth == 0)
		WinWidth = 80;

	length = strlen(string);
	temp = (WinWidth - length)/ 2;
	x = WinStartx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
}

/**
 **************************************************************************
 * @brief Função: Cria a Janela do Jogo
 *
 * Descrição:
 * A Função recebe a largura e a altura de uma janela e com esses valores ela aloca e cria essa janela. Então é habilitada o keypad nessa janela. No final essa janela formada é retornada.
 *
 * Parâmetros:
 * @param int win_y - largura da janela do jogo (número de colunas)
 * @param int win_x - altura da janela do jogo (número de linhas)
 *
 * Valor retornado:
 * @return WINDOW* gameWin - janela do jogo
 *
 * Assertiva de entrada:
 * int win_y > 0
 * int win_x > 0
 *
 * Assertiva de saída:
 * WINDOW* gameWin != NULL
 ***************************************************************************/
WINDOW* gameWindow(int win_y, int win_x)
{
    FILE* fp;
    WINDOW* gameWin;
    int x = win_x-2;
    int y = win_y-4;

    /* Create GameWindow */
    gameWin = createWin(y, x, 4, 0);
    keypad(gameWin, TRUE);
    curs_set(0);
    //box(gameWin, 0, 0);
    refreshGame();
    wrefresh(gameWin);

    /*Assertiva de saída*/
    if (gameWin == NULL) {
        fp = fopen("Relatório_Erros.txt", "a");
        fprintf(fp, "Erro na gameWindow (arquivo WinManager.c)\n");
        fclose(fp);
    }
    return gameWin;
}

/**
 **************************************************************************
 * @brief Função: Dá Refresh na Tela do jogo
 *
 * Descrição:
 * A Função recebe 2 janelas, a do jogo com o mapa e a janela de status do player e PC. Então ela atualiza e dá refresh na tela de acordo com o que aconteceu dentro do jogo.
 *
 * Parâmetros:
 * @param WINDOW* gameWin - janela do jogo, onde está o mapa
 * @param WINDOW* statusWin - janela com os status das tropas,prédios e base do player e do PC
 *
 * Valor retornado:
 * @return Void. A função apenas atualiza a tela
 *
 * Assertiva de entrada:
 * WINDOW* gameWin != NULL
 * WINDOW* statusWin != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void refreshWindows(WINDOW* gameWin, WINDOW* statusWin)
{
    refresh();
    wrefresh(gameWin);
    wrefresh(statusWin);
    wclear(statusWin);
    box(statusWin, 0, 0);
}

/**
 **************************************************************************
 * @brief Função: Printa os Status do Player
 *
 * Descrição:
 * A Função recebe uma janela e as structs da base, dos prédios e das tropas. Então ela printa na janela os status dessas structs, como HP, número de tropas e quantidade de recursos.
 *
 * Parâmetros:
 * @param WINDOW* status - janela dos status
 * @param Base* b - struct da base
 * @param Build* b1 - struct do prédio 1
 * @param Build* b2 - struct do prédio 2
 * @param Build* b3 - struct do prédio 3
 * @param Troop* t1 - struct da tropa 1
 * @param Troop* t2 - struct da tropa 2
 * @param Troop* t3 - struct da tropa 3
 *
 * Valor retornado:
 * @return Void. A função apenas printa os status
 *
 * Assertiva de entrada:
 * WINDOW* status != NULL
 * Base* b != NULL
 * Build* b1 != NULL
 * Build* b2 != NULL
 * Build* b3 != NULL
 * Troop* t1 != NULL
 * Troop* t2 != NULL
 * Troop* t3 != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void printPlayerStatus(WINDOW* status, Base* b, Build* b1, Build* b2, Build* b3, Troop* t1, Troop* t2, Troop* t3)
{
    wattron(status, COLOR_PAIR(2));
    mvwprintw(status, 1, 2, "HP B: %i + %i", b->hp, b->defense);
    mvwprintw(status, 2, 2, "HP X: %i + %i", b1->hp, b1->defense);
    mvwprintw(status, 4, 2, "HP Z: %i + %i", b2->hp, b2->defense);
    mvwprintw(status, 3, 2, "HP Y: %i + %i", b3->hp, b3->defense);

    mvwprintw(status, 1, termCols/10+8, "T1 Amount: %i", t1->amount);
    mvwprintw(status, 2, termCols/10+8, "T2 Amount: %i", t2->amount);
    mvwprintw(status, 3, termCols/10+8, "T3 Amount: %i", t3->amount);

    mvwprintw(status, 1, termCols/4+5, "Amount R1: %i", b->r1Amount);
    mvwprintw(status, 2, termCols/4+5, "Amount R2: %i", b->r2Amount);

    wattroff(status, COLOR_PAIR(2));
    mvwprintw(status, 4, termCols/4+5, "T%c Selected", troopSel);
}

/**
 **************************************************************************
 * @brief Função: Printa os Status do PC
 *
 * Descrição:
 * A Função recebe uma janela e as structs da base, dos prédios e das tropas. Então ela printa na janela os status dessas structs, como HP, número de tropas e quantidade de recursos.
 *
 * Parâmetros:
 * @param WINDOW* status - janela dos status
 * @param Base* b - struct da base
 * @param Build* b1 - struct do prédio 1
 * @param Build* b2 - struct do prédio 2
 * @param Build* b3 - struct do prédio 3
 * @param Troop* t1 - struct da tropa 1
 * @param Troop* t2 - struct da tropa 2
 * @param Troop* t3 - struct da tropa 3
 *
 * Valor retornado:
 * @return Void. A função apenas printa os status
 *
 * Assertiva de entrada:
 * WINDOW* status != NULL
 * Base* b != NULL
 * Build* b1 != NULL
 * Build* b2 != NULL
 * Build* b3 != NULL
 * Troop* t1 != NULL
 * Troop* t2 != NULL
 * Troop* t3 != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void printEnemyStatus(WINDOW* status, Base* b, Build* b1, Build* b2, Build* b3, Troop* t1, Troop* t2, Troop* t3)
{
    mvwprintw(status, 1, termCols/2-3, "|");
    mvwprintw(status, 2, termCols/2-3, "|");
    mvwprintw(status, 3, termCols/2-3, "|");
    mvwprintw(status, 4, termCols/2-3, "|");

    wattron(status, COLOR_PAIR(1));
    mvwprintw(status, 1, termCols/2+3, "HP C: %i + %i", b->hp, b->defense);
    mvwprintw(status, 2, termCols/2+3, "HP L: %i + %i", b1->hp, b1->defense);
    mvwprintw(status, 4, termCols/2+3, "HP N: %i + %i", b2->hp, b2->defense);
    mvwprintw(status, 3, termCols/2+3, "HP M: %i + %i", b3->hp, b3->defense);

    mvwprintw(status, 1, termCols/2+25, "T7 Amount: %i", t1->amount);
    mvwprintw(status, 2, termCols/2+25, "T8 Amount: %i", t2->amount);
    mvwprintw(status, 3, termCols/2+25, "T9 Amount: %i", t3->amount);

    mvwprintw(status, 1, termCols-25, "Amount R1: %i", b->r1Amount);
    mvwprintw(status, 2, termCols-25, "Amount R2: %i", b->r2Amount);
    wattroff(status, COLOR_PAIR(1));
}

/**
 **************************************************************************
 * @brief Função: Iniciar, printar e controlar o Menu de Pause
 *
 * Descrição:
 * A Função inicializa os itens do menu de pause, inicializa o menu, cria a janela do menu sobre a janela do jogo, printa o menu e as bordas com as suas cores. Então ela espera o usuário escolher um dos itens e dar "enter" . Depois a função destrói o menu e retorna o valor do item selecionado.
 *
 * Parâmetros:
 * @param sem parâmetros
 *
 * Valor retornado:
 * @return (long int)itemPtr - valor do item selecionado pelo player. Dependendo da opção selecionada, a variável possui um valor. Podendo ser:
 0 - New Game
 1 - Load Game
 2 - Credits
 3 - Exit
 *
 * Assertiva de entrada:
 * sem parâmetros
 *
 * Assertiva de saída:
 * (long int)itemPtr == 0 || itemPtr == 1 || itemPtr == 2
 ***************************************************************************/
int pauseGameMenu()
{
    FILE* fp;
    char* choices[] = { "Continue", "Save Game", "Exit Game" };
    ITEM** items;
    ITEM* cur_item;
	int n_choices, sel = 0;
	long int i;
	void* itemPtr;
	MENU* menu;
	WINDOW* pauseWin;
	MEVENT evento_mouse;

    /* Initialize items to the menu */
	n_choices = ARRAY_SIZE(choices);
    items = (ITEM **)calloc(n_choices + 1, sizeof(ITEM *));
    for(i = 0; i < n_choices; ++i)
    {
        items[i] = new_item(choices[i], NULL);
        set_item_userptr(items[i], (void*)i);
    }
	items[n_choices] = (ITEM *)NULL;

	/* Initiate menu */
	menu = new_menu((ITEM**)items);

    /* Create window for Menu */
    pauseWin = createWin(10, 40, (termLines/3), (termCols/3));
    set_menu_win(menu, pauseWin);
    set_menu_sub(menu, derwin(pauseWin, 0, 0, 4, 13));
    set_menu_mark(menu, "- ");

    /* Print window and border*/
    box(pauseWin, 0, 0);
    middlePrint(pauseWin, 1, 0, 40, "GAME PAUSED", COLOR_PAIR(1));
    mvwaddch(pauseWin, 2, 0, ACS_LTEE);
	mvwhline(pauseWin, 2, 1, ACS_HLINE, 38);
	mvwaddch(pauseWin, 2, 39, ACS_RTEE);
    wrefresh(pauseWin);

	/* Setting grounds (fore and back) for the menu */
	set_menu_fore(menu, COLOR_PAIR(1)); //EDITAR CORES
	set_menu_back(menu, COLOR_PAIR(2)); //EDITAR CORES
	set_menu_grey(menu, COLOR_PAIR(3)); //EDITAR CORES

	/* Printing the menu */
	post_menu(menu);
	wrefresh(pauseWin);

	while(!sel)
	{
	    flushinp();
        switch(wgetch(pauseWin))
        {
            case KEY_DOWN:
                menu_driver(menu, REQ_DOWN_ITEM);
                break;

            case KEY_UP:
                menu_driver(menu, REQ_UP_ITEM);
                break;

            case 10:
                cur_item = current_item(menu);
                itemPtr = item_userptr(cur_item);
                sel = 1;
                break;
            case KEY_MOUSE:
                getmouse(&evento_mouse);
                if (evento_mouse.bstate & REPORT_MOUSE_POSITION) {
                    i = getMenu(evento_mouse.x , evento_mouse.y);
                    switch (i) {
                        case 1:
                            menu_driver(menu, REQ_FIRST_ITEM);
                            break;
                        case 2:
                            menu_driver(menu, REQ_FIRST_ITEM);
                            menu_driver(menu, REQ_DOWN_ITEM);
                            break;
                        case 3:
                            menu_driver(menu, REQ_LAST_ITEM);
                            menu_driver(menu, REQ_UP_ITEM);
                            break;
                        case 4:
                            menu_driver(menu, REQ_LAST_ITEM);
                            break;
                        default:
                            break;
                    }
                }
                if (evento_mouse.bstate & BUTTON1_CLICKED) {
                    sel = getMenu(evento_mouse.x, evento_mouse.y);
                    switch (sel) {
                        case 1:
                            menu_driver(menu, REQ_FIRST_ITEM);
                            cur_item = current_item(menu);
                            itemPtr = item_userptr(cur_item);
                            break;
                        case 2:
                            menu_driver(menu, REQ_FIRST_ITEM);
                            menu_driver(menu, REQ_DOWN_ITEM);
                            cur_item = current_item(menu);
                            itemPtr = item_userptr(cur_item);
                            break;
                        case 3:
                            menu_driver(menu, REQ_LAST_ITEM);
                            menu_driver(menu, REQ_UP_ITEM);
                            cur_item = current_item(menu);
                            itemPtr = item_userptr(cur_item);
                            break;
                        case 4:
                            menu_driver(menu, REQ_LAST_ITEM);
                            cur_item = current_item(menu);
                            itemPtr = item_userptr(cur_item);
                            break;
                        default:
                            break;
                    }
                }
                break;

        }
        wrefresh(pauseWin);
	}

	unpost_menu(menu);
    free_menu(menu);
	for(i = 0; i < n_choices; ++i)
		free_item(items[i]);

    destroyWin(&pauseWin);

    /*Assertiva de saída*/
    if ((long int)itemPtr != 0 && (long int)itemPtr != 1 && (long int)itemPtr != 2) {
        fp = fopen("Relatório_Erros.txt", "a");
        fprintf(fp, "Erro na escolha de item na pauseGameMenu (arquivo WinManager.c)\n");
        fclose(fp);
    }
    return (long int)itemPtr;
}

/**
 **************************************************************************
 * @brief Função: Monta e Printa uma Janela do Fim do Jogo
 *
 * Descrição:
 * A Função recebe as 2 structs da base (do player e do PC) e então verifica qual das duas bases tem o HP igual a 0. Se for do player é mostrada uma tela dizendo que o jogador perdeu o jogo. Se for do PC é mostrada uma tela dizendo que o jogador ganhou o jogo.
 *
 * Parâmetros:
 * @param Base* b_p - struct da base do player
 * @param Base* b_e - struct da base do PC
 *
 * Valor retornado:
 * @return Void. A função apenas printa uma janela com uma mensagem
 *
 * Assertiva de entrada:
 * Base* b_p != NULL
 * Base* b_e != NULL
 *
 * Assertiva de saída:
 * Função void
 ***************************************************************************/
void gameEnd(Base* b_p, Base* b_e)
{
    WINDOW* win;

    win = createWin(10, 70, termLines/3, termCols/4);
    box(win, 0, 0);

    if(b_p->hp <= 0)
    {
        middlePrint(win, 2, 0, 70, "OH NO!", COLOR_PAIR(1));
        middlePrint(win, 4, 0, 70, "YOU LOST THE BATTLE!!", COLOR_PAIR(1));
    }

    else if(b_e->hp <= 0)
    {
        middlePrint(win, 2, 0, 70, "OH YEAH!", COLOR_PAIR(2));
        middlePrint(win, 4, 0, 70, "YOU WON THE BATTLE!!", COLOR_PAIR(2));
    }

    wrefresh(win);
    sleep(3);
    destroyWin(&win);
}
