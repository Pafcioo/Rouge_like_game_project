#include <iostream>
#include "EnemyManager.h"

void EnemyManager::addEnemy(std::shared_ptr<Enemy> enemy)
{
    vectorOfEnemies.push_back(enemy);
}