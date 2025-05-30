#include <iostream>
#include "Game/Spawner/EnemyManager.h"

#include <algorithm>

void EnemyManager::addEnemy(std::shared_ptr<Entity> enemy)
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

void EnemyManager::update(float deltaTime)
{
    for (const auto& entity : vectorOfEnemies)
    {
        if(auto enemy = std::dynamic_pointer_cast<Enemy>(entity))
        {
            enemy->update(deltaTime);
        }
        vectorOfEnemies.erase(std::remove_if(vectorOfEnemies.begin(), vectorOfEnemies.end(), [](std::shared_ptr<Entity> entity) {
            return entity->getHealth() <= 0;
        }), vectorOfEnemies.end());
    }
}

std::vector<std::shared_ptr<Entity> > EnemyManager::getEnemies() {
    return vectorOfEnemies;
}
