#include <iostream>
#include "../inc/EnemyManager.h"
#include <algorithm>

void EnemyManager::setGameplayInfo(std::shared_ptr<GameplayInfoSource> gameplayInfoSource)
{
    gameplayInfo = gameplayInfoSource;
}

void EnemyManager::addEnemy(std::shared_ptr<Entity> enemy)
{
    vectorOfEnemies.push_back(enemy);
}

void EnemyManager::draw(sf::RenderTarget& target)
{
    for (const auto& enemy : vectorOfEnemies)
    {
        enemy->draw(target, sf::RenderStates::Default);
    }
}

void EnemyManager::update(float deltaTime)
{
    for (const auto& entity : vectorOfEnemies) {
        if(auto enemy = std::dynamic_pointer_cast<Enemy>(entity))
        {
            enemy->update(deltaTime);
        }
        if (entity->getHealth() <= 0) {
            gameplayInfo->setInfo("EnemiesKilled", gameplayInfo->getInfo<int>("EnemiesKilled") + 1);
        }
    }
        vectorOfEnemies.erase(std::remove_if(vectorOfEnemies.begin(), vectorOfEnemies.end(), [](std::shared_ptr<Entity> entity) {
            return entity->getHealth() <= 0;
        }), vectorOfEnemies.end());

}

std::vector<std::shared_ptr<Entity> > EnemyManager::getEnemies() {
    return vectorOfEnemies;
}
