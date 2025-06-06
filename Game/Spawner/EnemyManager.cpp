#include <iostream>
#include "Game/Spawner/EnemyManager.h"

void EnemyManager::addEnemy(std::shared_ptr<Entity> enemy)
{
    vectorOfEnemies.push_back(enemy);
}

void EnemyManager::drawEnemies(sf::RenderTarget& target)
{
    for (const auto& enemy : vectorOfEnemies)
    {
        enemy->draw(target, sf::RenderStates::Default);
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
    }
}