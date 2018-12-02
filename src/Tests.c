#include <gtest/gtest.h>
#include "EnemyFunc.h"
// #include "GameLogic.h"
// #include "MapFunc.h"
// #include "PlayerFunc.h"
// #include "WinManager.h"

using namespace std;
/* Teste case para biblioteca EnemyFunc.h */
TEST(enemy_func,testa_path){

    int path_y;
    path_y = ReadPathY(1, 1);

}



int main(int argc, char **argv)
{

	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
