#include "WinManager.h"
#include "CUnit/Basic.h"

/**Teste para verificar se o mapa aloca de forma correta*/
void testALLOCMAP(void);

/**Teste para verificar se o mapa desaloca de forma correta*/
void testDEALLOCMAP(void);

/** Teste para verificar se a base é colocada de forma correta no mapa*/
void testSETBASEONMAP(void);

/**Teste para verificar se os prédios são colocados de forma correta no mapa*/
void testSETBUILDONMAP(void);

/**Teste para verificar se as tropas são colocadas de forma correta no mapa*/
void testSETTROOPONMAP(void);

/**Teste para verificar se o mapa é preenchido corretamente e não possui nenhum espaço == NULL*/
void testSETMAP(void);

/**Teste para verificar se a Base é inicializada corretamente*/
void testSETBASEATT(void);

/**Teste para verificar se os Builds são inicializados corretamente*/
void testSETBUILDATT(void);

/**Teste para verificar se as Tropas são inicializadas corretamente*/
void testSETTROOPATT(void);

/**Teste para verificar se a tropa identifica quando atacar e quando está do lado de um prédio que aumenta tropas*/
void testTROOPCHECKER(void);

/**Teste para verificar se a tropa é gerada de forma certa*/
void testTROOPCONTROLLER(void);

/**Teste para verificar se os prédios são destruídos corretamente quando a vida deles chega a zero*/
void testBUILDHPCHECKER(void);

/** Teste para verificar se as tropas somem quando a vida delas chega a zero*/
void testTROOPAMOUNTCHECKER(void);

/**Teste para verificar se as batalhas entre tropas funciona como o esperado*/
void testBATTLECHECKER(void);

/**Teste para verificar se as tropas atacam da forma esperada a base e os prédios inimigos*/
void testDESTROYBUILDCHECKER(void);

/**Teste para verificar se o jogo lê o save de forma correta*/
void testLOADGAME(void);

/**Teste para verificar se a tropa do PC identifica quando atacar e quando está do lado de um prédio que aumenta tropas*/
void testENEMYTROOPCHECKER(void);

/**Teste para verificar se a tropa do PC é gerada de forma certa*/
void testENEMYTROOPCONTROLLER(void);

/**Teste para verificar se as tropas do PC atacam da forma esperada a base e os prédios do player*/
void testENEMYHITCONTROL(void);

/** Pointer to the file used by the tests. */
static FILE* temp_file = NULL;

/** The suite initialization function.
 * Opens the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int init_suite1(void)
{
    if (NULL == (temp_file = fopen("temp.txt", "w+"))) {
        return -1;
    }
    else {
        return 0;
    }
}

/** The suite cleanup function.
 * Closes the temporary file used by the tests.
 * Returns zero on success, non-zero otherwise.
 */
int clean_suite1(void)
{
    if (0 != fclose(temp_file)) {
        return -1;
    }
    else {
        temp_file = NULL;
        return 0;
    }
}

int main()
{
    CU_pSuite pSuite = NULL;

    /* initialize the CUnit test registry */
    if (CUE_SUCCESS != CU_initialize_registry())
        return CU_get_error();
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("PlayerFunc", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of setBaseAtt()", testSETBASEATT))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of setBuildAtt()", testSETBUILDATT))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of setTroopAtt()", testSETTROOPATT))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of troopChecker()", testTROOPCHECKER))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of troopController()", testTROOPCONTROLLER))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of buildHPChecker()", testBUILDHPCHECKER))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of troopAmountChecker()", testTROOPAMOUNTCHECKER))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of battleChecker()", testBATTLECHECKER))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of destroyBuildChecker()", testDESTROYBUILDCHECKER))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("MapFunc", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of allocMap()", testALLOCMAP))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of deallocMap()", testDEALLOCMAP))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of setBaseOnMap()", testSETBASEONMAP))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of setBuildOnMap()", testSETBUILDONMAP))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of setTroopOnMap()", testSETTROOPONMAP))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of setMap()", testSETMAP))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("GameLogic", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of loadGame()", testSETMAP))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* add a suite to the registry */
    pSuite = CU_add_suite("EnemyFunc", init_suite1, clean_suite1);
    if (NULL == pSuite) {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of enemyTroopChecker()", testENEMYTROOPCHECKER))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of enemyTroopController()", testENEMYTROOPCONTROLLER))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    if (NULL == CU_add_test(pSuite, "test of enemyHitControl()", testENEMYHITCONTROL))
    {
        CU_cleanup_registry();
        return CU_get_error();
    }
    
    /* Run all tests using the CUnit Basic interface */
    CU_basic_set_mode(CU_BRM_VERBOSE);
    CU_basic_run_tests();
    CU_cleanup_registry();
    remove("temp.txt");
    return CU_get_error();
}

void testALLOCMAP(void){
    char** map = NULL;
    
    map = allocMap(map,27,23);
    CU_ASSERT_NOT_EQUAL(map, 0);
}

void testDEALLOCMAP(void){
    char** map = NULL;
    
    map = allocMap(map,27,23);
    map = deallocMap(map);
    CU_ASSERT_EQUAL(map, NULL);
}

void testSETBASEONMAP(void){
    char** map = NULL;
    int i,j;
    
    map = allocMap(map,107,103);
    setBaseOnMap(map,&Base_p,50,50,2,2,0,0);
    
    for(i = Base_p.y; i<=(Base_p.height+Base_p.y); i++){
        for(j = Base_p.x; j<=(Base_p.width+Base_p.x); j++){
            CU_ASSERT_EQUAL(map[i][j],'B');
        }
    }
    
    setBaseOnMap(map,&Base_p,50,50,2,2,1,0);
    for(i = Base_p.y; i<=(Base_p.height+Base_p.y); i++){
        for(j = Base_p.x; j<=(Base_p.width+Base_p.x); j++){
            CU_ASSERT_EQUAL(map[i][j],'C');
        }
    }
    map = deallocMap(map);
}

void testSETBUILDONMAP(void){
    char** map = NULL;
    int i,j;
    
    map = allocMap(map,107,103);
    setBuildOnMap(map, &B1_p,50,50,2,2,0,0,0);
    
    for(i = B1_p.y; i<=(B1_p.height+B1_p.y); i++){
        for(j = B1_p.x; j<=(B1_p.width+B1_p.x); j++){
            CU_ASSERT_EQUAL(map[i][j],'X');
        }
    }
    
    setBuildOnMap(map, &B1_p,50,50,2,2,1,0,0);
    
    for(i = B1_p.y; i<=(B1_p.height+B1_p.y); i++){
        for(j = B1_p.x; j<=(B1_p.width+B1_p.x); j++){
            CU_ASSERT_EQUAL(map[i][j],'Y');
        }
    }
    
    setBuildOnMap(map, &B1_p,50,50,2,2,2,0,0);
    
    for(i = B1_p.y; i<=(B1_p.height+B1_p.y); i++){
        for(j = B1_p.x; j<=(B1_p.width+B1_p.x); j++){
            CU_ASSERT_EQUAL(map[i][j],'Z');
        }
    }
    
    setBuildOnMap(map, &B1_p,50,50,2,2,0,1,0);
    
    for(i = B1_p.y; i<=(B1_p.height+B1_p.y); i++){
        for(j = B1_p.x; j<=(B1_p.width+B1_p.x); j++){
            CU_ASSERT_EQUAL(map[i][j],'L');
        }
    }
    
    setBuildOnMap(map, &B1_p,50,50,2,2,1,1,0);
    
    for(i = B1_p.y; i<=(B1_p.height+B1_p.y); i++){
        for(j = B1_p.x; j<=(B1_p.width+B1_p.x); j++){
            CU_ASSERT_EQUAL(map[i][j],'M');
        }
    }
    
    setBuildOnMap(map, &B1_p,50,50,2,2,2,1,0);
    
    for(i = B1_p.y; i<=(B1_p.height+B1_p.y); i++){
        for(j = B1_p.x; j<=(B1_p.width+B1_p.x); j++){
            CU_ASSERT_EQUAL(map[i][j],'N');
        }
    }
    map = deallocMap(map);
}

void testSETTROOPONMAP(void){
    char** map = NULL;
    
    map = allocMap(map,107,103);
    
    setTroopOnMap(map,&T1_p,50,50,0,0,0);
    CU_ASSERT_EQUAL(map[50][50],'1');
    
    setTroopOnMap(map,&T1_p,50,50,1,0,0);
    CU_ASSERT_EQUAL(map[50][50],'2');
    
    setTroopOnMap(map,&T1_p,50,50,2,0,0);
    CU_ASSERT_EQUAL(map[50][50],'3');
    
    setTroopOnMap(map,&T1_p,50,50,0,1,0);
    CU_ASSERT_EQUAL(map[50][50],'7');
    
    setTroopOnMap(map,&T1_p,50,50,1,1,0);
    CU_ASSERT_EQUAL(map[50][50],'8');
    
    setTroopOnMap(map,&T1_p,50,50,2,1,0);
    CU_ASSERT_EQUAL(map[50][50],'9');
    
    map = deallocMap(map);
}

void testSETMAP(void){
    char** map = NULL;
    int i,j;
    
    map = allocMap(map,55,181);
    
    setMap(map,0);
    for (i=0; i<48; i++) {
        for (j=0; j<178; j++) {
            CU_ASSERT_NOT_EQUAL(&map[i][j],NULL);
        }
    }
    map = deallocMap(map);
}

void testSETBASEATT(void){
    
    Base_p = *setBaseAtt(&Base_p,2,3,4,5);
    CU_ASSERT_EQUAL(Base_p.x,2);
    CU_ASSERT_EQUAL(Base_p.y,3);
    CU_ASSERT_EQUAL(Base_p.height,4);
    CU_ASSERT_EQUAL(Base_p.width,5);
    CU_ASSERT_EQUAL(Base_p.r1Amount,100);
    CU_ASSERT_EQUAL(Base_p.r2Amount,100);
    CU_ASSERT_EQUAL(Base_p.defense,1000);
    CU_ASSERT_EQUAL(Base_p.hp,5000);
}

void testSETBUILDATT(void){
    
    B1_p = *setBuildAtt(&B1_p,2,3,4,5,0);
    
    CU_ASSERT_EQUAL(B1_p.x,2);
    CU_ASSERT_EQUAL(B1_p.y,3);
    CU_ASSERT_EQUAL(B1_p.height,5);
    CU_ASSERT_EQUAL(B1_p.width,4);
    
    CU_ASSERT_EQUAL(B1_p.defense,500);
    CU_ASSERT_EQUAL(B1_p.mineSpeed,150);
    CU_ASSERT_EQUAL(B1_p.resourceConsume,0);
    CU_ASSERT_EQUAL(B1_p.hp,1000);
    
    B1_p = *setBuildAtt(&B1_p,2,3,4,5,1);
    
    CU_ASSERT_EQUAL(B1_p.defense,500);
    CU_ASSERT_EQUAL(B1_p.mineSpeed,120);
    CU_ASSERT_EQUAL(B1_p.resourceConsume,0);
    CU_ASSERT_EQUAL(B1_p.hp,1200);
    
    B1_p = *setBuildAtt(&B1_p,2,3,4,5,2);
    
    CU_ASSERT_EQUAL(B1_p.defense,700);
    CU_ASSERT_EQUAL(B1_p.mineSpeed,100);
    CU_ASSERT_EQUAL(B1_p.resourceConsume,100);
    CU_ASSERT_EQUAL(B1_p.hp,1300);
}

void testSETTROOPATT(void){
    
    T1_p = *setTroopAtt(&T1_p,2,3,0);
    
    CU_ASSERT_EQUAL(T1_p.x,2);
    CU_ASSERT_EQUAL(T1_p.y,3);
    
    CU_ASSERT_EQUAL(T1_p.amount,100);
    CU_ASSERT_EQUAL(T1_p.damage,40);
    CU_ASSERT_EQUAL(T1_p.defense,30);
    CU_ASSERT_EQUAL(T1_p.hp,80);
    
    T1_p = *setTroopAtt(&T1_p,2,3,1);
    
    CU_ASSERT_EQUAL(T1_p.amount,80);
    CU_ASSERT_EQUAL(T1_p.damage,60);
    CU_ASSERT_EQUAL(T1_p.defense,40);
    CU_ASSERT_EQUAL(T1_p.hp,90);
    
    T1_p = *setTroopAtt(&T1_p,2,3,2);
    
    CU_ASSERT_EQUAL(T1_p.amount,40);
    CU_ASSERT_EQUAL(T1_p.damage,100);
    CU_ASSERT_EQUAL(T1_p.defense,70);
    CU_ASSERT_EQUAL(T1_p.hp,70);
}

void testTROOPCHECKER(void){
    
    int i, j;
    
    map1 = allocMap(map1,107,103);
    
    for (i = 0; i< 100; i++) {
        for (j = 0; j < 100; j++) {
            map1[i][j] = MAP_TILE;
        }
    }
    
    setTroopOnMap(map1, &T1_p, 50, 50, 1, 0, 0);
    i = troopChecker(&T1_p, 0);
    CU_ASSERT_EQUAL(i, 0);
    
    setBuildOnMap(map1, &B1_p, 50, 51, 2, 2, 1, 0, 0);
    i = troopChecker(&T1_p, 0);
    CU_ASSERT_EQUAL(i, 1);
    
    setTroopOnMap(map1, &T1_e, 50, 51, 0, 1, 0);
    i = troopChecker(&T1_p, 1);
    CU_ASSERT_EQUAL(i, 7);
    
    setTroopOnMap(map1, &T1_e, 50, 51, 1, 1, 0);
    i = troopChecker(&T1_p, 1);
    CU_ASSERT_EQUAL(i, 8);
    
    setTroopOnMap(map1, &T1_e, 50, 51, 2, 1, 0);
    i = troopChecker(&T1_p, 1);
    CU_ASSERT_EQUAL(i, 9);
    
    setBaseOnMap(map1, &Base_e, 50, 51, 2, 2, 1, 0);
    i = troopChecker(&T1_p, 1);
    CU_ASSERT_EQUAL(i, 10);
    
    setBuildOnMap(map1, &B1_e, 50, 51, 2, 2, 0, 1, 0);
    i = troopChecker(&T1_p, 1);
    CU_ASSERT_EQUAL(i, 11);
    
    setBuildOnMap(map1, &B1_e, 50, 51, 2, 2, 1, 1, 0);
    i = troopChecker(&T1_p, 1);
    CU_ASSERT_EQUAL(i, 12);
    
    setBuildOnMap(map1, &B1_e, 50, 51, 2, 2, 2, 1, 0);
    i = troopChecker(&T1_p, 1);
    CU_ASSERT_EQUAL(i, 13);
    
    map1 = deallocMap(map1);
}

void testTROOPCONTROLLER(void){
    
    int t1amount, t2amount, t3amount, r1amount, r2amount;
    map1 = allocMap(map1,107,103);
    setMap(map1, 0);
    
    setTroopOnMap(map1, &T1_p, 5, (map_y/2)+5, 0, 0, 0);
    setTroopOnMap(map1, &T2_p, 5, (map_y/2)+6, 1, 0, 0);
    setTroopOnMap(map1, &T3_p, 5, (map_y/2)+7, 2, 0, 0);
    
    t1amount = T1_p.amount;
    t2amount = T2_p.amount;
    t3amount = T3_p.amount;
    r1amount = Base_p.r1Amount;
    r2amount = Base_p.r2Amount;
    
    troopController(&T1_p, &T2_p, &T3_p, &B1_p, &Base_p);
    
    CU_ASSERT_NOT_EQUAL(t1amount, T1_p.amount);
    CU_ASSERT_NOT_EQUAL(t2amount, T2_p.amount);
    CU_ASSERT_NOT_EQUAL(t3amount, T3_p.amount);
    CU_ASSERT_EQUAL(r1amount, Base_p.r1Amount);
    CU_ASSERT_EQUAL(r2amount, Base_p.r2Amount);
    
    map1 = deallocMap(map1);
}

void testBUILDHPCHECKER(void){
    
    int i,j;
    
    map1 = allocMap(map1,107,103);
    setMap(map1, 0);
    
    B1_p.hp = 0;
    B2_p.hp = 0;
    B3_p.hp = 0;
    
    buildHPChecker(&B1_p, &B2_p, &B3_p, map1);
    
    CU_ASSERT_EQUAL(B1_p.hp, -1);
    CU_ASSERT_EQUAL(B2_p.hp, -1);
    CU_ASSERT_EQUAL(B3_p.hp, -1);
    
    for(i = B1_p.y; i<=(B1_p.height+B1_p.y); i++)
        for(j = B1_p.x; j<=(B1_p.width+B1_p.x); j++)
            CU_ASSERT_EQUAL(map1[i][j], MAP_TILE);
    
    for(i = B2_p.y; i<=(B2_p.height+B2_p.y); i++)
        for(j = B2_p.x; j<=(B2_p.width+B2_p.x); j++)
            CU_ASSERT_EQUAL(map1[i][j], MAP_TILE);
    
    for(i = B3_p.y; i<=(B3_p.height+B3_p.y); i++)
        for(j = B3_p.x; j<=(B3_p.width+B3_p.x); j++)
            CU_ASSERT_EQUAL(map1[i][j], MAP_TILE);
    
    map1 = deallocMap(map1);
}

void testTROOPAMOUNTCHECKER(void){
    
    int y[3],x[3], i;
    
    map1 = allocMap(map1,107,103);
    setMap(map1,0);
    
    T1_p.amount = -5;
    T2_p.amount = -5;
    T3_p.amount = -5;
    y[0] = T1_p.y;
    x[0] = T1_p.x;
    y[1] = T2_p.y;
    x[1] = T2_p.x;
    y[2] = T3_p.y;
    x[2] = T3_p.x;
    
    troopAmountChecker(&T1_p, &T2_p, &T3_p, map1);
    
    for (i = 0; i < 3; i++)
        CU_ASSERT_EQUAL(map1[i][i], MAP_TILE);
    
    CU_ASSERT_EQUAL(T1_p.amount, 0)
    CU_ASSERT_EQUAL(T2_p.amount, 0)
    CU_ASSERT_EQUAL(T3_p.amount, 0)
    
    CU_ASSERT_EQUAL(T1_p.y, 0);
    CU_ASSERT_EQUAL(T1_p.x, 0);
    CU_ASSERT_EQUAL(T2_p.y, 0);
    CU_ASSERT_EQUAL(T2_p.x, 0);
    CU_ASSERT_EQUAL(T3_p.y, 0);
    CU_ASSERT_EQUAL(T3_p.x, 0);
    
    map1 = deallocMap(map1);
}

void testBATTLECHECKER(void){
    
    int amount;
    
    map1 = allocMap(map1,107,103);
    setMap(map1,0);
    
    setTroopOnMap(map1, &T1_p, map_x-19,(map_y/2), 0, 0, 0);
    amount = T2_e.amount;
    battleChecker(&T1_p, &T1_e, &T2_e, &T3_e);
    CU_ASSERT_EQUAL(T2_e.amount, amount);
    
    setTroopOnMap(map1, &T3_p, map_x-19,(map_y/2), 2, 0, 0);
    amount = T2_e.amount;
    battleChecker(&T3_p, &T1_e, &T2_e, &T3_e);
    CU_ASSERT_NOT_EQUAL(T2_e.amount, amount);
    
    setTroopOnMap(map1, &T2_p, map_x-19, (map_y/2)-2, 1, 0, 0);
    amount = T2_p.amount;
    battleChecker(&T2_p, &T1_e, &T2_e, &T3_e);
    CU_ASSERT_EQUAL(T2_p.amount, amount);
    
    setTroopOnMap(map1, &T2_p, map_x-19, (map_y/2)+2, 1, 0, 0);
    amount = T2_p.amount;
    battleChecker(&T2_p, &T1_e, &T2_e, &T3_e);
    CU_ASSERT_NOT_EQUAL(T2_p.amount, amount);
    
    map1 = deallocMap(map1);
}

void testDESTROYBUILDCHECKER(void){
    
    int defense, hp;
    
    map1 = allocMap(map1, 107,103);
    setMap(map1,0);
    
    setTroopOnMap(map1, &T1_p, map_x-6, (map_y/2)-8, 0, 0, 0);
    defense = B1_e.defense;
    destroyBuildChecker(&T1_p, &Base_e, &B1_e, &B2_e, &B3_e);
    CU_ASSERT_EQUAL((defense - T1_p.damage), B1_e.defense);
    
    B1_e.defense = 0;
    hp = B1_e.hp;
    destroyBuildChecker(&T1_p, &Base_e, &B1_e, &B2_e, &B3_e);
    CU_ASSERT_EQUAL((hp - T1_p.damage), B1_e.hp);
    
    setTroopOnMap(map1, &T1_p, map_x-6, (map_y/2)+5, 0, 0, 0);
    defense = B2_e.defense;
    destroyBuildChecker(&T1_p, &Base_e, &B1_e, &B2_e, &B3_e);
    CU_ASSERT_EQUAL((defense - T1_p.damage), B2_e.defense);
    
    B2_e.defense = 0;
    hp = B2_e.hp;
    destroyBuildChecker(&T1_p, &Base_e, &B1_e, &B2_e, &B3_e);
    CU_ASSERT_EQUAL((hp - T1_p.damage), B2_e.hp);
    
    setTroopOnMap(map1, &T1_p, map_x-17, (map_y/2)-1, 0, 0, 0);
    defense = B3_e.defense;
    destroyBuildChecker(&T1_p, &Base_e, &B1_e, &B2_e, &B3_e);
    CU_ASSERT_EQUAL((defense - T1_p.damage), B3_e.defense);
    
    B3_e.defense = 0;
    hp = B3_e.hp;
    destroyBuildChecker(&T1_p, &Base_e, &B1_e, &B2_e, &B3_e);
    CU_ASSERT_EQUAL((hp - T1_p.damage), B3_e.hp);
    
    setTroopOnMap(map1, &T1_p, map_x-10, (map_y/2)-3, 0, 0, 0);
    defense = Base_e.defense;
    destroyBuildChecker(&T1_p, &Base_e, &B1_e, &B2_e, &B3_e);
    CU_ASSERT_EQUAL((defense - T1_p.damage), Base_e.defense);
    
    Base_e.defense = 0;
    hp = Base_e.hp;
    destroyBuildChecker(&T1_p, &Base_e, &B1_e, &B2_e, &B3_e);
    CU_ASSERT_EQUAL((hp - T1_p.damage), Base_e.hp);
    
    map1 = deallocMap(map1);
}

void testLOADGAME(void){
    
    map1 = allocMap(map1, 107, 103);
    setMap(map1, 0);
    saveGame();
    map1 = deallocMap(map1);
    loadGame();
    
    CU_ASSERT_EQUAL(Base_p.r1Amount, 100);
    CU_ASSERT_EQUAL(Base_p.r2Amount, 100);
    CU_ASSERT_EQUAL(Base_p.defense, 1000);
    CU_ASSERT_EQUAL(Base_p.hp, 5000);
    
    CU_ASSERT_EQUAL(B1_p.defense, 500);
    CU_ASSERT_EQUAL(B1_p.mineSpeed, 150);
    CU_ASSERT_EQUAL(B1_p.resourceConsume, 0);
    CU_ASSERT_EQUAL(B1_p.hp, 1000);
    
    CU_ASSERT_EQUAL(B2_p.defense, 500);
    CU_ASSERT_EQUAL(B2_p.mineSpeed, 120);
    CU_ASSERT_EQUAL(B2_p.resourceConsume, 0);
    CU_ASSERT_EQUAL(B2_p.hp, 1200);
    
    CU_ASSERT_EQUAL(B3_p.defense, 500);
    CU_ASSERT_EQUAL(B3_p.mineSpeed, 120);
    CU_ASSERT_EQUAL(B3_p.resourceConsume, 0);
    CU_ASSERT_EQUAL(B3_p.hp, 1300);
    
    CU_ASSERT_EQUAL(T1_p.amount, 100);
    CU_ASSERT_EQUAL(T1_p.damage, 60);
    CU_ASSERT_EQUAL(T1_p.defense, 30);
    CU_ASSERT_EQUAL(T1_p.hp, 80);
    
    CU_ASSERT_EQUAL(T2_p.amount, 80);
    CU_ASSERT_EQUAL(T2_p.damage, 50);
    CU_ASSERT_EQUAL(T2_p.defense, 50);
    CU_ASSERT_EQUAL(T2_p.hp, 100);
    
    CU_ASSERT_EQUAL(T3_p.amount, 40);
    CU_ASSERT_EQUAL(T3_p.damage, 80);
    CU_ASSERT_EQUAL(T3_p.defense, 70);
    CU_ASSERT_EQUAL(T3_p.hp, 70);
    
    CU_ASSERT_EQUAL(Base_e.r1Amount, 100);
    CU_ASSERT_EQUAL(Base_e.r2Amount, 100);
    CU_ASSERT_EQUAL(Base_e.defense, 1000);
    CU_ASSERT_EQUAL(Base_e.hp, 5000);
    
    CU_ASSERT_EQUAL(B1_e.defense, 500);
    CU_ASSERT_EQUAL(B1_e.mineSpeed, 150);
    CU_ASSERT_EQUAL(B1_e.resourceConsume, 0);
    CU_ASSERT_EQUAL(B1_e.hp, 1000);
    
    CU_ASSERT_EQUAL(B2_e.defense, 500);
    CU_ASSERT_EQUAL(B2_e.mineSpeed, 120);
    CU_ASSERT_EQUAL(B2_e.resourceConsume, 0);
    CU_ASSERT_EQUAL(B2_e.hp, 1200);
    
    CU_ASSERT_EQUAL(B3_e.defense, 500);
    CU_ASSERT_EQUAL(B3_e.mineSpeed, 120);
    CU_ASSERT_EQUAL(B3_e.resourceConsume, 0);
    CU_ASSERT_EQUAL(B3_e.hp, 1300);
    
    CU_ASSERT_EQUAL(T1_e.amount, 100);
    CU_ASSERT_EQUAL(T1_e.damage, 60);
    CU_ASSERT_EQUAL(T1_e.defense, 30);
    CU_ASSERT_EQUAL(T1_e.hp, 80);
    
    CU_ASSERT_EQUAL(T2_e.amount, 80);
    CU_ASSERT_EQUAL(T2_e.damage, 50);
    CU_ASSERT_EQUAL(T2_e.defense, 50);
    CU_ASSERT_EQUAL(T2_e.hp, 100);
    
    CU_ASSERT_EQUAL(T3_e.amount, 40);
    CU_ASSERT_EQUAL(T3_e.damage, 80);
    CU_ASSERT_EQUAL(T3_e.defense, 70);
    CU_ASSERT_EQUAL(T3_e.hp, 70);
    
    remove("save.bin");
}

void testENEMYTROOPCHECKER(void){
    int i, j;
    
    map1 = allocMap(map1,107,103);
    
    for (i = 0; i< 100; i++) {
        for (j = 0; j < 100; j++) {
            map1[i][j] = MAP_TILE;
        }
    }
    
    setTroopOnMap(map1, &T1_e, 50, 50, 1, 1, 0);
    i = enemyTroopChecker(&T1_e, 0);
    CU_ASSERT_EQUAL(i, 0);
    
    setBuildOnMap(map1, &B1_e, 50, 51, 2, 2, 1, 1, 0);
    i = enemyTroopChecker(&T1_e, 0);
    CU_ASSERT_EQUAL(i, 1);
    
    setBaseOnMap(map1, &Base_p, 50, 51, 2, 2, 0, 0);
    i = enemyTroopChecker(&T1_e, 1);
    CU_ASSERT_EQUAL(i, 4);
    
    setBuildOnMap(map1, &B1_p, 50, 51, 2, 2, 0, 0, 0);
    i = enemyTroopChecker(&T1_e, 1);
    CU_ASSERT_EQUAL(i, 5);
    
    setBuildOnMap(map1, &B1_p, 50, 51, 2, 2, 1, 0, 0);
    i = enemyTroopChecker(&T1_e, 1);
    CU_ASSERT_EQUAL(i, 6);
    
    setBuildOnMap(map1, &B1_p, 50, 51, 2, 2, 2, 0, 0);
    i = enemyTroopChecker(&T1_e, 1);
    CU_ASSERT_EQUAL(i, 7);
    
    map1 = deallocMap(map1);
}

void testENEMYTROOPCONTROLLER(void){
    
    int t1amount, t2amount, t3amount, r1amount, r2amount;
    map1 = allocMap(map1,107,103);
    setMap(map1, 0);
    
    setTroopOnMap(map1, &T1_e, map_x-6, (map_y/2)+5, 0, 1, 0);
    setTroopOnMap(map1, &T2_e, map_x-6, (map_y/2)+6, 1, 1, 0);
    setTroopOnMap(map1, &T3_e, map_x-6, (map_y/2)+7, 2, 1, 0);
    
    t1amount = T1_e.amount;
    t2amount = T2_e.amount;
    t3amount = T3_e.amount;
    r1amount = Base_e.r1Amount;
    r2amount = Base_e.r2Amount;
    
    enemyTroopController(&T1_e, &T2_e, &T3_e, &B2_e, &Base_e);
    
    CU_ASSERT_NOT_EQUAL(t1amount, T1_e.amount);
    CU_ASSERT_NOT_EQUAL(t2amount, T2_e.amount);
    CU_ASSERT_NOT_EQUAL(t3amount, T3_e.amount);
    CU_ASSERT_EQUAL(r1amount, Base_e.r1Amount);
    CU_ASSERT_EQUAL(r2amount, Base_e.r2Amount);
    
    map1 = deallocMap(map1);
}

void testENEMYHITCONTROL(void){
    int defense, hp;
    
    map1 = allocMap(map1, 107,103);
    setMap(map1,0);
    
    setTroopOnMap(map1, &T1_e, 5, (map_y/2)-8, 0, 1, 0);
    defense = B1_p.defense;
    enemyHitControl(&T1_e, &Base_p, &B1_p, &B2_p, &B3_p);
    CU_ASSERT_EQUAL((defense - T1_e.damage), B1_p.defense);
    
    B1_p.defense = 0;
    hp = B1_p.hp;
    enemyHitControl(&T1_e, &Base_p, &B1_p, &B2_p, &B3_p);
    CU_ASSERT_EQUAL((hp - T1_e.damage), B1_p.hp);
    
    setTroopOnMap(map1, &T1_e, 5, (map_y/2)+5, 0, 1, 0);
    defense = B2_p.defense;
    enemyHitControl(&T1_e, &Base_p, &B1_p, &B2_p, &B3_p);
    CU_ASSERT_EQUAL((defense - T1_e.damage), B2_p.defense);
    
    B2_p.defense = 0;
    hp = B2_p.hp;
    enemyHitControl(&T1_e, &Base_p, &B1_p, &B2_p, &B3_p);
    CU_ASSERT_EQUAL((hp - T1_e.damage), B2_p.hp);
    
    setTroopOnMap(map1, &T1_e, 12, (map_y/2)-1, 0, 1, 0);
    defense = B3_p.defense;
    enemyHitControl(&T1_e, &Base_p, &B1_p, &B2_p, &B3_p);
    CU_ASSERT_EQUAL((defense - T1_e.damage), B3_p.defense);
    
    B3_p.defense = 0;
    hp = B3_p.hp;
    enemyHitControl(&T1_e, &Base_p, &B1_p, &B2_p, &B3_p);
    CU_ASSERT_EQUAL((hp - T1_e.damage), B3_p.hp);
    
    setTroopOnMap(map1, &T1_e, 9, (map_y/2)-3, 0, 1, 0);
    defense = Base_p.defense;
    enemyHitControl(&T1_e, &Base_p, &B1_p, &B2_p, &B3_p);
    CU_ASSERT_EQUAL((defense - T1_e.damage), Base_p.defense);
    
    Base_p.defense = 0;
    hp = Base_p.hp;
    enemyHitControl(&T1_e, &Base_p, &B1_p, &B2_p, &B3_p);
    CU_ASSERT_EQUAL((hp - T1_e.damage), Base_p.hp);
    
    map1 = deallocMap(map1);
}