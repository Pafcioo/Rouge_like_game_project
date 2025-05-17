#include <iostream>
#include "EnemyManager.h"

void EnemyManager::addEnemy(std::shared_ptr<Enemy> enemy)
{
    vectorOfEnemies.push_back(enemy);
}

void EnemyManager::drawEnemies(sf::RenderWindow& window)
{
    for (const auto& enemy : vectorOfEnemies)
    {
        enemy->draw(window, sf::RenderStates::Default);
    }
}